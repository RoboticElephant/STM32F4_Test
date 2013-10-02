#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "Hdr.h"

// USART
extern volatile char *receiveBufferEnd;
extern volatile char *receiveBufferCurrent;
extern const char* RXBUFEND;
void ResetUARTBuffer(void);
int jbgetcRX(char *rxBuffChar);
void jbprintf(USART_TypeDef* USARTx, char* txBuffChar);

// SPI
void jbSPISend(SPI_TypeDef* SPIx, char* txBuffChar, int leng);
char jbSPIReceive(SPI_TypeDef* SPIx);

// I2C
int MasterI2CWrite (I2C_TypeDef* I2Cx, unsigned char address, unsigned char hblb, unsigned char hbyte, unsigned char lbyte, int strLength, unsigned char *saveString);
int MasterI2CRead (I2C_TypeDef* I2Cx, unsigned char address, unsigned char hblb, unsigned char hbyte, unsigned char lbyte, int strLength, unsigned char *saveString);

#endif