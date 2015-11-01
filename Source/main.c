#ifndef USBMOUSE_C
#define USBMOUSE_C

/** INCLUDES **/
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "config.h"
#include <delays.h>
/****************************************/


/** VARIABLES **/
/*
/* System Variables */
#pragma udata
BYTE old_sw2,old_sw3;
BOOL emulate_mode;
BYTE movement_length;
BYTE vector = 0;
#pragma udata USB_VARS
unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];
#pragma udata
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
/*
/* Interrapt variables */
BYTE TMR0_Inter = 0;
BYTE TMR1_Inter = 0;
/*
/* Step Motors variables */
int stepMotor1DelayMs = 0;
int stepMotor2DelayMs = 0;
/*
/* General Variables */
BOOL wasAborted = FALSE;
/************************************************/


/** ENUMS **/
/*
/* Commands */
enum 
{
    /** Impulse counter commands **/
    /*************************/
    StartCalculateImpulses = 0x51,
    /*************************/

    /** Step Motor commands **/
    /*************************/
    /* First Step Motor */
    StepMotor1SetDelayMs = 0x20,
    StepMotor1OnIncrement = 0x21,    
    StepMotor1OnDecrement = 0x22,     

    /* Second Step Motor */
    StepMotor2SetDelayMs = 0x30,
    StepMotor2OnIncrement = 0x31,    
    StepMotor2OnDecrement = 0x32,
    /*************************/

    /** Abort all current actions **/
    /*************************/
    AbortAllActions = 0x10
    /*************************/
};
/*****************************************************/


/** FUNCTION PROTOTYPES **/
/*
/* System Functions */
void Emulate_Mouse(void);
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
BOOL Switch2IsPressed(void);
BOOL Switch3IsPressed(void);
void USBCBSuspend(void);
void USBCBWakeFromSuspend(void);
void USBCB_SOF_Handler(void);
void USBCBErrorHandler(void);
void USBCBCheckOtherReq(void);
void USBCBStdSetDscHandler(void);
void USBCBInitEP(void);
void USBCBSendResume(void);
/*
/* User Functions */
/*
/* Timers &/or Impulse counters  */
void TMR_SendData();
void TMR0_ClearREG();
void TMR1_ClearREG();
void StartImpulseCounter();
/*
/* Step Motors */
void SetDelayMsForStepMotor1(BYTE delayMs);
void SetDelayMsForStepMotor2(BYTE delayMs);
void StepMotor1OnForward(BYTE, BYTE);
void StepMotor1OnBack(BYTE, BYTE);
/*
/* Delay */
void Delay(BYTE, BYTE);
void DelayMs(BYTE);
void DelaySec(BYTE sec);
/*
/* General */
BOOL WasAborted();
void SetAbort();
void SendDataToPC();
/********************************************/


/** FUNCTION IMPLEMENTATIONS **/
/*
/* System Functions */

void main(void)
{
    InitializeSystem();// user's initializations

    while(1)
    {
        USBDeviceTasks(); 
        ProcessIO();        
    }
}

static void InitializeSystem(void)
{
    ADCON1 |= 0x0F; // Default all pins to digital

    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
    USBDeviceInit();	
    UserInit();
    
    TMR0L =0;
    TMR0H =0;
    
    TMR1L =0;
    TMR1H =0;
    
    TMR3L =0;
    TMR3H =0;
        
    TRISDbits.TRISD7 =0;
    TRISBbits.TRISB0 =0;
    PORTDbits.RD7 =0;
    PORTBbits.RB0 =0;
    
    RCONbits.IPEN =1;   
    INTCONbits.GIEH =1;  
    INTCONbits.GIEL =1;   
            
    /****************timer0*************/
    INTCONbits.TMR0IE = 1;  
    INTCON2bits.TMR0IP = 1; 
    TRISAbits.TRISA4 =1; 
    T0CONbits.T08BIT =0;    
    T0CONbits.T0CS =1;      
    T0CONbits.T0SE =1;      
    T0CONbits.PSA =1;       
    
    /****************timer1*************/
    PIE1bits.TMR1IE = 1;  
    IPR1bits.TMR1IP = 1;  
    TRISCbits.TRISC0 =1;    
    T1CONbits.RD16 =0;      
    T1CONbits.T1RUN =0;     
    T1CONbits.T1CKPS1 =0;   
    T1CONbits.T1CKPS0 =0;
    T1CONbits.T1OSCEN =0;   
    T1CONbits.T1SYNC =1;    
    T1CONbits.TMR1CS =1;    
            
    // Step Motor***********************/
    // output pins
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    TRISCbits.TRISC7 = 0;
    TRISCbits.TRISC6 = 0;
    // for begin position
    PORTDbits.RD5 = 1;
    PORTDbits.RD4 = 0;
    PORTCbits.RC7 = 0;
    PORTCbits.RC6 = 0;
}

