/* Includes ------------------------------------------------------------------*/
#include "LCD.h"
#include "Hdr.h"
#include "Communication.h"

/* Private define ------------------------------------------------------------*/

#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */

/* Private variables ---------------------------------------------------------*/
static uint8_t LCD_Code;

/* Private define ------------------------------------------------------------*/
#define  ILI9320    0  /* 0x9320 */
#define  ILI9325    1  /* 0x9325 */
#define  ILI9328    2  /* 0x9328 */
#define  ILI9331    3  /* 0x9331 */
#define  SSD1298    4  /* 0x8999 */
#define  SSD1289    5  /* 0x8989 */
#define  ST7781     6  /* 0x7783 */
#define  LGDP4531   7  /* 0x4531 */
#define  SPFD5408B  8  /* 0x5408 */
#define  R61505U    9  /* 0x1505 0x0505 */	   
#define  HX8347D    10 /* 0x0047 */
#define  HX8347A    11 /* 0x0047 */	
#define  LGDP4535   12 /* 0x4535 */  
#define  SSD2119    13 /* 3.5 LCD 0x9919 */

/*******************************************************************************
* Function Name  : LCDInitialization
* Description    : SSD1963 Resets
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
	uint16_t DeviceCode;
	uint16_t i;

void LCDInitialization(void)
{
    DeviceCode = 0x0123;
    DeviceCode = LCDReadReg(0x0000);		/* Read LCD ID	*/	

    if( DeviceCode == 0x9325 || DeviceCode == 0x9328 )	
    {
    LCD_Code = ILI9325;
    LCDWriteReg(0x00e7,0x0010);      
    LCDWriteReg(0x0000,0x0001);  	/* start internal osc */
    LCDWriteReg(0x0001,0x0100);     
    LCDWriteReg(0x0002,0x0700); 	/* power on sequence */
    LCDWriteReg(0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3) ); 	/* importance */
    LCDWriteReg(0x0004,0x0000);                                   
    LCDWriteReg(0x0008,0x0207);	           
    LCDWriteReg(0x0009,0x0000);         
    LCDWriteReg(0x000a,0x0000); 	/* display setting */        
    LCDWriteReg(0x000c,0x0001);	/* display setting */        
    LCDWriteReg(0x000d,0x0000); 			        
    LCDWriteReg(0x000f,0x0000);
    /* Power On sequence */
    LCDWriteReg(0x0010,0x0000);   
    LCDWriteReg(0x0011,0x0007);
    LCDWriteReg(0x0012,0x0000);                                                                 
    LCDWriteReg(0x0013,0x0000);                 
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0010,0x1590);   
    LCDWriteReg(0x0011,0x0227);
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0012,0x009c);                  
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0013,0x1900);   
    LCDWriteReg(0x0029,0x0023);
    LCDWriteReg(0x002b,0x000e);
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0020,0x0000);                                                            
    LCDWriteReg(0x0021,0x0000);           
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0030,0x0007); 
    LCDWriteReg(0x0031,0x0707);   
    LCDWriteReg(0x0032,0x0006);
    LCDWriteReg(0x0035,0x0704);
    LCDWriteReg(0x0036,0x1f04); 
    LCDWriteReg(0x0037,0x0004);
    LCDWriteReg(0x0038,0x0000);        
    LCDWriteReg(0x0039,0x0706);     
    LCDWriteReg(0x003c,0x0701);
    LCDWriteReg(0x003d,0x000f);
    Delayms(50);  /* delay 50 ms */		
    LCDWriteReg(0x0050,0x0000);        
    LCDWriteReg(0x0051,0x00ef);   
    LCDWriteReg(0x0052,0x0000);     
    LCDWriteReg(0x0053,0x013f);
    LCDWriteReg(0x0060,0xa700);        
    LCDWriteReg(0x0061,0x0001); 
    LCDWriteReg(0x006a,0x0000);
    LCDWriteReg(0x0080,0x0000);
    LCDWriteReg(0x0081,0x0000);
    LCDWriteReg(0x0082,0x0000);
    LCDWriteReg(0x0083,0x0000);
    LCDWriteReg(0x0084,0x0000);
    LCDWriteReg(0x0085,0x0000);

    LCDWriteReg(0x0090,0x0010);     
    LCDWriteReg(0x0092,0x0000);  
    LCDWriteReg(0x0093,0x0003);
    LCDWriteReg(0x0095,0x0110);
    LCDWriteReg(0x0097,0x0000);        
    LCDWriteReg(0x0098,0x0000);  
    /* display on sequence */    
    LCDWriteReg(0x0007,0x0133);

    LCDWriteReg(0x0020,0x0000);
    LCDWriteReg(0x0021,0x0000);
    }
    else if( DeviceCode == 0x9320 || DeviceCode == 0x9300 )
    {
        LCD_Code = ILI9320;
        LCDWriteReg(0x00,0x0000);
        LCDWriteReg(0x01,0x0100);	/* Driver Output Contral */
        LCDWriteReg(0x02,0x0700);	/* LCD Driver Waveform Contral */
        LCDWriteReg(0x03,0x1018);	/* Entry Mode Set */

        LCDWriteReg(0x04,0x0000);	/* Scalling Contral */
        LCDWriteReg(0x08,0x0202);	/* Display Contral */
        LCDWriteReg(0x09,0x0000);	/* Display Contral 3.(0x0000) */
        LCDWriteReg(0x0a,0x0000);	/* Frame Cycle Contal.(0x0000) */
        LCDWriteReg(0x0c,(1<<0));	/* Extern Display Interface Contral */
        LCDWriteReg(0x0d,0x0000);	/* Frame Maker Position */
        LCDWriteReg(0x0f,0x0000);	/* Extern Display Interface Contral 2. */

        Delayms(100);  /* delay 100 ms */		
        LCDWriteReg(0x07,0x0101);	/* Display Contral */
        Delayms(100);  /* delay 100 ms */		

        LCDWriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	/* Power Control 1.(0x16b0)	*/
        LCDWriteReg(0x11,0x0007);								/* Power Control 2 */
        LCDWriteReg(0x12,(1<<8)|(1<<4)|(0<<0));				/* Power Control 3.(0x0138)	*/
        LCDWriteReg(0x13,0x0b00);								/* Power Control 4 */
        LCDWriteReg(0x29,0x0000);								/* Power Control 7 */

        LCDWriteReg(0x2b,(1<<14)|(1<<4));

        LCDWriteReg(0x50,0);       /* Set X Start */
        LCDWriteReg(0x51,239);	    /* Set X End */
        LCDWriteReg(0x52,0);	    /* Set Y Start */
        LCDWriteReg(0x53,319);	    /* Set Y End */

        LCDWriteReg(0x60,0x2700);	/* Driver Output Control */
        LCDWriteReg(0x61,0x0001);	/* Driver Output Control */
        LCDWriteReg(0x6a,0x0000);	/* Vertical Srcoll Control */

        LCDWriteReg(0x80,0x0000);	/* Display Position? Partial Display 1 */
        LCDWriteReg(0x81,0x0000);	/* RAM Address Start? Partial Display 1 */
        LCDWriteReg(0x82,0x0000);	/* RAM Address End-Partial Display 1 */
        LCDWriteReg(0x83,0x0000);	/* Displsy Position? Partial Display 2 */
        LCDWriteReg(0x84,0x0000);	/* RAM Address Start? Partial Display 2 */
        LCDWriteReg(0x85,0x0000);	/* RAM Address End? Partial Display 2 */

        LCDWriteReg(0x90,(0<<7)|(16<<0));	/* Frame Cycle Contral.(0x0013)	*/
        LCDWriteReg(0x92,0x0000);	/* Panel Interface Contral 2.(0x0000) */
        LCDWriteReg(0x93,0x0001);	/* Panel Interface Contral 3. */
        LCDWriteReg(0x95,0x0110);	/* Frame Cycle Contral.(0x0110)	*/
        LCDWriteReg(0x97,(0<<8));	
        LCDWriteReg(0x98,0x0000);	/* Frame Cycle Contral */

        LCDWriteReg(0x07,0x0173);
    }
    else if( DeviceCode == 0x9331 )
    {
        LCD_Code = ILI9331;
        LCDWriteReg(0x00E7, 0x1014);
        LCDWriteReg(0x0001, 0x0100);   /* set SS and SM bit */
        LCDWriteReg(0x0002, 0x0200);   /* set 1 line inversion */
        LCDWriteReg(0x0003, 0x1030);   /* set GRAM write direction and BGR=1 */
        LCDWriteReg(0x0008, 0x0202);   /* set the back porch and front porch */
        LCDWriteReg(0x0009, 0x0000);   /* set non-display area refresh cycle ISC[3:0] */
        LCDWriteReg(0x000A, 0x0000);   /* FMARK function */
        LCDWriteReg(0x000C, 0x0000);   /* RGB interface setting */
        LCDWriteReg(0x000D, 0x0000);   /* Frame marker Position */
        LCDWriteReg(0x000F, 0x0000);   /* RGB interface polarity */
        /* Power On sequence */
        LCDWriteReg(0x0010, 0x0000);   /* SAP, BT[3:0], AP, DSTB, SLP, STB	*/
        LCDWriteReg(0x0011, 0x0007);   /* DC1[2:0], DC0[2:0], VC[2:0] */
        LCDWriteReg(0x0012, 0x0000);   /* VREG1OUT voltage	*/
        LCDWriteReg(0x0013, 0x0000);   /* VDV[4:0] for VCOM amplitude */
        Delayms(200);  /* delay 200 ms */		
        LCDWriteReg(0x0010, 0x1690);   /* SAP, BT[3:0], AP, DSTB, SLP, STB	*/
        LCDWriteReg(0x0011, 0x0227);   /* DC1[2:0], DC0[2:0], VC[2:0] */
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0012, 0x000C);   /* Internal reference voltage= Vci	*/
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0013, 0x0800);   /* Set VDV[4:0] for VCOM amplitude */
        LCDWriteReg(0x0029, 0x0011);   /* Set VCM[5:0] for VCOMH */
        LCDWriteReg(0x002B, 0x000B);   /* Set Frame Rate */
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0020, 0x0000);   /* GRAM horizontal Address */
        LCDWriteReg(0x0021, 0x0000);   /* GRAM Vertical Address */
        /* Adjust the Gamma Curve */
        LCDWriteReg(0x0030, 0x0000);
        LCDWriteReg(0x0031, 0x0106);
        LCDWriteReg(0x0032, 0x0000);
        LCDWriteReg(0x0035, 0x0204);
        LCDWriteReg(0x0036, 0x160A);
        LCDWriteReg(0x0037, 0x0707);
        LCDWriteReg(0x0038, 0x0106);
        LCDWriteReg(0x0039, 0x0707);
        LCDWriteReg(0x003C, 0x0402);
        LCDWriteReg(0x003D, 0x0C0F);
        /* Set GRAM area */
        LCDWriteReg(0x0050, 0x0000);   /* Horizontal GRAM Start Address */
        LCDWriteReg(0x0051, 0x00EF);   /* Horizontal GRAM End Address */
        LCDWriteReg(0x0052, 0x0000);   /* Vertical GRAM Start Address */
        LCDWriteReg(0x0053, 0x013F);   /* Vertical GRAM Start Address */
        LCDWriteReg(0x0060, 0x2700);   /* Gate Scan Line */
        LCDWriteReg(0x0061, 0x0001);   /*  NDL,VLE, REV */
        LCDWriteReg(0x006A, 0x0000);   /* set scrolling line */
        /* Partial Display Control */
        LCDWriteReg(0x0080, 0x0000);
        LCDWriteReg(0x0081, 0x0000);
        LCDWriteReg(0x0082, 0x0000);
        LCDWriteReg(0x0083, 0x0000);
        LCDWriteReg(0x0084, 0x0000);
        LCDWriteReg(0x0085, 0x0000);
        /* Panel Control */
        LCDWriteReg(0x0090, 0x0010);
        LCDWriteReg(0x0092, 0x0600);
        LCDWriteReg(0x0007,0x0021);		
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0007,0x0061);
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0007,0x0133);    /* 262K color and display ON */
    }
    else if( DeviceCode == 0x9919 )
    {
        LCD_Code = SSD2119;
        /* POWER ON &RESET DISPLAY OFF */
        LCDWriteReg(0x28,0x0006);
        LCDWriteReg(0x00,0x0001);		
        LCDWriteReg(0x10,0x0000);		
        LCDWriteReg(0x01,0x72ef);
        LCDWriteReg(0x02,0x0600);
        LCDWriteReg(0x03,0x6a38);	
        LCDWriteReg(0x11,0x6874);
        LCDWriteReg(0x0f,0x0000);    /* RAM WRITE DATA MASK */
        LCDWriteReg(0x0b,0x5308);    /* RAM WRITE DATA MASK */
        LCDWriteReg(0x0c,0x0003);
        LCDWriteReg(0x0d,0x000a);
        LCDWriteReg(0x0e,0x2e00);  
        LCDWriteReg(0x1e,0x00be);
        LCDWriteReg(0x25,0x8000);
        LCDWriteReg(0x26,0x7800);
        LCDWriteReg(0x27,0x0078);
        LCDWriteReg(0x4e,0x0000);
        LCDWriteReg(0x4f,0x0000);
        LCDWriteReg(0x12,0x08d9);
        /* Adjust the Gamma Curve */
        LCDWriteReg(0x30,0x0000);
        LCDWriteReg(0x31,0x0104);	 
        LCDWriteReg(0x32,0x0100);	
        LCDWriteReg(0x33,0x0305);	
        LCDWriteReg(0x34,0x0505);	 
        LCDWriteReg(0x35,0x0305);	
        LCDWriteReg(0x36,0x0707);	
        LCDWriteReg(0x37,0x0300);	
        LCDWriteReg(0x3a,0x1200);	
        LCDWriteReg(0x3b,0x0800);		 
        LCDWriteReg(0x07,0x0033);
    }
    else if( DeviceCode == 0x1505 || DeviceCode == 0x0505 )
    {
        LCD_Code = R61505U;
        /* second release on 3/5  ,luminance is acceptable,water wave appear during camera preview */
        LCDWriteReg(0x0007,0x0000);
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0012,0x011C);    /* why need to set several times?	*/
        LCDWriteReg(0x00A4,0x0001);    /* NVM */
        LCDWriteReg(0x0008,0x000F);
        LCDWriteReg(0x000A,0x0008);
        LCDWriteReg(0x000D,0x0008);    
        /* GAMMA CONTROL */
        LCDWriteReg(0x0030,0x0707);
        LCDWriteReg(0x0031,0x0007); 
        LCDWriteReg(0x0032,0x0603); 
        LCDWriteReg(0x0033,0x0700); 
        LCDWriteReg(0x0034,0x0202); 
        LCDWriteReg(0x0035,0x0002); 
        LCDWriteReg(0x0036,0x1F0F);
        LCDWriteReg(0x0037,0x0707); 
        LCDWriteReg(0x0038,0x0000); 
        LCDWriteReg(0x0039,0x0000); 
        LCDWriteReg(0x003A,0x0707); 
        LCDWriteReg(0x003B,0x0000); 
        LCDWriteReg(0x003C,0x0007); 
        LCDWriteReg(0x003D,0x0000); 
        Delayms(50);  /* delay 50 ms */		
        LCDWriteReg(0x0007,0x0001);
        LCDWriteReg(0x0017,0x0001);    /* Power supply startup enable */
        Delayms(50);  /* delay 50 ms */		
        /* power control */
        LCDWriteReg(0x0010,0x17A0); 
        LCDWriteReg(0x0011,0x0217);    /* reference voltage VC[2:0]   Vciout = 1.00*Vcivl */
        LCDWriteReg(0x0012,0x011E);    /* Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?	*/
        LCDWriteReg(0x0013,0x0F00);    /* VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl */
        LCDWriteReg(0x002A,0x0000);  
        LCDWriteReg(0x0029,0x000A);    /* Vcomh = VCM1[4:0]*Vreg1out    gate source voltage?? */
        LCDWriteReg(0x0012,0x013E);    /* power supply on */
        /* Coordinates Control */
        LCDWriteReg(0x0050,0x0000);
        LCDWriteReg(0x0051,0x00EF); 
        LCDWriteReg(0x0052,0x0000); 
        LCDWriteReg(0x0053,0x013F); 
        /* Pannel Image Control */
        LCDWriteReg(0x0060,0x2700); 
        LCDWriteReg(0x0061,0x0001); 
        LCDWriteReg(0x006A,0x0000); 
        LCDWriteReg(0x0080,0x0000); 
        /* Partial Image Control */
        LCDWriteReg(0x0081,0x0000); 
        LCDWriteReg(0x0082,0x0000); 
        LCDWriteReg(0x0083,0x0000); 
        LCDWriteReg(0x0084,0x0000); 
        LCDWriteReg(0x0085,0x0000); 
        /* Panel Interface Control */
        LCDWriteReg(0x0090,0x0013);      /* frenqucy */	
        LCDWriteReg(0x0092,0x0300); 
        LCDWriteReg(0x0093,0x0005); 
        LCDWriteReg(0x0095,0x0000); 
        LCDWriteReg(0x0097,0x0000); 
        LCDWriteReg(0x0098,0x0000); 

        LCDWriteReg(0x0001,0x0100); 
        LCDWriteReg(0x0002,0x0700); 
        LCDWriteReg(0x0003,0x1030); 
        LCDWriteReg(0x0004,0x0000); 
        LCDWriteReg(0x000C,0x0000); 
        LCDWriteReg(0x000F,0x0000); 
        LCDWriteReg(0x0020,0x0000); 
        LCDWriteReg(0x0021,0x0000); 
        LCDWriteReg(0x0007,0x0021); 
        Delayms(200);  /* delay 200 ms */		
        LCDWriteReg(0x0007,0x0061); 
        Delayms(200);  /* delay 200 ms */		
        LCDWriteReg(0x0007,0x0173); 
    }							 
    else if( DeviceCode == 0x8989 )
    {
        LCD_Code = SSD1289;
        LCDWriteReg(0x0000,0x0001);    Delayms(50);   /* Enable LCD Oscillator */
        LCDWriteReg(0x0003,0xA8A4);    Delayms(50);   
        LCDWriteReg(0x000C,0x0000);    Delayms(50);   
        LCDWriteReg(0x000D,0x080C);    Delayms(50);   
        LCDWriteReg(0x000E,0x2B00);    Delayms(50);   
        LCDWriteReg(0x001E,0x00B0);    Delayms(50);   
        LCDWriteReg(0x0001,0x2B3F);    Delayms(50);   /* 320*240 0x2B3F */
        LCDWriteReg(0x0002,0x0600);    Delayms(50);
        LCDWriteReg(0x0010,0x0000);    Delayms(50);
        LCDWriteReg(0x0011,0x6070);    Delayms(50);
        LCDWriteReg(0x0005,0x0000);    Delayms(50);
        LCDWriteReg(0x0006,0x0000);    Delayms(50);
        LCDWriteReg(0x0016,0xEF1C);    Delayms(50);
        LCDWriteReg(0x0017,0x0003);    Delayms(50);
        LCDWriteReg(0x0007,0x0133);    Delayms(50);         
        LCDWriteReg(0x000B,0x0000);    Delayms(50);
        LCDWriteReg(0x000F,0x0000);    Delayms(50);
        LCDWriteReg(0x0041,0x0000);    Delayms(50);
        LCDWriteReg(0x0042,0x0000);    Delayms(50);
        LCDWriteReg(0x0048,0x0000);    Delayms(50);
        LCDWriteReg(0x0049,0x013F);    Delayms(50);
        LCDWriteReg(0x004A,0x0000);    Delayms(50);
        LCDWriteReg(0x004B,0x0000);    Delayms(50);
        LCDWriteReg(0x0044,0xEF00);    Delayms(50);
        LCDWriteReg(0x0045,0x0000);    Delayms(50);
        LCDWriteReg(0x0046,0x013F);    Delayms(50);
        LCDWriteReg(0x0030,0x0707);    Delayms(50);
        LCDWriteReg(0x0031,0x0204);    Delayms(50);
        LCDWriteReg(0x0032,0x0204);    Delayms(50);
        LCDWriteReg(0x0033,0x0502);    Delayms(50);
        LCDWriteReg(0x0034,0x0507);    Delayms(50);
        LCDWriteReg(0x0035,0x0204);    Delayms(50);
        LCDWriteReg(0x0036,0x0204);    Delayms(50);
        LCDWriteReg(0x0037,0x0502);    Delayms(50);
        LCDWriteReg(0x003A,0x0302);    Delayms(50);
        LCDWriteReg(0x003B,0x0302);    Delayms(50);
        LCDWriteReg(0x0023,0x0000);    Delayms(50);
        LCDWriteReg(0x0024,0x0000);    Delayms(50);
        LCDWriteReg(0x0025,0x8000);    Delayms(50);
        LCDWriteReg(0x004f,0);
        LCDWriteReg(0x004e,0);
        LCDWriteReg(0x0011,0x6068);
    }
    else if( DeviceCode == 0x8999 )
    {
        LCD_Code = SSD1298;		
        LCDWriteReg(0x0028,0x0006);
        LCDWriteReg(0x0000,0x0001);
        LCDWriteReg(0x0003,0xaea4);    /* power control 1---line frequency and VHG,VGL voltage */
        LCDWriteReg(0x000c,0x0004);    /* power control 2---VCIX2 output voltage */
        LCDWriteReg(0x000d,0x000c);    /* power control 3---Vlcd63 voltage */
        LCDWriteReg(0x000e,0x2800);    /* power control 4---VCOMA voltage VCOML=VCOMH*0.9475-VCOMA */
        LCDWriteReg(0x001e,0x00b5);    /* POWER CONTROL 5---VCOMH voltage */   
        LCDWriteReg(0x0001,0x3b3f);     
        LCDWriteReg(0x0002,0x0600);
        LCDWriteReg(0x0010,0x0000);
        LCDWriteReg(0x0011,0x6830);
        LCDWriteReg(0x0005,0x0000);
        LCDWriteReg(0x0006,0x0000);
        LCDWriteReg(0x0016,0xef1c);  
        LCDWriteReg(0x0007,0x0033);    /* Display control 1 */
        /* when GON=1 and DTE=0,all gate outputs become VGL */
        /* when GON=1 and DTE=0,all gate outputs become VGH */
        /* non-selected gate wires become VGL */     
        LCDWriteReg(0x000b,0x0000);
        LCDWriteReg(0x000f,0x0000);
        LCDWriteReg(0x0041,0x0000);
        LCDWriteReg(0x0042,0x0000);
        LCDWriteReg(0x0048,0x0000);
        LCDWriteReg(0x0049,0x013f);
        LCDWriteReg(0x004a,0x0000);
        LCDWriteReg(0x004b,0x0000); 
        LCDWriteReg(0x0044,0xef00);	/* Horizontal RAM start and end address */
        LCDWriteReg(0x0045,0x0000);	/* Vretical RAM start address */
        LCDWriteReg(0x0046,0x013f);	/* Vretical RAM end address */ 
        LCDWriteReg(0x004e,0x0000);	/* set GDDRAM x address counter */
        LCDWriteReg(0x004f,0x0000);    /* set GDDRAM y address counter */   
        /* y control */
        LCDWriteReg(0x0030,0x0707);
        LCDWriteReg(0x0031,0x0202);
        LCDWriteReg(0x0032,0x0204);
        LCDWriteReg(0x0033,0x0502);
        LCDWriteReg(0x0034,0x0507);
        LCDWriteReg(0x0035,0x0204);
        LCDWriteReg(0x0036,0x0204);
        LCDWriteReg(0x0037,0x0502);
        LCDWriteReg(0x003a,0x0302);
        LCDWriteReg(0x003b,0x0302); 
        LCDWriteReg(0x0023,0x0000);
        LCDWriteReg(0x0024,0x0000);
        LCDWriteReg(0x0025,0x8000);
        LCDWriteReg(0x0026,0x7000);
        LCDWriteReg(0x0020,0xb0eb);
        LCDWriteReg(0x0027,0x007c);
    }
    else if( DeviceCode == 0x5408 )
    {
        LCD_Code = SPFD5408B;

        LCDWriteReg(0x0001,0x0100);	  /* Driver Output Contral Register */ 
        LCDWriteReg(0x0002,0x0700);      /* LCD Driving Waveform Contral */
        LCDWriteReg(0x0003,0x1030);

        LCDWriteReg(0x0004,0x0000);	  /* Scalling Control register */
        LCDWriteReg(0x0008,0x0207);	  /* Display Control 2 */
        LCDWriteReg(0x0009,0x0000);	  /* Display Control 3 */
        LCDWriteReg(0x000A,0x0000);	  /* Frame Cycle Control */
        LCDWriteReg(0x000C,0x0000);	  /* External Display Interface Control 1 */
        LCDWriteReg(0x000D,0x0000);      /* Frame Maker Position */
        LCDWriteReg(0x000F,0x0000);	  /* External Display Interface Control 2 */
        Delayms(50);
        LCDWriteReg(0x0007,0x0101);	  /* Display Control */
        Delayms(50);
        LCDWriteReg(0x0010,0x16B0);      /* Power Control 1 */
        LCDWriteReg(0x0011,0x0001);      /* Power Control 2 */
        LCDWriteReg(0x0017,0x0001);      /* Power Control 3 */
        LCDWriteReg(0x0012,0x0138);      /* Power Control 4 */
        LCDWriteReg(0x0013,0x0800);      /* Power Control 5 */
        LCDWriteReg(0x0029,0x0009);	  /* NVM read data 2 */
        LCDWriteReg(0x002a,0x0009);	  /* NVM read data 3 */
        LCDWriteReg(0x00a4,0x0000);  
        LCDWriteReg(0x0050,0x0000);
        LCDWriteReg(0x0051,0x00EF);
        LCDWriteReg(0x0052,0x0000);
        LCDWriteReg(0x0053,0x013F);

        LCDWriteReg(0x0060,0x2700);	  /* Driver Output Control */

        LCDWriteReg(0x0061,0x0003);	  /* Driver Output Control */
        LCDWriteReg(0x006A,0x0000);	  /* Vertical Scroll Control */

        LCDWriteReg(0x0080,0x0000);	  /* Display Position šC Partial Display 1 */
        LCDWriteReg(0x0081,0x0000);	  /* RAM Address Start šC Partial Display 1 */
        LCDWriteReg(0x0082,0x0000);	  /* RAM address End - Partial Display 1 */
        LCDWriteReg(0x0083,0x0000);	  /* Display Position šC Partial Display 2 */
        LCDWriteReg(0x0084,0x0000);	  /* RAM Address Start šC Partial Display 2 */
        LCDWriteReg(0x0085,0x0000);	  /* RAM address End šC Partail Display2 */
        LCDWriteReg(0x0090,0x0013);	  /* Frame Cycle Control */
        LCDWriteReg(0x0092,0x0000); 	  /* Panel Interface Control 2 */
        LCDWriteReg(0x0093,0x0003);	  /* Panel Interface control 3 */
        LCDWriteReg(0x0095,0x0110);	  /* Frame Cycle Control */
        LCDWriteReg(0x0007,0x0173);
    }
    else if( DeviceCode == 0x4531 )
    {	
        LCD_Code = LGDP4531;
        /* Setup display */
        LCDWriteReg(0x00,0x0001);
        LCDWriteReg(0x10,0x0628);
        LCDWriteReg(0x12,0x0006);
        LCDWriteReg(0x13,0x0A32);
        LCDWriteReg(0x11,0x0040);
        LCDWriteReg(0x15,0x0050);
        LCDWriteReg(0x12,0x0016);
        Delayms(50);
        LCDWriteReg(0x10,0x5660);
        Delayms(50);
        LCDWriteReg(0x13,0x2A4E);
        LCDWriteReg(0x01,0x0100);
        LCDWriteReg(0x02,0x0300);	
        LCDWriteReg(0x03,0x1030);		
        LCDWriteReg(0x08,0x0202);
        LCDWriteReg(0x0A,0x0000);
        LCDWriteReg(0x30,0x0000);
        LCDWriteReg(0x31,0x0402);
        LCDWriteReg(0x32,0x0106);
        LCDWriteReg(0x33,0x0700);
        LCDWriteReg(0x34,0x0104);
        LCDWriteReg(0x35,0x0301);
        LCDWriteReg(0x36,0x0707);
        LCDWriteReg(0x37,0x0305);
        LCDWriteReg(0x38,0x0208);
        LCDWriteReg(0x39,0x0F0B);
        Delayms(50);
        LCDWriteReg(0x41,0x0002);
        LCDWriteReg(0x60,0x2700);
        LCDWriteReg(0x61,0x0001);
        LCDWriteReg(0x90,0x0119);
        LCDWriteReg(0x92,0x010A);
        LCDWriteReg(0x93,0x0004);
        LCDWriteReg(0xA0,0x0100);
        Delayms(50);
        LCDWriteReg(0x07,0x0133);
        Delayms(50);
        LCDWriteReg(0xA0,0x0000);
    }
    else if( DeviceCode == 0x4535 )
    {	
        LCD_Code = LGDP4535;	
        LCDWriteReg(0x15, 0x0030); 	 /* Set the internal vcore voltage */                                              
        LCDWriteReg(0x9A, 0x0010); 	 /* Start internal OSC */
        LCDWriteReg(0x11, 0x0020);	     /* set SS and SM bit */
        LCDWriteReg(0x10, 0x3428);	     /* set 1 line inversion */
        LCDWriteReg(0x12, 0x0002);	     /* set GRAM write direction and BGR=1 */ 
        LCDWriteReg(0x13, 0x1038);	     /* Resize register */
        Delayms(40); 
        LCDWriteReg(0x12, 0x0012);	     /* set the back porch and front porch */
        Delayms(40); 
        LCDWriteReg(0x10, 0x3420);	     /* set non-display area refresh cycle ISC[3:0] */
        LCDWriteReg(0x13, 0x3045);	     /* FMARK function */
        Delayms(70); 
        LCDWriteReg(0x30, 0x0000);      /* RGB interface setting */
        LCDWriteReg(0x31, 0x0402);	     /* Frame marker Position */
        LCDWriteReg(0x32, 0x0307);      /* RGB interface polarity */
        LCDWriteReg(0x33, 0x0304);      /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCDWriteReg(0x34, 0x0004);      /* DC1[2:0], DC0[2:0], VC[2:0] */
        LCDWriteReg(0x35, 0x0401);      /* VREG1OUT voltage */
        LCDWriteReg(0x36, 0x0707);      /* VDV[4:0] for VCOM amplitude */
        LCDWriteReg(0x37, 0x0305);      /* SAP, BT[3:0], AP, DSTB, SLP, STB */
        LCDWriteReg(0x38, 0x0610);      /* DC1[2:0], DC0[2:0], VC[2:0] */
        LCDWriteReg(0x39, 0x0610);      /* VREG1OUT voltage */
        LCDWriteReg(0x01, 0x0100);      /* VDV[4:0] for VCOM amplitude */
        LCDWriteReg(0x02, 0x0300);      /* VCM[4:0] for VCOMH */
        LCDWriteReg(0x03, 0x1030);      /* GRAM horizontal Address */
        LCDWriteReg(0x08, 0x0808);      /* GRAM Vertical Address */
        LCDWriteReg(0x0A, 0x0008);		
        LCDWriteReg(0x60, 0x2700);	     /* Gate Scan Line */
        LCDWriteReg(0x61, 0x0001);	     /* NDL,VLE, REV */
        LCDWriteReg(0x90, 0x013E);
        LCDWriteReg(0x92, 0x0100);
        LCDWriteReg(0x93, 0x0100);
        LCDWriteReg(0xA0, 0x3000);
        LCDWriteReg(0xA3, 0x0010);
        LCDWriteReg(0x07, 0x0001);
        LCDWriteReg(0x07, 0x0021);
        LCDWriteReg(0x07, 0x0023);
        LCDWriteReg(0x07, 0x0033);
        LCDWriteReg(0x07, 0x0133);
    } 		 		
    else if( DeviceCode == 0x0047 )
    {
        LCD_Code = HX8347D;
        /* Start Initial Sequence */
        LCDWriteReg(0xEA,0x00);                          
        LCDWriteReg(0xEB,0x20);                                                     
        LCDWriteReg(0xEC,0x0C);                                                   
        LCDWriteReg(0xED,0xC4);                                                    
        LCDWriteReg(0xE8,0x40);                                                     
        LCDWriteReg(0xE9,0x38);                                                    
        LCDWriteReg(0xF1,0x01);                                                    
        LCDWriteReg(0xF2,0x10);                                                    
        LCDWriteReg(0x27,0xA3);                                                    
        /* GAMMA SETTING */
        LCDWriteReg(0x40,0x01);                           
        LCDWriteReg(0x41,0x00);                                                   
        LCDWriteReg(0x42,0x00);                                                   
        LCDWriteReg(0x43,0x10);                                                    
        LCDWriteReg(0x44,0x0E);                                                   
        LCDWriteReg(0x45,0x24);                                                  
        LCDWriteReg(0x46,0x04);                                                  
        LCDWriteReg(0x47,0x50);                                                   
        LCDWriteReg(0x48,0x02);                                                    
        LCDWriteReg(0x49,0x13);                                                  
        LCDWriteReg(0x4A,0x19);                                                  
        LCDWriteReg(0x4B,0x19);                                                 
        LCDWriteReg(0x4C,0x16);                                                 
        LCDWriteReg(0x50,0x1B);                                                   
        LCDWriteReg(0x51,0x31);                                                    
        LCDWriteReg(0x52,0x2F);                                                     
        LCDWriteReg(0x53,0x3F);                                                    
        LCDWriteReg(0x54,0x3F);                                                     
        LCDWriteReg(0x55,0x3E);                                                     
        LCDWriteReg(0x56,0x2F);                                                   
        LCDWriteReg(0x57,0x7B);                                                     
        LCDWriteReg(0x58,0x09);                                                  
        LCDWriteReg(0x59,0x06);                                                 
        LCDWriteReg(0x5A,0x06);                                                   
        LCDWriteReg(0x5B,0x0C);                                                   
        LCDWriteReg(0x5C,0x1D);                                                   
        LCDWriteReg(0x5D,0xCC);                                                   
        /* Power Voltage Setting */
        LCDWriteReg(0x1B,0x18);                                                    
        LCDWriteReg(0x1A,0x01);                                                    
        LCDWriteReg(0x24,0x15);                                                    
        LCDWriteReg(0x25,0x50);                                                    
        LCDWriteReg(0x23,0x8B);                                                   
        LCDWriteReg(0x18,0x36);                           
        LCDWriteReg(0x19,0x01);                                                    
        LCDWriteReg(0x01,0x00);                                                   
        LCDWriteReg(0x1F,0x88);                                                    
        Delayms(50);
        LCDWriteReg(0x1F,0x80);                                                  
        Delayms(50);
        LCDWriteReg(0x1F,0x90);                                                   
        Delayms(50);
        LCDWriteReg(0x1F,0xD0);                                                   
        Delayms(50);
        LCDWriteReg(0x17,0x05);                                                    
        LCDWriteReg(0x36,0x00);                                                    
        LCDWriteReg(0x28,0x38);                                                 
        Delayms(50);
        LCDWriteReg(0x28,0x3C);                                                
    }
    else if( DeviceCode == 0x7783 )
    {
        LCD_Code = ST7781;
        /* Start Initial Sequence */
        LCDWriteReg(0x00FF,0x0001);
        LCDWriteReg(0x00F3,0x0008);
        LCDWriteReg(0x0001,0x0100);
        LCDWriteReg(0x0002,0x0700);
        LCDWriteReg(0x0003,0x1030);  
        LCDWriteReg(0x0008,0x0302);
        LCDWriteReg(0x0008,0x0207);
        LCDWriteReg(0x0009,0x0000);
        LCDWriteReg(0x000A,0x0000);
        LCDWriteReg(0x0010,0x0000);  
        LCDWriteReg(0x0011,0x0005);
        LCDWriteReg(0x0012,0x0000);
        LCDWriteReg(0x0013,0x0000);
        Delayms(50);
        LCDWriteReg(0x0010,0x12B0);
        Delayms(50);
        LCDWriteReg(0x0011,0x0007);
        Delayms(50);
        LCDWriteReg(0x0012,0x008B);
        Delayms(50);	
        LCDWriteReg(0x0013,0x1700);
        Delayms(50);	
        LCDWriteReg(0x0029,0x0022);		
        LCDWriteReg(0x0030,0x0000);
        LCDWriteReg(0x0031,0x0707);
        LCDWriteReg(0x0032,0x0505);
        LCDWriteReg(0x0035,0x0107);
        LCDWriteReg(0x0036,0x0008);
        LCDWriteReg(0x0037,0x0000);
        LCDWriteReg(0x0038,0x0202);
        LCDWriteReg(0x0039,0x0106);
        LCDWriteReg(0x003C,0x0202);
        LCDWriteReg(0x003D,0x0408);
        Delayms(50);				
        LCDWriteReg(0x0050,0x0000);		
        LCDWriteReg(0x0051,0x00EF);		
        LCDWriteReg(0x0052,0x0000);		
        LCDWriteReg(0x0053,0x013F);		
        LCDWriteReg(0x0060,0xA700);		
        LCDWriteReg(0x0061,0x0001);
        LCDWriteReg(0x0090,0x0033);				
        LCDWriteReg(0x002B,0x000B);		
        LCDWriteReg(0x0007,0x0133);
    }
    else	/* special ID */
    {
        DeviceCode = 0x0123;
        DeviceCode = LCDReadReg(0x67);
        if( DeviceCode == 0x0047 )
        {
            LCD_Code = HX8347A;
            LCDWriteReg(0x0042,0x0008);   
            /* Gamma setting */  
            LCDWriteReg(0x0046,0x00B4); 
            LCDWriteReg(0x0047,0x0043); 
            LCDWriteReg(0x0048,0x0013); 
            LCDWriteReg(0x0049,0x0047); 
            LCDWriteReg(0x004A,0x0014); 
            LCDWriteReg(0x004B,0x0036); 
            LCDWriteReg(0x004C,0x0003); 
            LCDWriteReg(0x004D,0x0046); 
            LCDWriteReg(0x004E,0x0005);  
            LCDWriteReg(0x004F,0x0010);  
            LCDWriteReg(0x0050,0x0008);  
            LCDWriteReg(0x0051,0x000a);  
            /* Window Setting */
            LCDWriteReg(0x0002,0x0000); 
            LCDWriteReg(0x0003,0x0000); 
            LCDWriteReg(0x0004,0x0000); 
            LCDWriteReg(0x0005,0x00EF); 
            LCDWriteReg(0x0006,0x0000); 
            LCDWriteReg(0x0007,0x0000); 
            LCDWriteReg(0x0008,0x0001); 
            LCDWriteReg(0x0009,0x003F); 
            Delayms(10); 
            LCDWriteReg(0x0001,0x0006); 
            LCDWriteReg(0x0016,0x00C8);   
            LCDWriteReg(0x0023,0x0095); 
            LCDWriteReg(0x0024,0x0095); 
            LCDWriteReg(0x0025,0x00FF); 
            LCDWriteReg(0x0027,0x0002); 
            LCDWriteReg(0x0028,0x0002); 
            LCDWriteReg(0x0029,0x0002); 
            LCDWriteReg(0x002A,0x0002); 
            LCDWriteReg(0x002C,0x0002); 
            LCDWriteReg(0x002D,0x0002); 
            LCDWriteReg(0x003A,0x0001);  
            LCDWriteReg(0x003B,0x0001);  
            LCDWriteReg(0x003C,0x00F0);    
            LCDWriteReg(0x003D,0x0000); 
            Delayms(20); 
            LCDWriteReg(0x0035,0x0038); 
            LCDWriteReg(0x0036,0x0078); 
            LCDWriteReg(0x003E,0x0038); 
            LCDWriteReg(0x0040,0x000F); 
            LCDWriteReg(0x0041,0x00F0);  
            LCDWriteReg(0x0038,0x0000); 
            /* Power Setting */ 
            LCDWriteReg(0x0019,0x0049);  
            LCDWriteReg(0x0093,0x000A); 
            Delayms(10); 
            LCDWriteReg(0x0020,0x0020);   
            LCDWriteReg(0x001D,0x0003);   
            LCDWriteReg(0x001E,0x0000);  
            LCDWriteReg(0x001F,0x0009);   
            LCDWriteReg(0x0044,0x0053);  
            LCDWriteReg(0x0045,0x0010);   
            Delayms(10);  
            LCDWriteReg(0x001C,0x0004);  
            Delayms(20); 
            LCDWriteReg(0x0043,0x0080);    
            Delayms(5); 
            LCDWriteReg(0x001B,0x000a);    
            Delayms(40);  
            LCDWriteReg(0x001B,0x0012);    
            Delayms(40);   
            /* Display On Setting */ 
            LCDWriteReg(0x0090,0x007F); 
            LCDWriteReg(0x0026,0x0004); 
            Delayms(40);  
            LCDWriteReg(0x0026,0x0024); 
            LCDWriteReg(0x0026,0x002C); 
            Delayms(40);   
            LCDWriteReg(0x0070,0x0008); 
            LCDWriteReg(0x0026,0x003C);  
            LCDWriteReg(0x0057,0x0002); 
            LCDWriteReg(0x0055,0x0000); 
            LCDWriteReg(0x0057,0x0000); 
        }	 
    }  						
    Delayms(50);   /* delay 50 ms */		
}

