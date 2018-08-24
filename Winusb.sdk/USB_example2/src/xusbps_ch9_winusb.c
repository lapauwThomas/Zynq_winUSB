/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal 
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
 * @file xusbps_ch9_storage.c
 *
 * This file contains the implementation of the storage specific chapter 9 code
 * for the example.
 *
 *<pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- ---------------------------------------------------------
 * 1.00a wgr  10/10/10 First release
 *</pre>
 ******************************************************************************/

/***************************** Include Files *********************************/

#include <string.h>
#include "GUID.h"
#include "xparameters.h"	/* XPAR parameters */
#include "xusbps.h"		/* USB controller driver */

#include "xusbps_ch9.h"
#include "xusbps_ch9_winusb.h"
#include "DEBUG.h"
/************************** Constant Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	u8  bLength;
	u8  bDescriptorType;
	u16 bcdUSB;
	u8  bDeviceClass;
	u8  bDeviceSubClass;
	u8  bDeviceProtocol;
	u8  bMaxPacketSize0;
	u16 idVendor;
	u16 idProduct;
	u16 bcdDevice;
	u8  iManufacturer;
	u8  iProduct;
	u8  iSerialNumber;
	u8  bNumConfigurations;
#ifdef __ICCARM__
}USB_STD_DEV_DESC;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_STD_DEV_DESC;
#endif

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	u8  bLength;
	u8  bDescriptorType;
	u16 wTotalLength;
	u8  bNumInterfaces;
	u8  bConfigurationValue;
	u8  iConfiguration;
	u8  bmAttributes;
	u8  bMaxPower;
#ifdef __ICCARM__
}USB_STD_CFG_DESC;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_STD_CFG_DESC;
#endif

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	u8  bLength;
	u8  bDescriptorType;
	u8  bInterfaceNumber;
	u8  bAlternateSetting;
	u8  bNumEndPoints;
	u8  bInterfaceClass;
	u8  bInterfaceSubClass;
	u8  bInterfaceProtocol;
	u8  iInterface;
#ifdef __ICCARM__
}USB_STD_IF_DESC;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_STD_IF_DESC;
#endif

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	u8  bLength;
	u8  bDescriptorType;
	u8  bEndpointAddress;
	u8  bmAttributes;
	u16 wMaxPacketSize;
	u8  bInterval;
#ifdef __ICCARM__
}USB_STD_EP_DESC;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_STD_EP_DESC;
#endif

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	u8  bLength;
	u8  bDescriptorType;
	u16 wLANGID[1];
#ifdef __ICCARM__
}USB_STD_STRING_DESC;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_STD_STRING_DESC;
#endif

#ifdef __ICCARM__
#pragma pack(push, 1)
#endif
typedef struct {
	USB_STD_CFG_DESC stdCfg;
	USB_STD_IF_DESC ifCfg;
	USB_STD_EP_DESC epCfg1;
	USB_STD_EP_DESC epCfg2;
#ifdef __ICCARM__
}USB_CONFIG;
#pragma pack(pop)
#else
}__attribute__((__packed__))USB_CONFIG;
#endif




/* OS descriptor as per WinUSB requirement */
const u8 MSFTUsbOSDscr[] = {
0x12,                           /* bLength: Length of the descriptor */
0x03,        					/* bDescriptorType: Descriptor type */
'M',0x00,                        /* qwSignature: Signature field */
'S',0x00,
'F',0x00,
'T',0x00,
'1',0x00,
'0',0x00,
'0',0x00,
bMS_VendorCode,                           /* bMS_VendorCode: Vendor code */
0x00                            /* bPad: Pad field */
};





/* Extended Compat ID OS Feature Descriptor as per WinUSB requirement */
const u8 MSFTUsbExtCompatIdOSFeatureDscr[] = {

// Header Section
0x28,0x00,0x00,0x00,                     /* dwLength: 40 = 16 + 24 */
0x00,0x01,                               /* bcdVersion: The descriptor’s version number */
0x04,0x00,                                 /* wIndex: Extended compat ID descriptor */
0x01,                                    /* bCount: Number of function sections */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,      /* RESERVED */

// Function Sections
0x00,                                    /* bFirstInterfaceNumber */
0x01,                                    /* RESERVED */
'W','I','N','U','S','B',0x00,0x00,       /* compatibleID */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* subCompatibleID */
0x00,0x00,0x00,0x00,0x00,0x00            /* RESERVED */ };