void ProcessIO(void)
{ 
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
    {
        return;
    }
    
    if(!HIDRxHandleBusy(USBOutHandle))
    {   
        switch(ReceivedDataBuffer[0])
        {   
             /** Impulses counter **/    
            /**/
            case StartCalculateImpulses:
                StartImpulseCounter();
            break;
            /**/       
            
            /** Step Motors **/
            /**/
            case StepMotor1OnIncrement:   
                StepMotor1OnForward(ReceivedDataBuffer[1], ReceivedDataBuffer[2]); 
            break;

            case StepMotor1OnDecrement:     
                StepMotor1OnBack(ReceivedDataBuffer[1], ReceivedDataBuffer[2]);
            break;

            case StepMotor1SetDelayMs: // set delay for stepMotor
                SetDelayMsForStepMotor1(ReceivedDataBuffer[1]);
            break;

            case StepMotor2SetDelayMs: // set delay for stepMotor
                SetDelayMsForStepMotor2(ReceivedDataBuffer[1]);
            break;
            /**/
            
            /** Abort **/
            /**/
            case AbortAllActions:
                SetAbort();
            break;
            /**/
        }       
        //Re-arm the OUT endpoint for the next packet
        USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
   }   
}

void UserInit(void)
{
    //Initialize all of the LED pins
    mInitAllLEDs();
    
    //Initialize all of the push buttons
    mInitAllSwitches();
    old_sw2 = sw2;
    old_sw3 = sw3;
    
    //initialize the variable holding the handle for the last
    // transmission
    USBOutHandle = 0;
    USBInHandle = 0;
}

BOOL Switch2IsPressed(void)
{
    if(sw2 != old_sw2)
    {
        old_sw2 = sw2;                  // Save new value
        if(sw2 == 0)                    // If pressed
            return TRUE;                // Was pressed
    }//end if
    return FALSE;                       // Was not pressed
}

BOOL Switch3IsPressed(void)
{
    if(sw3 != old_sw3)
    {
        old_sw3 = sw3;                  // Save new value
        if(sw3 == 0)                    // If pressed
            return TRUE;                // Was pressed
    }//end if
    return FALSE;                       // Was not pressed
}

void USBCBSuspend(void){}

void USBCBWakeFromSuspend(void){}

void USBCB_SOF_Handler(void){}

void USBCBErrorHandler(void){}

void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}

void USBCBStdSetDscHandler(void){}

void USBCBInitEP(void)
{
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,65);
}

void USBCBSendResume(void)
{
    static WORD delay_count;

    USBResumeControl = 1;                // Start RESUME signaling

    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}

/*
/* User Functions */
/*
/* Timers &/or Impulse counters  */
void TMR_SendData()
{
    /*********TMR0 DATA*****************/  
    ToSendDataBuffer[1] = TMR0L;
    ToSendDataBuffer[2] = TMR0H;
    ToSendDataBuffer[3] = TMR0_Inter;
    /***********************************/
    /*********TMR1 DATA*****************/        
    ToSendDataBuffer[4] = TMR1L;
    ToSendDataBuffer[5] = TMR1H;
    ToSendDataBuffer[6] = TMR1_Inter;
    /***********************************/
    
    // Send data via USB          
    SendDataToPC();
}

void TMR0_ClearREG()
{
    int i;
    for(i=0; i<2; i++)
    {
        TMR0L = 0;
        TMR0H = 0;
        TMR0_Inter = 0;
    }    
}

void TMR1_ClearREG()
{
    int i;
    for(i=0; i<2; i++)
    {
        TMR1L = 0;
        TMR1H = 0;
        TMR1_Inter = 0;
    }    
} 

void StartImpulseCounter()
{
    // Clear TMR registers.
    TMR0_ClearREG();
    TMR1_ClearREG();

    // Start impulse counters.
    T1CONbits.TMR1ON = 1;
    T0CONbits.TMR0ON = 1;

    // Do delay sec of ReceivedDataBuffer[1] value.
    DelaySec(ReceivedDataBuffer[1]);

    // Stop impulse counters.
    T1CONbits.TMR1ON = 0;
    T0CONbits.TMR0ON = 0;

    // Send calculate result to PC;
    TMR_SendData();
}

/*
/* Step Motors */
void SetDelayMsForStepMotor1(BYTE delayMs)
{
    stepMotor1DelayMs = delayMs;
}

void SetDelayMsForStepMotor2(BYTE delayMs)
{
    stepMotor2DelayMs = delayMs;
}