/*******************************************************************************
* Function Name  : LCDClear
* Description    : 
* Input          : - Color: Screen Color
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDClear(uint16_t Color)
{
    uint32_t index=0;

    if( LCD_Code == HX8347D || LCD_Code == HX8347A )
    {
        LCDWriteReg(0x02,0x00);                                                  
        LCDWriteReg(0x03,0x00);  
            
        LCDWriteReg(0x04,0x00);                           
        LCDWriteReg(0x05,0xEF);  
             
        LCDWriteReg(0x06,0x00);                           
        LCDWriteReg(0x07,0x00);    
           
        LCDWriteReg(0x08,0x01);                           
        LCDWriteReg(0x09,0x3F);     
    }
    else
    {	
        LCDSetCursor(0,0); 
    }	

    LCDWriteIndex(0x0022);
    for( index = 0; index < MAX_X * MAX_Y; index++ )
    {
        LCDWriteData(Color);
    }

}

void LCDSetCursor( uint16_t Xpos, uint16_t Ypos )
{				   
#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

    uint16_t temp = Xpos;

    Xpos = Ypos;
    Ypos = ( MAX_X - 1 ) - temp;  

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#endif

    switch( LCD_Code )
    {
        default:		 /* 0x9320 0x9325 0x9328 0x9331 0x5408 0x1505 0x0505 0x7783 0x4531 0x4535 */
            LCDWriteReg(0x0020, Xpos );     
            LCDWriteReg(0x0021, Ypos );     
            break; 

        case SSD1298: 	 /* 0x8999 */
        case SSD1289:   /* 0x8989 */
            LCDWriteReg(0x004e, Xpos );      
            LCDWriteReg(0x004f, Ypos );          
            break;  

        case HX8347A: 	 /* 0x0047 */
        case HX8347D: 	 /* 0x0047 */
            LCDWriteReg(0x02, Xpos>>8 );                                                  
            LCDWriteReg(0x03, Xpos );  
            LCDWriteReg(0x06, Ypos>>8 );                           
            LCDWriteReg(0x07, Ypos );    
            break;     
        case SSD2119:	 /* 3.5 LCD 0x9919 */
            break; 
    }
}

