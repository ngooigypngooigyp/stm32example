#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//蜂鸣器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB8为输出口.并使能这个口的时钟		    
//蜂鸣器初始化
void BEEP_Init(void)
{
    GPIO_InitTypedef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GBIOB, ENABLE);   //enable GPIOB clock
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;             //BEEP -->PB.8 set the pin
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //set the speed to 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);             //init the parameter GPIOB.8
    
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);               //output 0, close the beep
}
