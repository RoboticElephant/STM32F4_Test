#include "Communication.h"
/******************************************************************************/
//
// Both I2C functions currently get stuck in an infinite loop if anything doesnt
// work as correctly. For example if during the "I2C_Send7bitAddress" doesnt see
// the desired address it will keep running until it finds it instead of exiting
// out of the program
//
/******************************************************************************/

/********************************************************************************/
//
// USART Functions:
//
/********************************************************************************/

char receiveBuffer[BUF_SIZE];
const char* RXBUFEND = receiveBuffer + BUF_SIZE;

//write to the end, read from the current
volatile char *receiveBufferEnd;
volatile char *receiveBufferCurrent;

void ResetUARTBuffer(void)
{
  receiveBufferCurrent = receiveBufferEnd = receiveBuffer;
  receiveBuffer[0] = '\0';
}

int jbgetcRX(char *rxBuffChar)
{
  if(receiveBufferCurrent < receiveBufferEnd) //checks to see if the buffer being read in is empty. If not it executes the code in the statement.
  {
    *rxBuffChar = *receiveBufferCurrent++;             //this takes the next character in the buffer and passes it back to where it is being read. It also increments the buffer.
    return 1;                                 //The returning of one tells who called it that there was information.
  } else                                      //The else simply states if there is no data return a zero.
  {
    *rxBuffChar = 0;
    return 0;
  }
}

void jbprintf(USART_TypeDef* USARTx, char* txBuffChar)
{
  while(*txBuffChar != '\0')
  {
    while(!(USARTx->SR & 0x00000040));
    USART_SendData(USARTx, *txBuffChar++);
  }
}

/********************************************************************************/
//
// SPI Functions:
//
/********************************************************************************/

void jbSPISend(SPI_TypeDef* SPIx, char* txBuffChar, int leng)
{    
    int count = 0;
    char temp;
    while(count < leng)
    {
        while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE));  // Wait until it resets itself
        SPI_I2S_SendData(SPIx, *txBuffChar++);
        while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));
        temp = SPI_I2S_ReceiveData(SPIx);
        count++;
    }
}

char jbSPIReceive(SPI_TypeDef* SPIx)
{
    while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE));  // Wait until it resets itself
    SPI_I2S_SendData(SPIx, 0x00);
    while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));
    return (char)SPI_I2S_ReceiveData(SPIx);
}

/********************************************************************************/
//
// I2C Functions:
//
/********************************************************************************/

int MasterI2CWrite (I2C_TypeDef* I2Cx, unsigned char address, unsigned char hblb, unsigned char hbyte, unsigned char lbyte, int strLength, unsigned char *saveString)
{
  int count = 0;
  I2C_GenerateSTART(I2Cx, ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  if(hblb != 0)
  {
    I2C_SendData(I2Cx, hbyte);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  I2C_SendData(I2Cx, lbyte);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  while(count < strLength)
  {
    I2C_SendData(I2Cx, *saveString++);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    count++;
  }

  I2C_GenerateSTOP(I2Cx, ENABLE);
  return 0;
}


int MasterI2CRead (I2C_TypeDef* I2Cx, unsigned char address, unsigned char hblb, unsigned char hbyte, unsigned char lbyte, int strLength, unsigned char *saveString)
{
  int count = 0;
  //Sends the start bit and checks to make sure it is sent correctly
  I2C_GenerateSTART(I2Cx, ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
  
  // Sends the address byte and makes sure it is sent correctly
  I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  // If there is a high byte, it will send the high byte and then check to make sure it was sent
  if(hblb != 0)
  {
    I2C_SendData(I2Cx, hbyte);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  I2C_SendData(I2Cx, lbyte);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  //Sends the start bit and checks to make sure it is sent correctly
  I2C_GenerateSTART(I2Cx, ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));

  // Sends the address byte and makes sure it is sent correctly (set up to receive)
  I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  if(strLength > 0)
  {
    while(count < strLength)
    {
      count++;
      if(count != strLength)
      {
        I2C_AcknowledgeConfig(I2Cx, ENABLE);
      } else
      {
        I2C_AcknowledgeConfig(I2Cx, DISABLE);
      }
      while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
      *saveString++ = I2C_ReceiveData(I2Cx);
    }
  }/* else
  {
    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
    *saveString++ = I2C_ReceiveData(I2Cx);
  }*/
  I2C_GenerateSTOP(I2Cx, ENABLE);
  return 0;
}