/******************************************************************************
* Function Name  : LCDBGR2RGB
* Description    : RRRRRGGGGGGBBBBB convert to BBBBBGGGGGGRRRRR
* Input          : RGB color
* Output         : None
* Return         : RGB color
* Attention		 :
*******************************************************************************/
static uint16_t LCDBGR2RGB(uint16_t color)
{
    uint16_t  r, g, b, rgb;

    b = ( color>>0 )  & 0x1f;
    g = ( color>>5 )  & 0x3f;
    r = ( color>>11 ) & 0x1f;

    rgb =  (b<<11) + (g<<5) + (r<<0);

    return(rgb);
}

/******************************************************************************
* Function Name  : LCDGetPoint
* Description    : Get color of the point
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : Screen Color
* Attention		 : None
*******************************************************************************/
uint16_t LCDGetPoint(uint16_t Xpos,uint16_t Ypos)
{
    uint16_t dummy;

    LCDSetCursor(Xpos,Ypos);
    LCDWriteIndex(0x0022);  

    switch( LCD_Code )
    {
        case ST7781:
        case LGDP4531:
        case LGDP4535:
        case SSD1289:
        case SSD1298:
            dummy = LCDReadData();
            dummy = LCDReadData(); 

            return  dummy;	      
        case HX8347A:
        case HX8347D:
        {
            uint8_t red,green,blue;
            red = LCDReadData()>>3;
            green = LCDReadData()>>3; 
            blue = LCDReadData()>>2; 
            dummy = ( green << 11 ) | (blue << 5 ) | red;
        }
            return  dummy;
        default:	/* 0x9320 0x9325 0x9328 0x9331 0x5408 0x1505 0x0505 0x9919 */
            dummy = LCDReadData();
            dummy = LCDReadData(); 
            return  LCDBGR2RGB(dummy);
    }
}

