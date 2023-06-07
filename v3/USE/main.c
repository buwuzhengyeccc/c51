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
/********************* �������� *******************/
uchar menu = 2;//now only angle dat
int Mpu_Xdat;
int Mpu_Ydat;
int Mpu_Zdat;

bit Flag_X_Nega;//0---����  1---����
bit Flag_Y_Nega;//0---����  1---����
bit Flag_Z_Nega;//0---����  1---����

/********************* �������� *******************/
//��ʾ����  ÿ���˵��Ľṹ
void Dis_menu();
//��ʾ ����
void Dis_Dat();
//��ȡ����
void Get_Dat();
//����ɨ��
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
	DelayMs(100);//�ȴ�ϵͳ�ȶ�
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
  //�л��˵�ҳ��
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
      //ˢ�²˵���ʾ�ṹ
			Dis_menu();
			while(!key1);
		}
	}
}
*/
//��ȡ����
void Get_Dat()
{
	static uint Run_Get_Cnt = RUN_CNT_MAX;
	if(Run_Get_Cnt++ > RUN_CNT_MAX)//���û�ȡ��ʾ���
	{
		Run_Get_Cnt = 0;
    //����menu��ȡ��Ӧ����   ��ΪMenu �պ��� 0 1 2 ��Ӧ�˺궨��
		Get_Mpu6050_Data(&Mpu_Xdat,&Mpu_Ydat,&Mpu_Zdat,menu);
    
    //�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
//		if(Mpu_Xdat < 0)
//    {
//      //Mpu_Xdat*=-1; //Mpu_Xdat = Mpu_Xdat * -1;
//      Flag_X_Nega = 1;
//    }
//    else
//    {
//      Flag_X_Nega = 0;
//    }
//    //�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
//		if(Mpu_Ydat < 0)
//    {
//      //Mpu_Ydat*=-1;
//      Flag_Y_Nega = 1;
//    }
//    else
//    {
//      Flag_Y_Nega = 0;
//    }
//    //�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
//		if(Mpu_Zdat < 0)
//    {
//      //Mpu_Zdat*=-1;
//      Flag_Z_Nega = 1;
//    }
//    else
//    {
//      Flag_Z_Nega = 0;
//    }
    //��ȡ������ �ͽ�������ʾ����
		Dis_Dat();
	}
}

//��ʾ ����
void Dis_Dat()
{
  //ֻ�����������˵�����ʾ��Ӧ����
	if(menu == 0 || menu == 1 || menu == 2)
	{
//    //�ж�������־λ  ��Ӧ��ʾ����
//    if(Flag_X_Nega)
//      LCD_Write_Char(9,0,'-');
//    else
//      LCD_Write_Char(9,0,' ');
    //�ڸ�������ʾ5λ�� ���� 
    LCD_Write_Number(10,0,Mpu_Xdat,5);
    
//    //�ж�������־λ  ��Ӧ��ʾ����
//    if(Flag_Y_Nega)
//      LCD_Write_Char(1,1,'-');
//    else
//      LCD_Write_Char(1,1,' ');
    //�ڸ�������ʾ5λ�� ���� 
    LCD_Write_Number(2,1,Mpu_Ydat,5);
    
//    //�ж�������־λ  ��Ӧ��ʾ����
//    if(Flag_Z_Nega)
//      LCD_Write_Char(9,1,'-');
//    else
//      LCD_Write_Char(9,1,' ');
    //�ڸ�������ʾ5λ�� ���� 
    LCD_Write_Number(10,1,Mpu_Zdat,5);
	}
}

//��ʾ����  ÿ���˵��Ľṹ
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

