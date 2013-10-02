#include "SCCB.h"

/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SCCB_GPIO_Config(void)
{
	I2C_InitTypeDef  SCCB_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(Open207V_SCCB_SDA_GPIO_CLK | Open207V_SCCB_SCL_GPIO_CLK,ENABLE);
	
	RCC_APB1PeriphClockCmd(Open207V_SCCB_CLK,ENABLE);
	
	GPIO_PinAFConfig(Open207V_SCCB_SDA_GPIO_PORT, Open207V_SCCB_SDA_SOURCE, Open207V_SCCB_SDA_AF);
	GPIO_PinAFConfig(Open207V_SCCB_SCL_GPIO_PORT, Open207V_SCCB_SCL_SOURCE, Open207V_SCCB_SCL_AF);
	
	GPIO_InitStructure.GPIO_Pin =  Open207V_SCCB_SDA_PIN | Open207V_SCCB_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	I2C_DeInit(Open207V_SCCB);
	SCCB_InitStructure.I2C_Mode = I2C_Mode_I2C;
	SCCB_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	SCCB_InitStructure.I2C_OwnAddress1 = SCCB_SLAVE_ADDRESS7;
	SCCB_InitStructure.I2C_Ack = I2C_Ack_Enable;
	SCCB_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	SCCB_InitStructure.I2C_ClockSpeed = SCCB_SPEED;
	
	I2C_Cmd(Open207V_SCCB, ENABLE);
	I2C_Init(Open207V_SCCB, &SCCB_InitStructure);
	
	I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);	
}