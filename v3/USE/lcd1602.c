#include "lcd1602.h"
#include "delay.h"
#include <intrins.h>
//#include <math.h>
#define uchar unsigned char
#define uint unsigned int

#define _NOP() _nop_()
#define DEBUG_LCD

#ifndef DEBUG_LCD
sbit RS = P2^5;   //����˿� 
sbit RW = P2^6;
sbit EN = P2^7;
#else
sbit RS = P2^6;   //����˿� 
sbit RW = P2^5;
sbit EN = P2^7;
#endif


#define DataPort    P0				
#define DataPIN     P0

#define CLR_RS (RS=0) 
#define SET_RS (RS=1)	
#define CLR_RW (RW=0)	
#define SET_RW (RW=1)
#define CLR_EN (EN=0)
#define SET_EN (EN=1)	


/*

��    �ܣ���Һ����ĳ��λ����������ʾһ����ֵ
��    ����x--λ�õ�������
          y--λ�õ�������
          Dis_dat--��Ҫ��ʾ����
					Dis_Len--��Ҫ��ʾ�Ŀ��
*/

void DispNum(uchar x, uchar y, uint Dis_dat, uchar Dis_Len)
{
	uchar i;
	uint dat = 1;
	Disp1Char(x+Dis_Len-1,y,Dis_dat%10+0x30);
	if(Dis_Len == 1)
		return;
	for(i = 1;i < Dis_Len;i++)
		dat*=10;
	for(i = 1; i < Dis_Len ; i++)
	{
		//dat = pow(10, Dis_Len-i);
		if(Dis_dat >= dat)
			Disp1Char(x+i-1,y,Dis_dat/dat%10+0x30);
		else
			Disp1Char(x+i-1,y,' ');
		dat/=10;
	}
}


/*
��    �ܣ���Һ����ĳ��λ����������ʾһ���ַ���
��    ����x--λ�õ�������
          y--λ�õ�������
          ptr--ָ���ַ������λ�õ�ָ��
*/
void DispStr(uchar x,uchar y,uchar *ptr) 
{
    uchar *temp;
    uchar i,n = 0;
    
    temp = ptr;
    while(*ptr++ != '\0')   n++;    //�����ַ�����Ч�ַ��ĸ���
    
    for (i=0;i<n;i++)
    {
        Disp1Char(x++,y,temp[i]);
        if (x == 0x10)
        {
            break;
        }
    }
}

/*
��    �ܣ���Һ����ĳ��λ����������ʾN���ַ�
��    ����x--λ�õ�������
          y--λ�õ�������
          n--�ַ�����
          ptr--ָ���ַ����λ�õ�ָ��
*******************************************
void DispNChar(uchar x,uchar y, uchar n,uchar *ptr) 
{
    uchar i;
    
    for (i=0;i<n;i++)
    {
        Disp1Char(x++,y,ptr[i]);
        if (x == 0x10)
        {
           x = 0; 
            y ^= 1;
        }
    }
}
*/
/*****
�������ƣ�LocateXY
��    �ܣ���Һ��������ʾ�ַ�λ�õ�������Ϣ
��    ����x--λ�õ�������
          y--λ�õ�������
********************************************/
void LocateXY(uchar x,uchar y) 
{
    uchar temp;

    temp = x&0x0f;
    y &= 0x01;
    if(y)   temp |= 0x40;  //����ڵ�2��
    temp |= 0x80;

    LcdWriteCommand(temp,1);
}

/**
��    �ܣ���ĳ��λ����ʾһ���ַ�
��    ����x--λ�õ�������
          y--λ�õ�������
          data--��ʾ���ַ�����
********************************************/
void Disp1Char(uchar x,uchar y,uchar data1) 
{
    LocateXY( x, y );			
    LcdWriteData( data1 );		
}

/***
��    �ܣ���1602Һ��ģ����и�λ����
**********/
void LcdReset(void) 
{
//    DataDir  = 0xFF;                 //���ݶ˿���Ϊ���״̬ 
    LcdWriteCommand(0x38, 0);	    //�涨�ĸ�λ����
    DelayMs(5);
    LcdWriteCommand(0x38, 0);		
    DelayMs(5);
    LcdWriteCommand(0x38, 0);
    DelayMs(5);

    LcdWriteCommand(0x38, 1);		//��ʾģʽ����
    LcdWriteCommand(0x08, 1);		//��ʾ�ر�
    LcdWriteCommand(0x01, 1);	    //��ʾ����
    LcdWriteCommand(0x06, 1);		//д�ַ�ʱ���岻�ƶ�
    LcdWriteCommand(0x0c, 1);		//��ʾ���������α꣬����˸
}

/*------------------------------------------------
                ��������
------------------------------------------------*/
void LcdClear(void) 
{ 
	LcdWriteCommand(0x01,1); 
	DelayMs(5);
}

/***
��    �ܣ���Һ��ģ��д������
��    ����cmd--���
          chk--�Ƿ���æ�ı�־��1����æ��0������
*************/
void LcdWriteCommand(uchar cmd,uchar chk) 
{

    if (chk) WaitForEnable();   // ���æ�ź�?
    
    CLR_RS;	
    CLR_RW; 
    _NOP();

    DataPort = cmd;             //��������д�����ݶ˿� 
    _NOP();					
    
    SET_EN;                     //����ʹ�������ź�
    _NOP();
    _NOP();
    CLR_EN;			
}

/**
��    �ܣ���Һ����ʾ�ĵ�ǰ��ַд����ʾ����
��    ����data--��ʾ�ַ�����
*******/
void LcdWriteData( uchar data1 ) 
{
    WaitForEnable();        //�ȴ�Һ����æ
    SET_RS;
    CLR_RW; 

    SET_EN;
	
	_NOP();
    DataPort = data1;        //����ʾ����д�����ݶ˿�
    _NOP();
                //����ʹ�������ź�
    _NOP(); 
    _NOP(); 
    CLR_EN;		
}

/***
��    �ܣ��ȴ�1602Һ������ڲ�����
****/
void WaitForEnable(void) 
{
  	unsigned int later=0;
	DataPort=0xff;
    CLR_RS;
    SET_RW;
    _NOP();
    SET_EN; 
    _NOP();
    _NOP();
//    while((DataPIN&Busy)!=0);    
    while(((DataPIN&0x80)!=0)&&(later<1000))  //���æ��־
    {
      DelayUs2x(2);
      later++;        
    }
    CLR_EN;
//    DataDir|=0xFF;  //��P4���л�Ϊ���״̬
}		