/* Extended Properties OS Feature Descriptor as per WinUSB (USB 3.0) requirement */
const u8 MSFTUsbExtPropertiesOSFeatureDscr[]= {
// Header Section
0x8E,0x00,0x00,0x00,                     /* dwLength: 142 = 10 + 132 */
0x00,0x01,                               /* bcdVersion: The descriptor’s version number */
0x05,0x00,                                 /* wIndex: Extended property OS descriptor */
0x01,0x00,                               /* bCount: Number of properties */
// Custom Property Section 1
0x84,0x00,0x00,0x00,                     /* dwSize: 132 = 14 + 40 + 78 */
0x01,0x00,0x00,0x00,                     /* dwPropertyDataType: A NULL-terminated Unicode String (REG_SZ) */
0x28,0x00,                               /* wPropertyNameLength: 40 */
/* bPropertyName: "DeviceInterfaceGUID" */
0x44, 0x00, 0x65, 0x00, 0x76, 0x00, 0x69, 0x00, 0x63, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x66, 0x00, 0x61, 0x00, 0x63, 0x00, 0x65, 0x00, 0x47, 0x00, 0x55, 0x00, 0x49, 0x00, 0x44, 0x00, 0x00, 0x00,



    0x4E,0x00,0x00,0x00, /* dwPropertyDataLength: 78 */

#ifndef GUID_HEX //if GUID_HEX is not defined in the GUID.h file
/*  bPropertyData: "{01234567-2A4F-49EE-8DD3-FADEA377234A}"      '{',0x00,'0',0x00,'1',0x00,'2',0x00,'3',0x00,
'4',0x00,'5',0x00,'6',0x00,'7',0x00,'-',0x00,
'2',0x00,'A',0x00,'4',0x00,'F',0x00,'-',0x00,
'4',0x00,'9',0x00,'E',0x00,'E',0x00,'-',0x00,
'8',0x00,'D',0x00,'D',0x00,'3',0x00,'-',0x00,
'F',0x00,'A',0x00,'D',0x00,'E',0x00,'A',0x00,
'3',0x00,'7',0x00,'7',0x00,'2',0x00,'3',0x00,
'4',0x00,'A',0x00,     '}',0x00,     0x00,0x00*/
#else
GUID_HEX //define from GUID.h file
#endif

 };

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

#define USB_ENDPOINT0_MAXP		0x40

#define USB_BULKIN_EP			1
#define USB_BULKOUT_EP			1

#define USB_DEVICE_DESC			0x01
#define USB_CONFIG_DESC			0x02
#define USB_STRING_DESC			0x03
#define USB_INTERFACE_CFG_DESC		0x04
#define USB_ENDPOINT_CFG_DESC		0x05


/*****************************************************************************/
/**
*
* This function returns the device descriptor for the device.
*
* @param	BufPtr is pointer to the buffer that is to be filled
*		with the descriptor.
* @param	BufLen is the size of the provided buffer.
*
* @return 	Length of the descriptor in the buffer on success.
*		0 on error.
*
******************************************************************************/
u32 XUsbPs_Ch9SetupDevDescReply(u8 *BufPtr, u32 BufLen)
{
	USB_STD_DEV_DESC deviceDesc = {
		sizeof(USB_STD_DEV_DESC),	/* bLength */
		USB_DEVICE_DESC,		/* bDescriptorType */
		be2les(0x0200),			/* bcdUSB 2.0 */
		0xFF,				/* bDeviceClass */
		0xFF,				/* bDeviceSubClass */
		0xFF,				/* bDeviceProtocol */
		USB_ENDPOINT0_MAXP,		/* bMaxPackedSize0 */
		be2les(VID),			/* idVendor */
		be2les(PID),			/* idProduct */
		be2les(0x0100),			/* bcdDevice */
		0x01,				/* iManufacturer */
		0x02,				/* iProduct */
		0x03,				/* iSerialNumber */
		0x01				/* bNumConfigurations */
	};

	/* Check buffer pointer is there and buffer is big enough. */
	if (!BufPtr) {
		return 0;
	}

	if (BufLen < sizeof(USB_STD_DEV_DESC)) {
		return 0;
	}

	memcpy(BufPtr, &deviceDesc, sizeof(USB_STD_DEV_DESC));

	return sizeof(USB_STD_DEV_DESC);
}






/*****************************************************************************/
/**
*
* This function returns the configuration descriptor for the device.
*
* @param	BufPtr is the pointer to the buffer that is to be filled with
*		the descriptor.
* @param	BufLen is the size of the provided buffer.
*
* @return 	Length of the descriptor in the buffer on success.
*		0 on error.
*
******************************************************************************/
u32 XUsbPs_Ch9SetupCfgDescReply(u8 *BufPtr, u32 BufLen)
{
	USB_CONFIG config = {
		/* Std Config */
		{sizeof(USB_STD_CFG_DESC),	/* bLength */
		 USB_CONFIG_DESC,		/* bDescriptorType */
		 be2les(sizeof(USB_CONFIG)),	/* wTotalLength */
		 0x01,				/* bNumInterfaces */
		 0x01,				/* bConfigurationValue */
		 0x04,				/* iConfiguration */
		 0xc0,				/* bmAttribute */
		 0x00},				/* bMaxPower  */

		/* Interface Config */
		{sizeof(USB_STD_IF_DESC),	/* bLength */
		 USB_INTERFACE_CFG_DESC,	/* bDescriptorType */
		 0x00,				/* bInterfaceNumber */
		 0x00,				/* bAlternateSetting */
		 0x02,				/* bNumEndPoints */
		 0x00,				/* bInterfaceClass */
		 0x00,				/* bInterfaceSubClass */
		 0xFF,				/* bInterfaceProtocol */
		 0x03},				/* iInterface */

		/* Bulk Out Endpoint Config */
		{sizeof(USB_STD_EP_DESC),	/* bLength */
		 USB_ENDPOINT_CFG_DESC,		/* bDescriptorType */
		 0x00 | USB_BULKOUT_EP,		/* bEndpointAddress */
		 0x02,				/* bmAttribute  */
		 be2les(0x200),			/* wMaxPacketSize */
		 0x00},				/* bInterval */

		/* Bulk In Endpoint Config */
		{sizeof(USB_STD_EP_DESC),	/* bLength */
		 USB_ENDPOINT_CFG_DESC,		/* bDescriptorType */
		 0x80 | USB_BULKIN_EP,		/* bEndpointAddress */
		 0x02,				/* bmAttribute  */
		 be2les(0x200),			/* wMaxPacketSize */
		 0x00}				/* bInterval */
	};

	/* Check buffer pointer is OK and buffer is big enough. */
	if (!BufPtr) {
		return 0;
	}

	if (BufLen < sizeof(USB_STD_DEV_DESC)) {
		return 0;
	}

	memcpy(BufPtr, &config, sizeof(USB_CONFIG));


	return sizeof(USB_CONFIG);

}


