#ifndef __LCD_H 
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "Hdr.h"
#include "ASCIILib.h" 

/* Private define ------------------------------------------------------------*/
#define USE_16BIT_PMP

/*********************************************************************
* Overview: Horizontal and vertical display resolution
*                  (from the glass datasheet).
*********************************************************************/
//#define DISP_HOR_RESOLUTION				320
//#define DISP_VER_RESOLUTION				240

#define DISP_ORIENTATION					0
//#define DISP_ORIENTATION					90
//#define DISP_ORIENTATION					180
//#define DISP_ORIENTATION					270

/* Private define ------------------------------------------------------------*/

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  320
#define  MAX_Y  240   

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  240
#define  MAX_Y  320   

#endif

/*********************************************************************
* Overview: Horizontal synchronization timing in pixels
*                  (from the glass datasheet).
*********************************************************************/
//#define DISP_HOR_PULSE_WIDTH		20      /* 20 */
//#define DISP_HOR_BACK_PORCH		51      /* 48 */
//#define DISP_HOR_FRONT_PORCH		20	/* 20 */

/*********************************************************************
* Overview: Vertical synchronization timing in lines
*                  (from the glass datasheet).
*********************************************************************/
//#define DISP_VER_PULSE_WIDTH		2	  /* 2 */
//#define DISP_VER_BACK_PORCH		12	  /* 16 */
//#define DISP_VER_FRONT_PORCH		4	  /* 4 */

/*********************************************************************
* Definition for SPI interface for HIMAX 8238-A relevant to hardware 
* layout; Hardware dependent!
*********************************************************************/
#define GPIO3 3
#define GPIO2 2
#define GPIO1 1
#define GPIO0 0
#define LCD_RESET (1<<GPIO3)	   /* LCD Reset signal (Reset for display panel, NOT ssd1963) */
#define LCD_SPENA (1<<GPIO0)	   /* SPI EN signal */
#define LCD_SPCLK (1<<GPIO1)	   /* SPI CLK */
#define LCD_SPDAT (1<<GPIO2)	   /* SPI DATA */

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define RGB565CONVERT(red, green, blue) (int) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))

/* Private function prototypes -----------------------------------------------*/
void LCDInitialization(void);
void LCDClear(uint16_t Color);	
//void LCD_SetBacklight(uint8_t intensity);
uint16_t LCDGetPoint(uint16_t Xpos,uint16_t Ypos);
void LCDSetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t point);
void PutChar(uint16_t Xpos,uint16_t Ypos,uint8_t c,uint16_t charColor,uint16_t bkColor);
void LCDDrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );
void GUIText(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor);
void LCDDrawPicture(uint16_t StartX,uint16_t StartY,uint16_t EndX,uint16_t EndY,uint16_t *pic);
void LCDDrawPoint(uint16_t Xpos,uint16_t Ypos);
void DrawCross(uint16_t Xpos,uint16_t Ypos);

void PrepareWriteRAM(void);
void LCDWriteIndex(uint16_t index);
void LCDWriteData(uint16_t data);
uint16_t LCDReadData(void);
uint16_t LCDReadReg(uint16_t LCD_Reg);
void LCDWriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue);
void LCDSetCursor(uint16_t Xpos, uint16_t Ypos);

/*******************************************************************************/
//
// Touch Panel
//
// Issues: Y-Axis Doesn't work properly
//
/*******************************************************************************/

#define TP_INT_IN   GPIO_ReadInputDataBit(SPI_SS_PORT_TOUCH, SPI_IRQ_PIN_TOUCH)

#define	CHX 	0x90
#define	CHY 	0xD0
#define THRESHOLD 2
#define SPI_SS_PIN_TOUCH    GPIO_Pin_4
#define SPI_IRQ_PIN_TOUCH   GPIO_Pin_5
#define SPI_SS_PORT_TOUCH   GPIOC
#define SPI_SS_PERIPH_TOUCH RCC_AHB1Periph_GPIOC

typedef	struct POINT 
{
    uint16_t x;
    uint16_t y;
}Coordinate;


typedef struct Matrix 
{						
    long double An,  
                Bn,     
                Cn,   
                Dn,    
                En,    
                Fn,     
                Divider ;
} Matrix ;
        
extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix matrix;
extern Coordinate  display;
    
void TouchInitialization(void);
Coordinate *ReadAds7846(void);
void TouchPanelCalibrate(void);
FunctionalState setCalibrationMatrix( Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
FunctionalState getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