/******************************************************************************
* Function Name  : LCDSetPoint
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDSetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t point)
{
    if( Xpos >= MAX_X || Ypos >= MAX_Y )
    {
        return;
    }
    LCDSetCursor(Xpos,Ypos);
    LCDWriteReg(0x0022,point);
}

/******************************************************************************
* Function Name  : LCDDrawLine
* Description    : Bresenham's line algorithm
* Input          : - x0:
*                  - y0:
*       	   - x1:
*       	   - y1:
*                  - color:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCDDrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color )
{
    short dx,dy;
    short temp;

    if( x0 > x1 )
    {
        temp = x1;
        x1 = x0;
        x0 = temp;   
    }
    if( y0 > y1 )
    {
        temp = y1;
        y1 = y0;
        y0 = temp;   
    }

    dx = x1-x0;
    dy = y1-y0;

    if( dx == 0 )
    {
        do
        { 
            LCDSetPoint(x0, y0, color);
            y0++;
        } while( y1 >= y0 ); 
        return; 
    }
    if( dy == 0 )
    {
        do
        {
            LCDSetPoint(x0, y0, color);
            x0++;
        } while( x1 >= x0 ); 
        return;
    }

    /* Bresenham's line algorithm  */
    if( dx > dy )
    {
        temp = 2 * dy - dx;
        while( x0 != x1 )
        {
            LCDSetPoint(x0,y0,color);
            x0++;
            if( temp > 0 )
            {
                y0++;
                temp += 2 * dy - 2 * dx; 
            }
            else         
            {
                temp += 2 * dy;
            }       
        }
        LCDSetPoint(x0,y0,color);
    }  
    else
    {
        temp = 2 * dx - dy;
        while( y0 != y1 )
        {
            LCDSetPoint(x0,y0,color);     
            y0++;                 
            if( temp > 0 )           
            {
                x0++;               
                temp+=2*dy-2*dx; 
            }
            else
            {
                temp += 2 * dy;
            }
        } 
        LCDSetPoint(x0,y0,color);
    }
} 

