#ifndef __CAMERA_H
#define __CAMERA_H

#include "Hdr.h"

#define DCMI_DR_ADDRESS     0x50050028
#define FSMC_LCD_ADDRESS    0x60020000

#define OV7670_ADD  0x42

typedef struct
{
  uint8_t Manufacturer_ID1;
  uint8_t Manufacturer_ID2;
  uint8_t Version;
  uint8_t PID; 
} OV7670_IDTypeDef;

void InitDCMI(void);
void MCO1_Init(void);
uint8_t DCMI_OV7670_Init(void);
uint8_t DCMI_OV7670_ReadID(OV7670_IDTypeDef* OV7670ID);
void OV7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height);

#endif