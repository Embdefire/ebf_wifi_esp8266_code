/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   DHT11��ʪ�ȴ�������ȡ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "systick/bsp_SysTick.h"
#include "DHT11/bsp_dht11.h"
#include "bsp_SysTick.h"
#include "./ESP8266/bsp_esp8266.h"
#include "./test/test.h"
#include "bsp_led.h"
#include "bsp_beep.h"

DHT11_Data_TypeDef DHT11_Data;

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
  
  ESP8266_Init (); 
  LED_GPIO_Config ();
	BEEP_GPIO_Config ();
	
	/* DHT11��ʼ�� */
	DHT11_GPIO_Config();
	
	printf("\r\n***Ұ��F429��ս��APP���ƿ�����ʵ��***\r\n");
  
  ESP8266_StaTcpClient_UnvarnishTest ();
	
  while(1);

}



/*********************************************END OF FILE**********************/

