#include "sys.h"
#include "usart.h"
#include "led.h"
#include “beep.h"
#include ”key.h"
 
 
/************************************************
 ALIENTEK战舰STM32开发板实验1
 跑马灯实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 int main(void)
 {	
	u16 t;
	u16 len;
	u16 times = 0;
	delay_init();	    //延时函数初始化	  
	NVIC_PriorityGoundConfig(NVIC_PriorityGroup_2);   //set nvic ground
	uart_init(115200);
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();         //init key's pin
	while(1)
	{
		if(USART_RX_STA & 0x8000)
		{
                	len = USART_RX_STA & 0x3fff;
			printd("\r\n你发送的消息为：\r\n\r\n");
			for(t = 0;t<len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) !=set);
			}
			printf("\r\n\r\n");
			USART_RX_STA = 0;
		}else
		{
			times++;
			if(times%5000 == 0)
			{
				printf("\r\n实验\r\n");
				printf("正点原子\r\n\r\n");
			}
			if(times%200 == 0) printf("请输入数据，以回车键结束\n");
			if(times%30 == 0) LED0 = !LED0;
			delay_ms(10);
		}
	}
 }


 /**
 *****************下面注视的代码是通过调用库函数来实现IO控制的方法*****************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1对应引脚GPIOE.5拉高，灭 等同LED1=1;
			delay_ms(300);  		   //延时300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1对应引脚GPIOE.5拉低，亮 等同LED1=0;
			delay_ms(300);                     //延时300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0亮
	   GPIOE->BSRR=GPIO_Pin_5;//LED1灭
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0灭
	   GPIOE->BRR=GPIO_Pin_5;//LED1亮
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