void StepMotor1OnForward(BYTE data0, BYTE data1)
{	
	long stepCount = (long)data0 + (long)data1 * 255;
	int i=0;
	
	BYTE delayMs;
	if (stepCount == 1)
	{
    	delayMs = 0;
	}
	else
	{
    	delayMs = stepMotor1DelayMs;
	}

	for(i=0; i<stepCount; i++)
	{
        if (WasAborted())
        {
            break;
        }
        else
        {
            if(LATDbits.LATD5)
            {
                LATDbits.LATD5 = 0;
                LATDbits.LATD4 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATDbits.LATD4)
            {
                LATDbits.LATD4 = 0;
                LATCbits.LATC7 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATCbits.LATC7)
            {
                LATCbits.LATC7 = 0;
                LATCbits.LATC6 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATCbits.LATC6)
            {
                LATCbits.LATC6 = 0;
                LATDbits.LATD5 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
        }
	}
	// send info to PC. its need to resume the dimensions on the PC
	SendDataToPC();
}

void StepMotor1OnBack(BYTE data0, BYTE data1)
{
	long stepCount = (long)data0 + (long)data1 * 255;
	int i=0;
	
	BYTE delayMs;
	if (stepCount == 1)
	{
    	delayMs = 0;
	}
	else
	{
    	delayMs = stepMotor1DelayMs;
	}

	for(i=0; i<stepCount; i++)
	{
        if (WasAborted())
        {
            break;
        }
        else
        {
            if(LATDbits.LATD5)
            {
                LATDbits.LATD5 = 0;
                LATCbits.LATC6 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATCbits.LATC6)
            { 
                LATCbits.LATC6 = 0;
                LATCbits.LATC7 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATCbits.LATC7)
            {
                LATCbits.LATC7 = 0;
                LATDbits.LATD4 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
            if(LATDbits.LATD4)
            {
                LATDbits.LATD4 = 0;
                LATDbits.LATD5 = 1;
                //Delay1KTCYx(24);
                //DelaySec(1);
                DelayMs(delayMs);
                continue;
            }
        }
	}
	// send info to PC. its need to resume the dimensions on the PC
	SendDataToPC();
}

/*
/* Delay */
void Delay(BYTE data0, BYTE data1)
{
	BYTE delay_100_ms = 0;
	BYTE delay_10_ms = 0;
	BYTE delay_1_ms = 0;
	
	BYTE delay_200_ms = 0;
	BYTE delay_20_ms = 0;
	
	long time_ms = (long)data0*256 + (long)data1;
	BYTE i = 0;
	
	delay_200_ms = time_ms/200;
	delay_100_ms = (time_ms - delay_200_ms*200)/100;
	delay_20_ms = (time_ms - delay_200_ms*200 - delay_100_ms*100)/20;
	delay_10_ms = (time_ms - delay_200_ms*200 - delay_100_ms*100 - delay_20_ms*20)/10;
	delay_1_ms = time_ms - delay_200_ms*200 - delay_100_ms*100 - delay_20_ms*20 - delay_1_ms;
	
	for(i=0; i<delay_200_ms; i++)
    {
		Delay10KTCYx(240);
    }
		
	for(i=0; i<delay_100_ms; i++)
    {
		Delay10KTCYx(120);
    }
		
	for(i=0; i<delay_20_ms; i++)
    {
		Delay10KTCYx(24);
    }
		
	for(i=0; i<delay_10_ms; i++)
    {
		Delay10KTCYx(12);
    }
		
	for(i=0; i<delay_1_ms; i++)
    {
		Delay1KTCYx(12);
    }
}

void DelayMs(BYTE delayMs)
{
    BYTE i = 0;
    for (i = 0; i < delayMs; i++)
    {
        Delay100TCYx(120);
    }
}

void DelaySec(BYTE sec)
{
    BYTE delay_200_ms = sec*5;

    BYTE i=0;
    for(i=0; i<delay_200_ms; i++)
    {
        Delay10KTCYx(240);
    }
}

/*
/* General */
void Hight_Interrupt(void)
{
    if(INTCONbits.TMR0IF == 1)
    {
        INTCONbits.TMR0IF = 0;
        TMR0_Inter++;
    }
    
    if(PIR1bits.TMR1IF == 1)
    {
        PIR1bits.TMR1IF = 0;
        TMR1_Inter++;
    }
}

BOOL WasAborted()
{
    if (wasAborted)
    {
        wasAborted = FALSE;
        return TRUE;
    }
    return FALSE;
}

void SetAbort()
{
    wasAborted = TRUE;
}

void SendDataToPC() 
{
	ToSendDataBuffer[0] =  ReceivedDataBuffer[0]; // The received command.
    ToSendDataBuffer[62] = ReceivedDataBuffer[1]; // The received first byte.
    ToSendDataBuffer[63] = ReceivedDataBuffer[2]; // The received second byte.
    
    if (!HIDTxHandleBusy(USBInHandle))
    	USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer,64);
}

/*****************************************************/

#endif
