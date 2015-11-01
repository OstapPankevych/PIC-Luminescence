# MPLAB IDE generated this makefile for use with GNU make.
# Project: USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.mcp
# Date: Wed Jan 14 14:27:44 2015

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

USB\ Device\ -\ HID\ -\ Simple\ Custom\ Demo\ -\ C18\ -\ PICDEM\ FSUSB.cof : ../output/usb_descriptors.o ../output/main.o ../output/usb_device.o ../output/usb_function_hid.o
	$(LD) /l"C:\_MCC18\lib" /k"C:\_MCC18\bin\LKR" "rm18f4550 - HID Bootload.lkr" "..\output\usb_descriptors.o" "..\output\main.o" "..\output\usb_device.o" "..\output\usb_function_hid.o" /u_CRUNTIME /u_DEBUG /m"C:\Users\Ostap\Desktop\PIC\output\USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.map" /w /o"USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.cof"

../output/usb_descriptors.o : usb_descriptors.c ../../../../../_MCC18/h/stdio.h ../../../../../_MCC18/h/stdlib.h ../../../../../_MCC18/h/string.h Include/usb_device.h usb_descriptors.c Include/GenericTypeDefs.h Include/Compiler.h ../../../../../_MCC18/h/p18cxxx.h ../../../../../_MCC18/h/p18f4550.h ../../../../../_MCC18/h/stdarg.h ../../../../../_MCC18/h/stddef.h Include/usb_config.h Include/USB/usb_ch9.h Include/USB/usb_hal.h Include/USB/usb_hal_pic18.h Include/usb_function_hid.h
	$(CC) -p=18F4550 /i"C:\Users\Ostap\Desktop\PIC\Generic HID - Simple Demo - Firmware\Include" -I"C:\_MCC18\h" "usb_descriptors.c" -fo="C:\Users\Ostap\Desktop\PIC\output\usb_descriptors.o" -D__DEBUG -pa=4

../output/main.o : main.c ../../../../../_MCC18/h/stdio.h ../../../../../_MCC18/h/stdlib.h ../../../../../_MCC18/h/string.h Include/USB/usb_device.h Include/usb/usb_common.h ../../../../../_MCC18/h/delays.h main.c Include/GenericTypeDefs.h Include/Compiler.h ../../../../../_MCC18/h/p18cxxx.h ../../../../../_MCC18/h/p18f4550.h ../../../../../_MCC18/h/stdarg.h ../../../../../_MCC18/h/stddef.h Include/usb_config.h Include/USB/usb_ch9.h Include/USB/usb_hal.h Include/USB/usb_hal_pic18.h Include/USB/usb.h ../../../../../_MCC18/h/limits.h Include/usb/usb_ch9.h Include/usb/usb_hal.h Include/usb/usb_device.h Include/HardwareProfile.h Include/USB/usb_function_hid.h
	$(CC) -p=18F4550 /i"C:\Users\Ostap\Desktop\PIC\Generic HID - Simple Demo - Firmware\Include" -I"C:\_MCC18\h" "main.c" -fo="C:\Users\Ostap\Desktop\PIC\output\main.o" -D__DEBUG -pa=4

../output/usb_device.o : usb_device.c ../../../../../_MCC18/h/stdio.h ../../../../../_MCC18/h/stdlib.h ../../../../../_MCC18/h/string.h Include/usb/usb_common.h Include/usb/usb_device.h usb_device.c Include/GenericTypeDefs.h Include/Compiler.h ../../../../../_MCC18/h/p18cxxx.h ../../../../../_MCC18/h/p18f4550.h ../../../../../_MCC18/h/stdarg.h ../../../../../_MCC18/h/stddef.h Include/USB/usb_ch9.h Include/USB/USB.h Include/usb_config.h ../../../../../_MCC18/h/limits.h Include/usb/usb_ch9.h Include/usb/usb_hal.h Include/USB/usb_hal_pic18.h Include/USB/usb_hal.h Include/USB/usb_device.h Include/HardwareProfile.h
	$(CC) -p=18F4550 /i"C:\Users\Ostap\Desktop\PIC\Generic HID - Simple Demo - Firmware\Include" -I"C:\_MCC18\h" "usb_device.c" -fo="C:\Users\Ostap\Desktop\PIC\output\usb_device.o" -D__DEBUG -pa=4

../output/usb_function_hid.o : usb_function_hid.c ../../../../../_MCC18/h/stdio.h ../../../../../_MCC18/h/stdlib.h ../../../../../_MCC18/h/string.h Include/USB/usb_device.h usb_function_hid.c Include/GenericTypeDefs.h Include/Compiler.h ../../../../../_MCC18/h/p18cxxx.h ../../../../../_MCC18/h/p18f4550.h ../../../../../_MCC18/h/stdarg.h ../../../../../_MCC18/h/stddef.h Include/usb_config.h Include/USB/usb_ch9.h Include/USB/usb_hal.h Include/USB/usb_hal_pic18.h Include/USB/usb_function_hid.h
	$(CC) -p=18F4550 /i"C:\Users\Ostap\Desktop\PIC\Generic HID - Simple Demo - Firmware\Include" -I"C:\_MCC18\h" "usb_function_hid.c" -fo="C:\Users\Ostap\Desktop\PIC\output\usb_function_hid.o" -D__DEBUG -pa=4

clean : 
	$(RM) "..\output\usb_descriptors.o" "..\output\main.o" "..\output\usb_device.o" "..\output\usb_function_hid.o" "USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.cof" "USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.hex" "USB Device - HID - Simple Custom Demo - C18 - PICDEM FSUSB.map"