/******************************************************************************
* Function Name  : PutChar
* Description    : 
* Input          : - Xpos:
*                  - Ypos:
*		   - ASCI:
*		   - charColor:
*		   - bkColor:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PutChar( uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor, uint16_t bkColor )
{
    uint16_t i, j;
    uint8_t buffer[16], tmp_char;
    GetASCIICode(buffer,ASCI);
    for( i=0; i<16; i++ )
    {
        tmp_char = buffer[i];
        for( j=0; j<8; j++ )
        {
            if( (tmp_char >> 7 - j) & 0x01 == 0x01 )
            {
                LCDSetPoint( Xpos + j, Ypos + i, charColor );
            }
            else
            {
                LCDSetPoint( Xpos + j, Ypos + i, bkColor );
            }
        }
    }
}

/******************************************************************************
* Function Name  : GUIText
* Description    : 
* Input          : - Xpos: 
*                  - Ypos: 
*		   - str:
*		   - charColor:
*		   - bkColor:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GUIText(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor)
{
    uint8_t TempChar;
    do
    {
        TempChar = *str++;  
        PutChar(Xpos, Ypos, TempChar, Color, bkColor);
        if( Xpos < MAX_X - 8 )
        {
            Xpos += 8;
        } 
        else if ( Ypos < MAX_Y - 16 )
        {
            Xpos = 0;
            Ypos += 16;
        }   
        else
        {
            Xpos = 0;
            Ypos = 0;
        }    
    }
    while ( *str != 0 );
}

/*******************************************************************************
* Function Name  : DrawCross
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DrawCross(uint16_t Xpos,uint16_t Ypos)
{
    LCDDrawLine(Xpos-15, Ypos, Xpos-2, Ypos, 0xffff);
    LCDDrawLine(Xpos+2, Ypos, Xpos+15, Ypos, 0xffff);
    LCDDrawLine(Xpos, Ypos-15, Xpos, Ypos-2, 0xffff);
    LCDDrawLine(Xpos, Ypos+2, Xpos, Ypos+15, 0xffff);

    LCDDrawLine(Xpos-15, Ypos+15, Xpos-7, Ypos+15, RGB565CONVERT(184,158,131));
    LCDDrawLine(Xpos-15, Ypos+7, Xpos-15, Ypos+15, RGB565CONVERT(184,158,131));

    LCDDrawLine(Xpos-15, Ypos-15, Xpos-7, Ypos-15, RGB565CONVERT(184,158,131));
    LCDDrawLine(Xpos-15, Ypos-7, Xpos-15, Ypos-15, RGB565CONVERT(184,158,131));

    LCDDrawLine(Xpos+7, Ypos+15, Xpos+15, Ypos+15, RGB565CONVERT(184,158,131));
    LCDDrawLine(Xpos+15, Ypos+7, Xpos+15, Ypos+15, RGB565CONVERT(184,158,131));

    LCDDrawLine(Xpos+7, Ypos-15, Xpos+15, Ypos-15, RGB565CONVERT(184,158,131));
    LCDDrawLine(Xpos+15, Ypos-15, Xpos+15, Ypos-7, RGB565CONVERT(184,158,131));	  	
}

/*******************************************************************************
* Function Name  : LCDDrawPoint
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDDrawPoint(uint16_t Xpos,uint16_t Ypos)
{
    LCDSetPoint(Xpos, Ypos, Blue);     /* Center point */
    LCDSetPoint(Xpos+1, Ypos, Blue);
    LCDSetPoint(Xpos, Ypos+1, Blue);
    LCDSetPoint(Xpos+1, Ypos+1, Blue);	
}	

