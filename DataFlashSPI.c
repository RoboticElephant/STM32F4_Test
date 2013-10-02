#include "DataFlashSPI.h"
#include "Hdr.h"
#include "Communication.h"

void InitDataFlashSPI(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(SPI_SS_Periph, ENABLE);   // Enable the GPIO for the pins
    
    // Set the NSS or SS pin or SPI_SS_PIN to NSS
    GPIO_InitStruct.GPIO_Pin = SPI_SS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   // No Pull up or pull down
    GPIO_Init(SPI_SS_PORT, &GPIO_InitStruct);
    GPIO_SetBits(SPI_SS_PORT, SPI_SS_PIN);
}

void writeToDataFlash(SPI_TypeDef* SPIx, BUFFER_SEL buf1_2, uint16_t buffLocation, char* data, int leng)
{
    if(buf1_2 != 0 && buf1_2 != 1)
    {
        return;   
    }
    
    char writeBufferArray[] = WRITE_BUFFER(0x84, buffLocation);
    int count = 0;
    
    if(buf1_2)
    {
        writeBufferArray[0] = 0x87;
    }
    // Enable the Slave select pin
    GPIO_ResetBits(SPI_SS_PORT, SPI_SS_PIN);
    jbSPISend(SPIx, writeBufferArray, 0x04);  // sends the command, 15 dont care and page location
    jbSPISend(SPIx, data++, leng); // while I have data send it
    GPIO_SetBits(SPI_SS_PORT, SPI_SS_PIN);  // Disable the Slave select pin
}
    
void readSingByteDataFlash(SPI_TypeDef* SPIx, BUFFER_SEL buf1_2, uint16_t buffLocation, unsigned char *saveString, int readSize)
{
    if(buf1_2 != 0 && buf1_2 != 1)
    {
        return;   
    }
    
    char readBufferArray[] = READ_BUFFER(0xD4, buffLocation);
    int count;
    
    if(buf1_2)
    {
        readBufferArray[0] = 0xD6;
    }
    // Enable the slave select pin
    GPIO_ResetBits(SPI_SS_PORT, SPI_SS_PIN);
    jbSPISend(SPIx, readBufferArray, 4);
    jbSPISend(SPIx, (char*)0xFF, 1);
    for(count = 0; count < readSize; count++)
    {
        *saveString++ = jbSPIReceive(SPIx);
    }
    // Disable the slave select pin
    GPIO_SetBits(SPI_SS_PORT, SPI_SS_PIN);
}