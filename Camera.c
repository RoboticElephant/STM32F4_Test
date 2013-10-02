#include "Camera.h"
#include "OV7670Cam.h"
#include "Communication.h"

/*
  D0 -- PC6
  D1 -- PA10
  D2 -- PC8
  D3 -- PC9
  D4 -- PE4
  D5 -- PB6
  D6 -- PE5
  D7 -- PE6
	
  PCK - PA6
  HS -- PA4
  VS -- PB7
*/	
void InitDCMI(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    DCMI_InitTypeDef DCMI_InitStruct;
    DMA_InitTypeDef  DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI); //HSYNC 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI); //PCLK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI); //VSYNC

    //RED	
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);

    //Blue
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);	

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    DCMI_InitStruct.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
    DCMI_InitStruct.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
    DCMI_InitStruct.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
    DCMI_InitStruct.DCMI_VSPolarity = DCMI_VSPolarity_High;
    DCMI_InitStruct.DCMI_HSPolarity = DCMI_HSPolarity_High;
    DCMI_InitStruct.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
    DCMI_InitStruct.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
    DCMI_Init(&DCMI_InitStruct);
    
    DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
    DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
    DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 

    /* Configures the DMA2 to transfer Data from DCMI to the LCD ****************/
    /* Enable DMA2 clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  

    /* DMA2 Stream1 Configuration */  
    DMA_DeInit(DMA2_Stream1);

    DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
    DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 0xfffe;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
 
    DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
}

void MCO1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_ClockSecuritySystemCmd(ENABLE);

	/* Enable GPIOs clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
		
	/* Configure MCO (PA8) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_3);
}

void DCMI_0V7670_PWDN_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOs clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*PWDN*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	Delayms(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);	
}

/**
  * @brief  Set the VGA size(640*320).
  * @param  None
  * @retval None
  */
uint8_t DCMI_OV7670_Init(void)
{
    uint8_t i;
    //	SCCB_GPIO_Config();
    InitDCMI();
    MCO1_Init();
    //DCMI_0V7670_RST_PWDN_Init();
    Delayms(0xfff);
//  if(DCMI_SingleRandomWrite(OV7670_COM7, SCCB_REG_RESET)!=0)
    if(MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, OV7670_COM7, 1, (char *)SCCB_REG_RESET)==0)
        return 0xff;
    Delayms(0xfff);

    for(i=0;i<CHANGE_REG_NUM;i++)
    {
//	if(DCMI_SingleRandomWrite(change_reg[i][0],change_reg[i][1])!=0)
        if(MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, change_reg[i][0], 1, &change_reg[i][1])==0)
        {
            return 0xff;
        }
    }
    //OV7670_config_window(272,16,320,240);// set 240*320
    Delayms(0xfff);
    return 0;//Init ok
}

/**
  * @brief  Read the OV7670 Manufacturer identifier.
  * @param  OV7670ID: pointer to the OV7670 Manufacturer identifier. 
  * @retval None
  */
uint8_t DCMI_OV7670_ReadID(OV7670_IDTypeDef* OV7670ID)
{
    uint8_t temp;
//    if(DCMI_SingleRandomRead(OV7670_MIDH,&temp)!=0)
    if(MasterI2CRead(I2C2, OV7670_ADD, 0, 0, OV7670_MIDH, 1, &temp)==0)
        return 0xff;
    OV7670ID->Manufacturer_ID1 = temp;
//    if(DCMI_SingleRandomRead(OV7670_MIDL,&temp)!=0)
    if(MasterI2CRead(I2C2, OV7670_ADD, 0, 0, OV7670_MIDL, 1, &temp)==0)
        return 0xff;
    OV7670ID->Manufacturer_ID2 = temp;
//    if(DCMI_SingleRandomRead(OV7670_VER,&temp)!=0)
    if(MasterI2CRead(I2C2, OV7670_ADD, 0, 0, OV7670_VER, 1, &temp)==0)
        return 0xff;
    OV7670ID->Version = temp;
//    if(DCMI_SingleRandomRead(OV7670_PID,&temp)!=0)
    if(MasterI2CRead(I2C2, OV7670_ADD, 0, 0, OV7670_PID, 1, &temp)==0)
        return 0xff;
    OV7670ID->PID = temp;

    return 0;
}
/**
  * @brief  config_OV7660_window 
  * @param  //(140,16,640,480) is good for VGA
  *			//(272,16,320,240) is good for QVGA
  * @retval None
  */
void OV7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height)
{
    uint16_t endx=(startx+width);
    uint16_t endy=(starty+height*2);// must be "height*2"
    uint8_t temp_reg1, temp_reg2;
    uint8_t state,temp;

    state = state;	   //Prevent report warning

//    state = DCMI_SingleRandomRead(0x03, &temp_reg1 );
    state = MasterI2CRead(I2C2, OV7670_ADD, 0, 0, 0x03, 1, &temp_reg1);
    temp_reg1 &= 0xC0;
//    state = DCMI_SingleRandomRead(0x32, &temp_reg2 );
    state = MasterI2CRead(I2C2, OV7670_ADD, 0, 0, 0x32, 1, &temp_reg2);
    temp_reg2 &= 0xC0;

    // Horizontal
    temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
//    state = DCMI_SingleRandomWrite(0x32, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x32, 1, &temp);
    temp = (startx&0x7F8)>>3;
//    state = DCMI_SingleRandomWrite(0x17, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x17, 1, &temp);
    temp = (endx&0x7F8)>>3;
//    state = DCMI_SingleRandomWrite(0x18, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x18, 1, &temp);

    // Vertical
    temp = temp_reg1|((endy&0x7)<<3)|(starty&0x7);
//    state = DCMI_SingleRandomWrite(0x03, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x03, 1, &temp);
    temp = (starty&0x7F8)>>3;
//    state = DCMI_SingleRandomWrite(0x19, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x19, 1, &temp);
    temp = (endy&0x7F8)>>3;
//    state = DCMI_SingleRandomWrite(0x1A, temp );
    state = MasterI2CWrite(I2C2, OV7670_ADD, 0, 0, 0x1A, 1, &temp);
}