void PrepareWriteRAM(void)
{	
	LCD_REG = 0x0022;
}

/*******************************************************************************
* Function Name  : LCDWriteReg
* Description    : 
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDWriteIndex(uint16_t index)
{
    //GPIO_ResetBits(GPIOD , GPIO_Pin_7);		 //CS=0;
    LCD_REG	= index;
    //GPIO_SetBits(GPIOD , GPIO_Pin_7);		 //CS=1;
}

/*******************************************************************************
* Function Name  : LCDWriteReg
* Description    : 
* Input          : - index:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDWriteData(uint16_t data)
{
    //GPIO_ResetBits(GPIOD , GPIO_Pin_7);		 //CS=0;
    LCD_RAM = data;
    //GPIO_SetBits(GPIOD , GPIO_Pin_7);		 //CS=1;
}

/*******************************************************************************
* Function Name  : LCDReadData
* Description    : 
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
uint16_t LCDReadData(void)
{
    //uint32_t tmp;
    //GPIO_ResetBits(GPIOD , GPIO_Pin_7);		 //CS=0;
    //tmp = LCD_RAM;
    //GPIO_SetBits(GPIOD , GPIO_Pin_7);		 //CS=1;
    return LCD_RAM;
}


/*******************************************************************************
* Function Name  : LCDWriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LCDWriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{ 
    /* Write 16-bit Index, then Write Reg */  
    LCDWriteIndex(LCD_Reg);         
    /* Write 16-bit Reg */
    LCDWriteData(LCD_RegValue);  
}

