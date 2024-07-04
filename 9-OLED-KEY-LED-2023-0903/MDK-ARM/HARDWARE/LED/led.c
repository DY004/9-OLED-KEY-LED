#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);  //使能GPIOF时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  //LED0和LED1对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);  //LED0、LED1设置高，灯灭

}

void LED01_ON(void)
{
	LED0 = 0;
	LED1 = 0;
}

void LED01_OFF(void)
{
	LED0=1;
	LED1=1;
}

