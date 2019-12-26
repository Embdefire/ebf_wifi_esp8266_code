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
#include "./test/test.h"


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

	
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );    //��ӡ����������ʾ��Ϣ

	
  ESP8266_StaTcpClient_UnvarnishTest ();
	
	
  while ( 1 );


}



/*********************************************END OF FILE**********************/

