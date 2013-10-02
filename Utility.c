#include "Utility.h"

void  Delay(uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

void Delayms(uint16_t ms)    
{ 
    uint16_t i,j; 
    for( i = 0; i < ms; i++ )
    { 
        for( j = 0; j < 1141; j++ );
    }
}

void DelayUS(vu32 cnt)
{
    uint16_t i;
    for(i = 0;i<cnt;i++)
    {
        uint8_t us = 12;
        while (us--);
    }
}