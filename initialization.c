#include "initialization.h"
#include "Hdr.h"

void InitPorts(void);
void InitUart3(BAUD_RATE baud);
void InitTimer2(void);
void InitI2C1(void);
void InitI2C2(void);
void InitSPI2(void);
void InitLCD(void);

void Initialize(void)
{
//    InitPorts();

#ifdef INIT_UART3
    InitUart3(BAUD_115200);
#endif

#ifdef INIT_TIM2
    InitTimer2();
#endif

#ifdef INIT_I2C1
    InitI2C1();
#endif

#ifdef INIT_I2C2
    InitI2C2();
#endif

#ifdef INIT_SPI2
    InitSPI2();
#endif

#ifdef INIT_LCD
    InitLCD();
#endif  
}

void InitPorts(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; // we want to configure all LED GPIO pins
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;           // this sets the pin type to push / pull (as opposed to open drain)
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
    GPIO_Init(GPIOD, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
}
// PC10 -> TX and PC11 -> RX
void InitUart3(BAUD_RATE baud)
{
    GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // Pins 10(UART_TX) and 11(UART_RX)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;// this defines the IO speed and has nothing to do with the baudrate!
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;// this defines the output type as push pull
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
    GPIO_Init(GPIOC, &GPIO_InitStruct);// now all the values are passed to the GPIO_Init()

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

    USART_InitStruct.USART_BaudRate = baud;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3, &USART_InitStruct);

    // Set up the interrupt
    // USART_IT_RXNE = Receive Data register not empty interrupt
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // Enable to USART
    USART_Cmd(USART3, ENABLE);
}

void InitTimer2(void)
{
    TIM_TimeBaseInitTypeDef structTimeBase;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    structTimeBase.TIM_Prescaler = 0x200;
    structTimeBase.TIM_CounterMode = TIM_CounterMode_Up;
    structTimeBase.TIM_Period = 0x400;
    structTimeBase.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM2, &structTimeBase);

    NVIC->ISER[0] |= 1<< (TIM2_IRQn); // enable the TIM2 IRQ

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);  // Enable the timer 2
}

void InitI2C1(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as I2C1SDA and I2C1SCL
    I2C_InitTypeDef I2C_InitStruct; // this is for the I2C1 initilization

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Pins 6(I2C1_SCL) and 7(I2C1_SDA)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;// this defines the IO speed and has nothing to do with the baudrate!
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;// this defines the output type as open drain
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
    GPIO_Init(GPIOB, &GPIO_InitStruct);// now all the values are passed to the GPIO_Init()

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

    I2C_InitStruct.I2C_ClockSpeed = 100000; // Set the speed of the clock (must be lower than 400kHz)
    I2C_InitStruct.I2C_Mode =I2C_Mode_I2C; // Set the mode to be I2C
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0xF0;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStruct);  // Initial setup of the I2C1 Line

    I2C_Cmd(I2C1, ENABLE);  // Start the I2C1 peripheral
}

void InitI2C2(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as I2C1SDA and I2C1SCL
    I2C_InitTypeDef I2C_InitStruct; // this is for the I2C1 initilization

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    // PB10-> I2C2_SCL and PB11-> I2C2_SDA
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // Pins 10(I2C1_SCL) and 11(I2C1_SDA)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;// this defines the IO speed and has nothing to do with the baudrate!
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;// this defines the output type as open drain
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
    GPIO_Init(GPIOB, &GPIO_InitStruct);// now all the values are passed to the GPIO_Init()

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

    I2C_InitStruct.I2C_ClockSpeed = 100000; // Set the speed of the clock (must be lower than 400kHz)
    I2C_InitStruct.I2C_Mode =I2C_Mode_I2C; // Set the mode to be I2C
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0xF0;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2C_InitStruct);  // Initial setup of the I2C1 Line

    I2C_Cmd(I2C2, ENABLE);  // Start the I2C1 peripheral
}

void InitSPI2(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);    // Enable SPI2 Peripheral
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   // Enable the GPIO for the pins
    
    // PB12 -> NSS; PB13 -> SCK; PB15 -> MOSI; PB14 -> MISO
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // No Pull up or pull down
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;    // was 128
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStruct);
    
    SPI_Cmd(SPI2, ENABLE);
}

void InitLCD(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;
    
    /* Enable GPIOs clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
    /* Enable FSMC clock */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); 
    
    /* GPIOD configuration */
    /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
        PD.10(D15), PD.11(A16), PD.14(D0), PD.15(D1) as alternate function push pull */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | 
                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_Init(GPIOD, &GPIO_InitStruct);
         
    /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) as alternate function push pull */	
    /* GPIOE configuration */
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);
    
    GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    /*CS always low*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStruct);	
    GPIO_ResetBits(GPIOD , GPIO_Pin_7);		 //CS=0;
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;               // LCD is type of SRAM
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;      // Communicate by 16bit parallel
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;  // LCD doesnt have burst memory
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;                           // Not Active because burst mode is off/disabled
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;            // Not run in synchronous
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;    // Extended mode is not used therefore we use this one
    
    FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 15; // Default value is 15 after reset // (between 0x0 and 0xF) Not used with synchronous NOR Flash Memories (using asynchronous)
    FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;   // Duration of address hold time
    FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 15;    // Duration of the data setup time
    FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;
    FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;       // Not used for asynchronous NOR Flash, SRAM or ROM accesser
    FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0;       // It is don't care in asynchronous NOR, SRAM or ROM accesses
    FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
    
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
