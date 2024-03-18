#ifndef __DELAY_H
#define __DELAY_H
#include "stm32g0xx.h"
void delay_init(uint8_t SYSCLK);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
#endif