/*******************************************************************************
* Function Name  : LCDWriteReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention		 : None
*******************************************************************************/
uint16_t LCDReadReg(uint16_t LCD_Reg)
{
    /* Write 16-bit Index (then Read Reg) */
    LCDWriteIndex(LCD_Reg);

    /* Read 16-bit Reg */
    return LCDReadData();
}


/******************************************************************************/
//
// Touch Panel Functions:
//
/******************************************************************************/

Matrix matrix;
Coordinate display;

Coordinate ScreenSample[3];
Coordinate DisplaySample[3] = {{50, 45}, {290, 100}, {160, 210}};

void TouchInitialization(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(SPI_SS_PERIPH_TOUCH , ENABLE);
    
    /*CS -> PC4*/
    GPIO_InitStruct.GPIO_Pin = SPI_SS_PIN_TOUCH;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(SPI_SS_PORT_TOUCH, &GPIO_InitStruct);
    GPIO_SetBits(SPI_SS_PORT_TOUCH, SPI_SS_PIN_TOUCH);

    /*IRQ Pin -> PC5*/
    GPIO_InitStruct.GPIO_Pin = SPI_IRQ_PIN_TOUCH;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(SPI_SS_PORT_TOUCH, &GPIO_InitStruct);	
}

/*******************************************************************************
* Function Name  : RD_AD
* Description    : 
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
static int RD_AD(void)  
{ 
    unsigned short buf,temp;  
    temp=jbSPIReceive(SPI2); 
    buf=temp<<8; 
    DelayUS(1);  
    temp=jbSPIReceive(SPI2); 
    buf |= temp; 
    buf>>=3;
    buf&=0xfff;     // Make sure only 12 bits are sent back
    return buf; 
} 


/*******************************************************************************
* Function Name  : ReadX
* Description    : Read ADS7843 ADC X 
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
int ReadX(void)  
{  
    int i; 
    GPIO_ResetBits(SPI_SS_PORT_TOUCH, SPI_SS_PIN_TOUCH); 
    jbSPISend(SPI2, (char *)CHX, 1);
    DelayUS(1); 
    i=RD_AD(); 
    GPIO_SetBits(SPI_SS_PORT_TOUCH, SPI_SS_PIN_TOUCH);
    return i;    
} 

/*******************************************************************************
* Function Name  : ReadY
* Description    : Read ADS7843 ADC Y
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
int ReadY(void)  
{  
    int i; 
    GPIO_ResetBits(SPI_SS_PORT_TOUCH, SPI_SS_PIN_TOUCH); 
    jbSPISend(SPI2, (char *)CHY, 1);
    DelayUS(1); 
    i=RD_AD(); 
    GPIO_SetBits(SPI_SS_PORT_TOUCH, SPI_SS_PIN_TOUCH);
    return i;    
} 


/*******************************************************************************
* Function Name  : TouchPanelGetAdXY
* Description    : Read ADS7843
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
void TouchPanelGetAdXY(int *x,int *y)  
{ 
    int adx,ady; 
    adx=ReadX(); 
    DelayUS(1); 
    ady=ReadY(); 
    *x=adx; 
    *y=ady; 
} 
	
/******************************************************************************
* Function Name  : ReadAds7846
* Description    : Get TouchPanel X Y
* Input          : None
* Output         : None
* Return         : Coordinate *
* Attention	 : None
*******************************************************************************/
Coordinate *ReadAds7846(void)
{
    static Coordinate  screen;
    int m0, m1, m2, TP_X, TP_Y,temp[3];
    uint8_t count=0;
    int buffer[2][9]={{0},{0}};
    int tempScreen[2];    

    do
    {		   
        TouchPanelGetAdXY(&TP_X, &TP_Y);  
        buffer[0][count]=TP_X;  
        buffer[1][count]=TP_Y;
        count++;  
    }while(!TP_INT_IN && count<9);  /* TP_INT_IN  */

    if(count==9)   /* Average X Y  */ 
    {
        for(count = 0; count < 2; count++)
        {
            /* Average X  and Y*/
            temp[0]=(buffer[count][0]+buffer[count][1]+buffer[count][2])/3;
            temp[1]=(buffer[count][3]+buffer[count][4]+buffer[count][5])/3;
            temp[2]=(buffer[count][6]+buffer[count][7]+buffer[count][8])/3;

            m0=temp[0]-temp[1];
            m1=temp[1]-temp[2];
            m2=temp[2]-temp[0];

            m0=m0>0?m0:(-m0);
            m1=m1>0?m1:(-m1);
            m2=m2>0?m2:(-m2);

            if( m0 > THRESHOLD  &&  m1 > THRESHOLD  &&  m2 > THRESHOLD ) 
            {
                return 0;
            }   

            if(m0<m1)
            {
                if(m2<m0) 
                    tempScreen[count]=(temp[0]+temp[2])/2;
                else 
                    tempScreen[count]=(temp[0]+temp[1])/2;	
            }
            else if(m2<m1) 
                tempScreen[count]=(temp[0]+temp[2])/2;
            else 
                tempScreen[count]=(temp[1]+temp[2])/2;
        }
        screen.x = tempScreen[0];
        screen.y = tempScreen[1];
        return &screen;
    }  
    return 0; 
}

