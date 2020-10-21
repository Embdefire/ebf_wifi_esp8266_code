#include "./test/test.h"
#include "./esp8266/bsp_esp8266.h"
#include "./systick/bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "./led/bsp_led.h"   
#include "./usart/bsp_debug_usart.h"

#define LED_CMD_NUMBER   8
char *ledCmd[5] = { "LED_1","LED_2","LED_3","LED_4","LED_OFF" };
                                          
volatile uint8_t ucTcpClosedFlag = 0;

/**
  * @brief  ��ȡ����������ֺʹ��ڵ������ַ�������Ϣ
  * @param  ��
  * @retval ��
  */
void Get_ESP82666_Cmd( char * cmd )
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
	uint16_t i;
		
  printf ( "\r\n�������� ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();
	
	ESP8266_Net_Mode_Choose ( STA );

  while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
	ESP8266_Enable_MultipleId ( DISABLE );
	
	while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	while ( ! ESP8266_UnvarnishSend () );
	
	printf ( "\r\n���� ESP8266 ���\r\n" );
	printf ( "\r\n��ʼ͸��......\r\n" );
	
	while ( 1 )
	{
		if(strUSART_Fram_Record .InfBit .FramFinishFlag == 1)  //������յ��˴��ڵ������ֵ�����
		{
			
			for(i = 0;i < strUSART_Fram_Record .InfBit .FramLength; i++)
			{
				 USART_SendData( macESP8266_USARTx ,strUSART_Fram_Record .Data_RX_BUF[i]); //ת����ESP82636
				 while(USART_GetFlagStatus(macESP8266_USARTx,USART_FLAG_TC)==RESET){}      //�ȴ��������
			}
			strUSART_Fram_Record .InfBit .FramLength = 0;                                //�������ݳ�������
			strUSART_Fram_Record .InfBit .FramFinishFlag = 0;                            //���ձ�־����
			Get_ESP82666_Cmd(strUSART_Fram_Record .Data_RX_BUF);                         //���һ���ǲ��ǵ������
	  }
		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //������յ���ESP8266������
		{                                                      
			for(i = 0;i < strEsp8266_Fram_Record .InfBit .FramLength; i++)               
			{
				 USART_SendData( DEBUG_USART ,strEsp8266_Fram_Record .Data_RX_BUF[i]);    //ת����ESP82636
				 while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TC)==RESET){}
			}
			 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //�������ݳ�������
			 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //���ձ�־����
			 Get_ESP82666_Cmd(strEsp8266_Fram_Record .Data_RX_BUF);                      //���һ���ǲ��ǵ������
		}
	
		
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