/*****************************************************************************/
/**
*
* This function returns a string descriptor for the given index.
*
* @param	BufPtr is a  pointer to the buffer that is to be filled with
*		the descriptor.
* @param	BufLen is the size of the provided buffer.
* @param	Index is the index of the string for which the descriptor
*		is requested.
*
* @return 	Length of the descriptor in the buffer on success.
*		0 on error.
*
******************************************************************************/
u32 XUsbPs_Ch9SetupStrDescReply(u8 *BufPtr, u32 BufLen, u8 Index)
{
	int i;

	static char *StringList[] = {
		"UNUSED",
		MFG_NAME, //from USB_CONFIG.h
		DEV_NAME, //from USB_CONFIG.h
		"2A49876D9CC1AA4",
		"Default Configuration",
		"Default Interface",
	};
	char *String;
	u32 StringLen;
	u32 DescLen;
	u8 TmpBuf[128];

	USB_STD_STRING_DESC *StringDesc;

	// Handler for string index 0xEE --> WINUSB definiton
	if(Index == 0xEE){
#ifdef  CH9_DEBUG
		xil_printf("WINUSB STRING");
#endif
		memcpy(BufPtr, MSFTUsbOSDscr, sizeof(MSFTUsbOSDscr)); //copy the constant array for the OS descriptor to the output.
		return sizeof(MSFTUsbOSDscr);
	}

	if (!BufPtr) {
		return 0;
	}

	if (Index >= sizeof(StringList) / sizeof(char *)) {
		return 0;
	}

	String = StringList[Index];
	StringLen = strlen(String);

	StringDesc = (USB_STD_STRING_DESC *) TmpBuf;

	/* Index 0 is special as we can not represent the string required in
	 * the table above. Therefore we handle index 0 as a special case.
	 */
	if (0 == Index) {
		StringDesc->bLength = 4;
		StringDesc->bDescriptorType = USB_STRING_DESC;
		StringDesc->wLANGID[0] = be2les(0x0409);
	}
	/* All other strings can be pulled from the table above. */
	else {
		StringDesc->bLength = StringLen * 2 + 2;
		StringDesc->bDescriptorType = USB_STRING_DESC;

		for (i = 0; i < StringLen; i++) {
			StringDesc->wLANGID[i] = be2les((u16) String[i]);
		}
	}
	DescLen = StringDesc->bLength;

	/* Check if the provided buffer is big enough to hold the descriptor. */
	if (DescLen > BufLen) {
		return 0;
	}

	memcpy(BufPtr, StringDesc, DescLen);

	return DescLen;
}


/*****************************************************************************/
/**
* This function handles a "set configuration" request.
*
* @param	InstancePtr is a pointer to XUsbPs instance of the controller.
* @param	ConfigIdx is the Index of the desired configuration.
*
* @return	None
*
******************************************************************************/
void XUsbPs_SetConfiguration(XUsbPs *InstancePtr, int ConfigIdx)
{
	Xil_AssertVoid(InstancePtr != NULL);

	/* We only have one configuration. Its index is 1. Ignore anything
	 * else.
	 */
	if (1 != ConfigIdx) {
		return;
	}

	XUsbPs_EpEnable(InstancePtr, 1, XUSBPS_EP_DIRECTION_OUT);
	XUsbPs_EpEnable(InstancePtr, 1, XUSBPS_EP_DIRECTION_IN);

	/* Set BULK mode for both directions.  */
	XUsbPs_SetBits(InstancePtr, XUSBPS_EPCR1_OFFSET,
						XUSBPS_EPCR_TXT_BULK_MASK |
						XUSBPS_EPCR_RXT_BULK_MASK |
						XUSBPS_EPCR_TXR_MASK |
						XUSBPS_EPCR_RXR_MASK);

	/* Prime the OUT endpoint. */
	XUsbPs_EpPrime(InstancePtr, 1, XUSBPS_EP_DIRECTION_OUT);
}
