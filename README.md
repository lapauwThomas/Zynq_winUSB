# Zynq winUSB
WinUSB implementation for the Xilinx ZYNQ platform (Zybo board)


This repo contains an implementation for the ZYBO board acting as a WINUSB device using the standard inf file (win8.1 and higher). The descriptors, strings and vendor commands are implemented according to the Microsoft OS descriptors 1.0 . 
The device mounts as a WINUSB device with a vendor device class. It has one interface with a single bulk interface in loopback. Using the [test application](https://github.com/lapauwThomas/WINUSB_loopback) data can be sent trough the pipe, which is then looped back and shown.

The SDK folder also contains an application "GUID_convertor.exe" combined with GUID.bat to generate a header file based on the GUID.txt file in the src folder. This header file contains a define of the GUID in UTF16-LE encoding which is used in the Extended Properties. The bat file is used in the makefile to make sure the GUID is up to date.

Tip: If something is wrong with the header, and the device is not recognized as a WINUSB device, it will not be reconginzed as such in the future unless you change the PID (or reboot?).

The code is an edit of the xusbps mass storage example from the XilinxProcessorIPLib. Code might not be fail safe in a lot of places, but the basis work. 


Note: This was made as a test to use as a basis for later development. Bugs and errors (probably) will not be fixed.
