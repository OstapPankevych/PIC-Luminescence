#include "Usb/usb_config.h"
#include "Usb/usb_device.h"
#include "Usb/usb.h"
#include "Usb/usb_function_hid.h"

/* CONFIGURATION */
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            LATAbits.LATA7 = 1;
        
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
            LATAbits.LATA7 = 0;
        }
    #endif
}
#endif

#if defined(PICDEM_FS_USB)      // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF

  
/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the current Microchip USB bootloader 
	//examples are intended to occupy addresses 0x00-0x7FF or
	//0x00-0xFFF depending on which bootloader is used.  Therefore,
	//the bootloader code remaps these vectors to new locations
	//as indicated below.  This remapping is only necessary if you
	//wish to program the hex file generated from this project with
	//the USB bootloader.  If no bootloader is used, edit the
	//usb_config.h file and comment out the following defines:
	//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
	//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER
	

#pragma code hight_vect = 0x0008
#pragma interrupt Hight_Interrupt // interapt config
void hight_vect(void)
{
    _asm 
    GOTO Hight_Interrupt 
    _endasm
}
#pragma code

    
#elif defined(LOW_PIN_COUNT_USB_DEVELOPMENT_KIT)
        #pragma config CPU_DIV = NoClkDiv, USB_LSCLK = OFF                   // CONFIG1L
        #pragma config FOSC = HS, PLL_EN=ON, FCMEN = OFF, IESO = OFF                     // CONFIG1H
        #pragma config PWRT = OFF, BOREN = OFF, BORV = 30, VREGEN = ON					// CONFIG2L
        #pragma config WDTEN = OFF, WDTPS = 32768                                     // CONFIG2H
        #pragma config MCLRE = OFF, HFOFST = OFF				        // CONFIG3H
        #pragma config STVREN = ON, LVP = OFF, XINST = OFF, BBSIZ=OFF	// CONFIG4L
        #pragma config CP0 = OFF, CP1 = OFF						                    // CONFIG5L
        #pragma config CPB = OFF                                    			    // CONFIG5H
        #pragma config WRT0 = OFF, WRT1 = OFF						                // CONFIG6L
        //#pragma config WRTB = ON, WRTC = OFF                            			// CONFIG6H
        // Disabled WRTB for debugging.  Reenable for real.
        #pragma config WRTB = OFF, WRTC = OFF                            			// CONFIG6H
        #pragma config EBTR0 = OFF, EBTR1 = OFF							           	// CONFIG7L
        #pragma config EBTRB = OFF                                                  // CONFIG7H
        
        
        #ifdef __DEBUG
            #pragma config BKBUG = ON 
        #endif
        #ifndef __DEBUG
            #pragma config BKBUG = OFF
        #endif   

#elif defined(EXPLORER_16)
    #ifdef __PIC24FJ256GB110__ //Defined by MPLAB when using 24FJ256GB110 device
        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
        _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & IOL1WAY_ON)
    #else
        #error No hardware board defined, see "HardwareProfile.h" and __FILE__
    #endif
#else
    #error No hardware board defined, see "HardwareProfile.h" and __FILE__
#endif

                