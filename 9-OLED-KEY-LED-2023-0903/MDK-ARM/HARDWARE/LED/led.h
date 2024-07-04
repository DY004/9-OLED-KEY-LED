#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stm32f4xx.h"

#define LED0 PFout(9)
#define LED1 PFout(10)
//�͵�ƽʱ���������ߵ�ƽʱ������
#define LED_ON  0
#define LED_OFF 1

void LED_Init(void);

void LED01_ON(void);
void LED01_OFF(void);

#endif

