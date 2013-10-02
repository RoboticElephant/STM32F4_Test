#ifndef __DATAFLASHSPI_H
#define __DATAFLASHSPI_H

#include "Hdr.h"

#define SPI_SS_PIN      GPIO_Pin_12
#define SPI_SS_PORT     GPIOB
#define SPI_SS_Periph   RCC_AHB1Periph_GPIOB

enum BUFFER_SEL
{
    BUFFER_1 = 0,
    BUFFER_2 = 1
};
typedef enum BUFFER_SEL BUFFER_SEL;

// Initialize the correct slave select pin
void InitDataFlashSPI(void);

// This sends the command (0x84 = buf1 or 0x87 = buf2) followed by 15 dont care bits
//followed by 9 page location bits. The value is 0 to 256 for page
#define WRITE_BUFFER(buf1_2, loc)  {buf1_2, 0xff, ((uint8_t)loc >> 8), (uint8_t)loc, '\0'}

// This sends the command (0xD4 = buf1 or 0xD6 = buf2) followed by 15 dont care bits
//followed by 9 page location bits. The value is 0 to 256 for page
#define READ_BUFFER(buf1_2, loc)  {buf1_2, 0xff, ((uint8_t)loc >> 8), (uint8_t)loc, '\0'}

void writeToDataFlash(SPI_TypeDef* SPIx, BUFFER_SEL buf1_2, uint16_t buffLocation, char* data, int leng);
void readSingByteDataFlash(SPI_TypeDef* SPIx, BUFFER_SEL buf1_2, uint16_t buffLocation, unsigned char *saveString, int readSize);

#endif
