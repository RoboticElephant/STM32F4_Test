#include "Hdr.h"
#include "Communication.h"

void TIM2_IRQHandler(void) 
{
    // flash on update event
    if (TIM2->SR & TIM_SR_UIF)
    {
//        GPIOD->ODR ^= (1 << 13);
        GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
 
//  TIM2->SR = 0x0; // reset the status register
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}

void USART3_IRQHandler(void)
{
    char tempChar;
    if(USART_GetITStatus(USART3, USART_IT_RXNE))
    {
        if(receiveBufferEnd < RXBUFEND)
        {
            *receiveBufferEnd++ = USART_ReceiveData(USART3);
        }
    }
}