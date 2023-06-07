#include "main.h"
#include "delay.h"
#include "lcd1602.h"
#include "MPU6050.h"

#define RUN_CNT_MAX			    40
#define MENU_NUM_LIMIT			2

#include <reg52.h>

//Pin P1, you can replace
sbit KEY1=P3^1;
sbit KEY2=P3^0;
	#define KEY1_PRESS	0
	#define KEY2_PRESS	1
	#define KEY_UNPRESS	2

	#define N 0.005
/********************* 变量定义 *******************/
uchar menu = 2;//now only angle dat
int Mpu_Xdat;
int Mpu_Ydat;
int Mpu_Zdat;

bit Flag_X_Nega;//0---正数  1---负数
bit Flag_Y_Nega;//0---正数  1---负数
bit Flag_Z_Nega;//0---正数  1---负数

/********************* 函数声明 *******************/
//显示界面  每个菜单的结构
void Dis_menu();
//显示 数据
void Dis_Dat();
//获取数据
void Get_Dat();
//按键扫描
void Key_Scan();


void delay_ms(unsigned int n)
{
 unsigned int i = n*100;
 while (i--);
}


void TurnMotor(unsigned long angle,unsigned int A)
{
 unsigned char tmp; 
 unsigned char index = 0; 
 unsigned long beats = 0; 
 unsigned char code BeatCode[2][8] = { 
 0xE, 0xC, 0xD, 0x9, 0xB, 0x3, 0x7, 0x6,
 0x6 ,0x7, 0x3, 0xB, 0x9, 0xD, 0xC, 0xE
 };
 
 beats = (angle*4096) / 360; 
 while (beats--) 
 {
 tmp = P1; 
 tmp = tmp & 0x0f;
 tmp = tmp | (BeatCode[A][index]<<4); 
 P1 = tmp; 
 index++; 
 index = index & 0x07;
 delay_ms(1); 
 }
 P1 = P1 | 0xf0; 
}


unsigned int key_scan()
{ 
	if(KEY1==0||KEY2==0)//??????????
	{
		delay_ms(5);//????
		if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
	}
	return KEY_UNPRESS;		
}




void main()
{
	int flagb = 2;
	int sum=0;
	unsigned int A=2;
	DelayMs(100);//等待系统稳定
	LCD_Init();
	Dis_menu();
	InitMPU6050();
	while(1)
	{
		//B:
		Get_Dat();
		DelayMs(5);
//		A=key_scan();
//		if(A==0||A==1)
//		{
//			TurnMotor(360*N,A);
//			
//		}
//		
//		A=2;
		sum++;
		if(Mpu_Ydat < -20&&sum>3)
		{
			TurnMotor(360*N,0);
			sum=0;
		}
		else if(Mpu_Ydat > 20&&sum>3)
		{
			TurnMotor(360*N,1);
			sum=0;
		}
	
	
		//Key_Scan();
	}
}

/*
void Key_Scan()
{
  //切换菜单页面
	if(!key1)
	{
		DelayMs(2);
		if(!key1)
		{
			menu++;
			if(menu > MENU_NUM_LIMIT)
			{
				menu = 0;
			}
      //刷新菜单显示结构
			Dis_menu();
			while(!key1);
		}
	}
}
*/
//获取数据
void Get_Dat()
{
	static uint Run_Get_Cnt = RUN_CNT_MAX;
	if(Run_Get_Cnt++ > RUN_CNT_MAX)//设置获取显示间隔
	{
		Run_Get_Cnt = 0;
    //根据menu获取对应数据   因为Menu 刚好是 0 1 2 对应了宏定义
		Get_Mpu6050_Data(&Mpu_Xdat,&Mpu_Ydat,&Mpu_Zdat,menu);
    
    //判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
//		if(Mpu_Xdat < 0)
//    {
//      //Mpu_Xdat*=-1; //Mpu_Xdat = Mpu_Xdat * -1;
//      Flag_X_Nega = 1;
//    }
//    else
//    {
//      Flag_X_Nega = 0;
//    }
//    //判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
//		if(Mpu_Ydat < 0)
//    {
//      //Mpu_Ydat*=-1;
//      Flag_Y_Nega = 1;
//    }
//    else
//    {
//      Flag_Y_Nega = 0;
//    }
//    //判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
//		if(Mpu_Zdat < 0)
//    {
//      //Mpu_Zdat*=-1;
//      Flag_Z_Nega = 1;
//    }
//    else
//    {
//      Flag_Z_Nega = 0;
//    }
    //获取完数据 就将数据显示出来
		Dis_Dat();
	}
}

//显示 数据
void Dis_Dat()
{
  //只有在这三个菜单才显示对应数据
	if(menu == 0 || menu == 1 || menu == 2)
	{
//    //判断正负标志位  对应显示负号
//    if(Flag_X_Nega)
//      LCD_Write_Char(9,0,'-');
//    else
//      LCD_Write_Char(9,0,' ');
    //在该坐标显示5位的 数据 
    LCD_Write_Number(10,0,Mpu_Xdat,5);
    
//    //判断正负标志位  对应显示负号
//    if(Flag_Y_Nega)
//      LCD_Write_Char(1,1,'-');
//    else
//      LCD_Write_Char(1,1,' ');
    //在该坐标显示5位的 数据 
    LCD_Write_Number(2,1,Mpu_Ydat,5);
    
//    //判断正负标志位  对应显示负号
//    if(Flag_Z_Nega)
//      LCD_Write_Char(9,1,'-');
//    else
//      LCD_Write_Char(9,1,' ');
    //在该坐标显示5位的 数据 
    LCD_Write_Number(10,1,Mpu_Zdat,5);
	}
}

//显示界面  每个菜单的结构
void Dis_menu()
{
  LCD_Clear();
	if(menu == 0)
	{
		LCD_Write_String(0,0,"ACCEL   X      ");
		LCD_Write_String(0,1,"Y       Z      ");
	}
	else if(menu == 1)
	{
		LCD_Write_String(0,0,"GYRO    X      ");
		LCD_Write_String(0,1,"Y       Z      ");
	}
	else if(menu == 2)
	{
		LCD_Write_String(0,0,"ANGLE   X:     ");
		LCD_Write_String(0,1,"Y:      Z:     ");
	}
	Dis_Dat();
}

