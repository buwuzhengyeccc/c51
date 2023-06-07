/**
int Mpu_Xdat;
int Mpu_Ydat;
int Mpu_Zdat;

bit Flag_X_Nega;//0---正数  1---负数
bit Flag_Y_Nega;//0---正数  1---负数
bit Flag_Z_Nega;//0---正数  1---负数


//初始化 MPU6050模块  设置一些参数
InitMPU6050();


//根据menu获取对应数据   因为Menu 刚好是 0 1 2 对应了宏定义
Get_Mpu6050_Data(&Mpu_Xdat,&Mpu_Ydat,&Mpu_Zdat,menu);

//判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
if(Mpu_Xdat < 0)
{
  Mpu_Xdat*=-1;
  Flag_X_Nega = 1;
}
else
{
  Flag_X_Nega = 0;
}
//判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
if(Mpu_Ydat < 0)
{
  Mpu_Ydat*=-1;
  Flag_Y_Nega = 1;
}
else
{
  Flag_Y_Nega = 0;
}
//判断正负  如果是负数则Flag_X_Nega置1 并将数据转换为正数
if(Mpu_Zdat < 0)
{
  Mpu_Zdat*=-1;
  Flag_Z_Nega = 1;
}
else
{
  Flag_Z_Nega = 0;
}

//判断正负标志位  对应显示负号
if(Flag_X_Nega)
  LCD_Write_Char(9,0,'-');
else
  LCD_Write_Char(9,0,' ');
//在该坐标显示5位的 数据 
LCD_Write_Number(10,0,Mpu_Xdat,5);

//判断正负标志位  对应显示负号
if(Flag_Y_Nega)
  LCD_Write_Char(1,1,'-');
else
  LCD_Write_Char(1,1,' ');
//在该坐标显示5位的 数据 
LCD_Write_Number(2,1,Mpu_Ydat,5);

//判断正负标志位  对应显示负号
if(Flag_Z_Nega)
  LCD_Write_Char(9,1,'-');
else
  LCD_Write_Char(9,1,' ');
//在该坐标显示5位的 数据 
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
// 定义51单片机端口
//****************************************
sbit    SCL=P1^0;			//IIC时钟引脚定义
sbit    SDA=P1^1;			//IIC数据引脚定义

//偏移量
#define TYPE_ACCEL      0
//角速度
#define TYPE_GYRO       1
//角度
#define TYPE_ANGLE      2


//

void InitMPU6050();											

/*=============
【功 能】获取偏移量-角速度-角度
【参 数】X_Dat Y_Dat Z_Dat 传入变量地址，函数走完后你传入的参数里就有值了
         Type 获取哪种数据  传入宏定义 TYPE_ACCEL  TYPE_GYRO  TYPE_ANGLE
【备 注】数据有正负请注意  前三个参数 如果你传入的不是指针地址 
         就在你想传入的参数前加一个&(取址符)
================================================================*/
void Get_Mpu6050_Data(int *X_Dat, int *Y_Dat, int *Z_Dat, uchar Type);




#endif

