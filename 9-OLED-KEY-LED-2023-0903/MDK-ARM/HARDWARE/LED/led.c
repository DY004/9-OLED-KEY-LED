#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);  //ʹ��GPIOFʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  //LED0��LED1��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     //��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //����
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);  //LED0��LED1���øߣ�����

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

