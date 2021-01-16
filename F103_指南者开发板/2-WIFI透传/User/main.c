/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFiģ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "test.h"
#include "bsp_dht11.h"
#include "bsp_led.h"  
 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main ( void )
{
	/* ��ʼ������1 */
  USART_Config ();        //
	
	/* ���� SysTick Ϊ 1ms �ж�һ��  */
	SysTick_Init ();        
	
	/* ��ʼ��WiFiģ��ʹ�õĽӿں����� */
	ESP8266_Init ();     

	/* ��ʼ��RGB�ʵ� */
  LED_GPIO_Config();      
  
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                               //��ӡ����������ʾ��Ϣ
  printf ( "\r\n������������ֻ��ߴ��ڵ��������Ϸ�������������Կ��ư���RGB��\r\n" );  //��ӡ����������ʾ��Ϣ
	printf ( "\r\nLED_RED\r\nLED_GREEN\r\nLED_BLUE\r\nLED_YELLOW\r\nLED_PURPLE\r\nLED_CYAN\r\nLED_WHITE\r\nLED_RGBOFF\r\n" ); //��ӡ����������ʾ��Ϣ
  
	/* ESP8266 ��Sta Tcp Client��͸�� */
	ESP8266_StaTcpClient_UnvarnishTest ();
	
  while ( 1 );
}


/*********************************************END OF FILE**********************/
