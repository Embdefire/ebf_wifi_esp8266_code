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
#include "stm32f10x_it.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "./dwt_delay/core_delay.h"

 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main ( void )
{
	/* ��ʼ�� */
  USARTx_Config ();                                                              //��ʼ������1
	SysTick_Init ();                                                               //���� SysTick Ϊ 1ms �ж�һ�� 
  CPU_TS_TmrInit();
	ESP8266_Init ();                                                               //��ʼ��WiFiģ��ʹ�õĽӿں�����
	DHT11_Init ();
  LED_Init ();
	Beep_Init ();
	
	
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                          //��ӡ����������ʾ��Ϣ
	
  
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                                  //��ESP8266��������
  
  
  while ( 1 )
  {
    if(Task_Delay[0] >= TASK_DELAY_0)     //�ж��Ƿ�ִ������0
    {
      Task_Delay[0] = 0;
      
      //ִ������0
      //macLED1_TOGGLE();
      ESP8266_CheckRecv_SendDataTest(); // ESP8266 ÿ10 ms�����յ�������

    }
    
    if(Task_Delay[1] >= TASK_DELAY_1)     //�ж��Ƿ�ִ������1
    {
      Task_Delay[1] = 0;
      
      //ִ������1
      macLED2_TOGGLE();  //�̵ƻ���˸
      
      
    }
    
    if(Task_Delay[2] >= TASK_DELAY_2)     //�ж��Ƿ�ִ������2
    {
      Task_Delay[2] = 0;
      
      //ִ������2
      
      //LED3_TOGGLE;
    }

    
    /*****************************************************************************/
    // ���ȷ������������ִ�����������ִ��
    // Delay_ms(1000);
    // ���⣬��Ҫ���ж��Ƿ�ִ���������Щ if ��������������Ӽ�����ʱ����Ӱ�������ִ��
    /*****************************************************************************/
  }
	
	
}


/*********************************************END OF FILE**********************/
