#include "Hdr.h"
#include "initialization.h"
#include "Communication.h"
//#include "DataFlashSPI.h"
#include "LCD.h"
#include <stdio.h>

#define EEPROMADDR 0xA0

uint32_t	fps=0;
uint32_t	disfps=0;
uint32_t	fpsbuff[5];

void main(void)
{
    debug_printf("hello world\n");
    Initialize();
//    ResetUARTBuffer();    // Reset the buffer for the UART
//    char tempArray[] = "World";
//    char readArray[3];

/*    // Writes and reads from the I2C at the address of EEPROMADDR
    unsigned char highByte = 0x00, lowByte = 0x00, highLowByte = 0x00;
    unsigned char jbSaveString[] = "Hello";
    unsigned char jbReturnString[10];
    MasterI2CWrite(I2C1, EEPROMADDR, highLowByte, highByte, lowByte, sizeof(jbSaveString), jbSaveString);
    MasterI2CRead(I2C1, EEPROMADDR, highLowByte, highByte, lowByte, 5, jbReturnString);
    debug_printf("value is %s\n", jbReturnString);
/**/

/*    //USART3
    jbprintf(USART3, "Hello\n");
*/

/*    // SPI read and write to a DataFlash
    InitDataFlashSPI();
    writeToDataFlash(SPI2, BUFFER_1, 0, tempArray, sizeof(tempArray));
    readSingByteDataFlash(SPI2, BUFFER_1, 0, readArray, sizeof(readArray));
    debug_printf("Character %s\n", readArray);
*/
    
/*    // LCD
    LCDInitialization();
    while(1)
    {
        LCDClear(Red);
        GUIText(132,104,"Josh",White,Red);
        Delay(0x1fffff);	
    
        LCDClear(White);
        GUIText(76,120,"Blakely",Red,White);
        Delay(0x1fffff);	
    
        LCDClear(Black);
        LCDDrawLine(20, 15, 120, 65, Green);
        Delay(0x1fffff);
    }
*/ 

    // LCD w/ Touchpanel Y-Axis Doesn't Work correctly (Possibly broken)
//    int8_t temp[12] = {0};
//    uint16_t tempx = 0, tempy = 0;
//    TouchInitialization();
//    LCDInitialization();
//    LCDClear(Black);
//    TouchPanelCalibrate();
//    Delayms(50);    
//    /* Infinite loop */
//    while (1)
//    {
//        getDisplayPoint(&display, ReadAds7846(), &matrix );
//        debug_printf("%i and %i\n",display.x, display.y);
//        if((tempx != display.x || tempy != display.y)  /*&& (display.x != 0 && display.y != 0)*/)
//        {
//            memset(temp, '\0', sizeof(temp));
//            sprintf(temp, "X:%3d,Y:%3d", display.x, display.y);
//            GUIText(10,10,(uint8_t*)temp, Red, Black);
//            tempx = display.x;
//            tempy = display.y;
//            LCDDrawPoint(tempx, tempy);
//        }	
//    }

    while(1);
}
