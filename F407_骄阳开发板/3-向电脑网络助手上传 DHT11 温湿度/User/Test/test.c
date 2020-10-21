#include "./test/test.h"
#include "./esp8266/bsp_esp8266.h"
#include "./systick/bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "DHT11/bsp_dht11.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_debug_usart.h"


#define LED_CMD_NUMBER   8
char *ledCmd[5] = { "LED_1","LED_2","LED_3","LED_4","LED_OFF" };
                           
                     
/**
  * @brief  ��ȡ����������ֺʹ��ڵ������ַ�������Ϣ
  * @param  ��
  * @retval ��
  */
volatile uint8_t ucTcpClosedFlag = 0;

char cStr [ 1500 ] = { 0 };

void Get_ESP82666_Cmd( char * cmd)
{
	uint8_t i;
	for(i = 0;i < LED_CMD_NUMBER; i++)
	{
     if(( bool ) strstr ( cmd, ledCmd[i] ))
		 break;
	}
	switch(i)
	{
		case 0:
			LED_1;
		break;
		case 1:
			LED_2;
		break;
		case 2:
			LED_3;
		break;
		case 3:
			LED_4;
		break;
		case 4:
			LED_OFF;
		break;
		default:
			
			break;      
	}    
}

/**
  * @brief  ESP8266 ��Sta Tcp Client��͸��
  * @param  ��
  * @retval ��
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
	uint8_t ucStatus;
	DHT11_Data_TypeDef DHT11_Data;
	
  printf ( "\r\n�������� ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();
	
	ESP8266_Net_Mode_Choose ( STA );

  while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
	ESP8266_Enable_MultipleId ( DISABLE );
	
	while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	while ( ! ESP8266_UnvarnishSend () );
	
	printf ( "\r\n���� ESP8266 ���\r\n" );
	
	while ( 1 )
	{
		Delay_ms ( 2000 );
		if ( Read_DHT11 ( & DHT11_Data ) == SUCCESS )       //��ȡ DHT11 ��ʪ����Ϣ
			sprintf ( cStr, "\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n", 
								DHT11_Data .humi_int, DHT11_Data .humi_deci, DHT11_Data .temp_int, DHT11_Data.temp_deci );			
		else
			sprintf ( cStr, "Read DHT11 ERROR!\r\n" );

		printf ( "%s", cStr );                                             //��ӡ��ȡ DHT11 ��ʪ����Ϣ

		ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );               //���� DHT11 ��ʪ����Ϣ�������������	
		
		if ( ucTcpClosedFlag )                                             //����Ƿ�ʧȥ����
		{
			ESP8266_ExitUnvarnishSend ();                                    //�˳�͸��ģʽ
			
			do ucStatus = ESP8266_Get_LinkStatus ();                         //��ȡ����״̬
			while ( ! ucStatus );
			
			if ( ucStatus == 4 )                                             //ȷ��ʧȥ���Ӻ�����
			{
				printf ( "\r\n���������ȵ�ͷ����� ......\r\n" );
				
				while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
				
				while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
				
				printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );

			}
			
			while ( ! ESP8266_UnvarnishSend () );		
			
		}
	}
	
		
}



