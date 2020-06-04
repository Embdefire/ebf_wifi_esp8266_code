/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   wifi ����͸������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./systick/bsp_SysTick.h"
#include "./DHT11/bsp_dht11.h"
#include "./esp8266/bsp_esp8266.h"
#include "test.h"
#include "./led/bsp_led.h"   
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART������ģʽΪ 115200 8-N-1*/
  Debug_USART_Config();
 
	/* ϵͳ��ʱ����ʼ�� */
	SysTick_Init();
	
	ESP8266_Init ();          //��ʼ��WiFiģ��ʹ�õĽӿں�����
	LED_GPIO_Config();                                                             //��ʼ��RGB�ʵ�
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                          //��ӡ����������ʾ��Ϣ
  printf ( "\r\n������������ֻ��ߴ��ڵ��������Ϸ�������������Կ��ư���RGB��\r\n" );                          //��ӡ����������ʾ��Ϣ
	printf ( "\r\nLED_RED\r\nLED_GREEN\r\nLED_BLUE\r\nLED_YELLOW\r\nLED_PURPLE\r\nLED_CYAN\r\nLED_WHITE\r\nLED_RGBOFF\r\n" );                          //��ӡ����������ʾ��Ϣ
  ESP8266_StaTcpClient_UnvarnishTest ();
	
  while(1)
	{	
  }	

}



/*********************************************END OF FILE**********************/

