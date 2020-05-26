/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_esp8266.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	
	uint16_t i;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	ESP8266_Init();
	/* ����һ���ַ��� */
	printf("��ӭʹ��Ұ��STM32������\n\n");
	printf("����һ��ESP8266ATָ�����ʵ��\n\n");
	printf("�뷢�͡�AT������ESP8266�Ƿ�׼����\n\n");
	printf("ʹ�ô��ڵ�������ʱ�ǵü��ϻ��лس�\n\n");
	printf("����ATָ����ο�ģ������\n\n");
	printf("������ESP8266�ϵ��ʼ����ӡ����Ϣ\n\n");
  while(1)
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
	  }
		if(strEsp8266_Fram_Record .InfBit .FramFinishFlag)                             //������յ���ESP8266������
		{                                                      
			for(i = 0;i < strEsp8266_Fram_Record .InfBit .FramLength; i++)               
			{
				 USART_SendData( DEBUG_USARTx ,strEsp8266_Fram_Record .Data_RX_BUF[i]);    //ת����ESP82636
				 while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC)==RESET){}
			}
			 strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //�������ݳ�������
			 strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //���ձ�־����
		}
  }	
}	
/*********************************************END OF FILE**********************/