/*******************************************************************************
* Function Name  : setCalibrationMatrix
* Description    : Calculate K A B C D E F
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
FunctionalState setCalibrationMatrix( Coordinate* displayPtr, Coordinate* screenPtr, Matrix* matrixPtr)
{

    FunctionalState retTHRESHOLD = ENABLE ;
    /* K\A3\BD(X0\A3\ADX2) (Y1\A3\ADY2)\A3\AD(X1\A3\ADX2) (Y0\A3\ADY2) */
    matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
    if( matrixPtr->Divider == 0 )
    {
        retTHRESHOLD = DISABLE;
    }
    else
    {
        /* A\A3\BD((XD0\A3\ADXD2) (Y1\A3\ADY2)\A3\AD(XD1\A3\ADXD2) (Y0\A3\ADY2))\A3\AFK	*/
        matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                        ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
            /* B\A3\BD((X0\A3\ADX2) (XD1\A3\ADXD2)\A3\AD(XD0\A3\ADXD2) (X1\A3\ADX2))\A3\AFK	*/
        matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                        ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
        /* C\A3\BD(Y0(X2XD1\A3\ADX1XD2)+Y1(X0XD2\A3\ADX2XD0)+Y2(X1XD0\A3\ADX0XD1))\A3\AFK */
        matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
        /* D\A3\BD((YD0\A3\ADYD2) (Y1\A3\ADY2)\A3\AD(YD1\A3\ADYD2) (Y0\A3\ADY2))\A3\AFK	*/
        matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                        ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
        /* E\A3\BD((X0\A3\ADX2) (YD1\A3\ADYD2)\A3\AD(YD0\A3\ADYD2) (X1\A3\ADX2))\A3\AFK	*/
        matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                        ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
        /* F\A3\BD(Y0(X2YD1\A3\ADX1YD2)+Y1(X0YD2\A3\ADX2YD0)+Y2(X1YD0\A3\ADX0YD1))\A3\AFK */
        matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                        (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                        (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
    }
    return( retTHRESHOLD ) ;
}

/*******************************************************************************
* Function Name  : getDisplayPoint
* Description    : Touch panel X Y to display X Y
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
FunctionalState getDisplayPoint(Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr )
{
    FunctionalState retTHRESHOLD =ENABLE ;

    if( matrixPtr->Divider != 0 )
    {
        /* XD = AX+BY+C */        
        displayPtr->x = ( (matrixPtr->An * screenPtr->x) + (matrixPtr->Bn * screenPtr->y) + matrixPtr->Cn) / matrixPtr->Divider ;
        /* YD = DX+EY+F */        
        displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + (matrixPtr->En * screenPtr->y) + matrixPtr->Fn) / matrixPtr->Divider ;
    }
    else
    {
        retTHRESHOLD = DISABLE;
    }
    return(retTHRESHOLD);
} 

void TouchPanelCalibrate(void)
{
    uint8_t i;
    Coordinate * Ptr;

    for(i=0;i<3;i++)
    {
        LCDClear(Black);
        GUIText(44,10,"Touch crosshair to calibrate",White,Black);
        Delayms(300);
        DrawCross(DisplaySample[i].x,DisplaySample[i].y);
        debug_printf("%i and %i cross\n", DisplaySample[i].x, DisplaySample[i].y);
        do
        {
            Ptr=ReadAds7846();
        }
        while(Ptr == (void*)0);
        debug_printf("%i and %i cross\n", Ptr->x, Ptr->y);
        ScreenSample[i].x= Ptr->x; ScreenSample[i].y= Ptr->y;
    }
    setCalibrationMatrix(&DisplaySample[0], &ScreenSample[0], &matrix);
    LCDClear(Black);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/