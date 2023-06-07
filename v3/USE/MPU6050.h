/**
int Mpu_Xdat;
int Mpu_Ydat;
int Mpu_Zdat;

bit Flag_X_Nega;//0---����  1---����
bit Flag_Y_Nega;//0---����  1---����
bit Flag_Z_Nega;//0---����  1---����


//��ʼ�� MPU6050ģ��  ����һЩ����
InitMPU6050();


//����menu��ȡ��Ӧ����   ��ΪMenu �պ��� 0 1 2 ��Ӧ�˺궨��
Get_Mpu6050_Data(&Mpu_Xdat,&Mpu_Ydat,&Mpu_Zdat,menu);

//�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
if(Mpu_Xdat < 0)
{
  Mpu_Xdat*=-1;
  Flag_X_Nega = 1;
}
else
{
  Flag_X_Nega = 0;
}
//�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
if(Mpu_Ydat < 0)
{
  Mpu_Ydat*=-1;
  Flag_Y_Nega = 1;
}
else
{
  Flag_Y_Nega = 0;
}
//�ж�����  ����Ǹ�����Flag_X_Nega��1 ��������ת��Ϊ����
if(Mpu_Zdat < 0)
{
  Mpu_Zdat*=-1;
  Flag_Z_Nega = 1;
}
else
{
  Flag_Z_Nega = 0;
}

//�ж�������־λ  ��Ӧ��ʾ����
if(Flag_X_Nega)
  LCD_Write_Char(9,0,'-');
else
  LCD_Write_Char(9,0,' ');
//�ڸ�������ʾ5λ�� ���� 
LCD_Write_Number(10,0,Mpu_Xdat,5);

//�ж�������־λ  ��Ӧ��ʾ����
if(Flag_Y_Nega)
  LCD_Write_Char(1,1,'-');
else
  LCD_Write_Char(1,1,' ');
//�ڸ�������ʾ5λ�� ���� 
LCD_Write_Number(2,1,Mpu_Ydat,5);

//�ж�������־λ  ��Ӧ��ʾ����
if(Flag_Z_Nega)
  LCD_Write_Char(9,1,'-');
else
  LCD_Write_Char(9,1,' ');
//�ڸ�������ʾ5λ�� ���� 
LCD_Write_Number(10,1,Mpu_Zdat,5);

******************************************************************/
#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "reg52.h"
#include <intrins.h> // _nop_();
#include <stdio.h>
#include <math.h>

#define uchar unsigned char
#define uint unsigned int


//****************************************
// ����51��Ƭ���˿�
//****************************************
sbit    SCL=P1^0;			//IICʱ�����Ŷ���
sbit    SDA=P1^1;			//IIC�������Ŷ���

//ƫ����
#define TYPE_ACCEL      0
//���ٶ�
#define TYPE_GYRO       1
//�Ƕ�
#define TYPE_ANGLE      2


//

void InitMPU6050();											

/*=============
���� �ܡ���ȡƫ����-���ٶ�-�Ƕ�
���� ����X_Dat Y_Dat Z_Dat ���������ַ������������㴫��Ĳ��������ֵ��
         Type ��ȡ��������  ����궨�� TYPE_ACCEL  TYPE_GYRO  TYPE_ANGLE
���� ע��������������ע��  ǰ�������� ����㴫��Ĳ���ָ���ַ 
         �������봫��Ĳ���ǰ��һ��&(ȡַ��)
================================================================*/
void Get_Mpu6050_Data(int *X_Dat, int *Y_Dat, int *Z_Dat, uchar Type);




#endif

