#ifndef __HDR_H
#define __HDR_H

#include <__cross_studio_io.h>
#include <stm32f4xx.h>
#include "stm32f4xx_conf.h"

// Header for delay
#include "Utility.h"

#define BUF_SIZE        128                     //Size of the buffer for RX/TX (128 bytes)

enum BAUD_RATE
{
    BAUD_115200 = 115200,
    BAUD_19200 = 19200,
    BAUD_9600 = 9600,
    BAUD_1200 = 1200
};
typedef enum BAUD_RATE BAUD_RATE;

#endif