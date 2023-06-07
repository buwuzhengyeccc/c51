/*代码使用说明：
  LCD_Init();
  LCD_Clear();
  LCD_Write_String(0,0,"hello world!!");
  LCD_Write_Number(0,0,Dat,3);
*/
#include<reg52.h> //包含头文件，不需要改动!!!!!!!!!!!!!!!!!!!!!!!!!
#include<intrins.h>

#ifndef __LCD1602_H__
#define __LCD1602_H__

void DispStr(unsigned char x,unsigned char y,unsigned char *ptr);
void DispNChar(unsigned char x,unsigned char y, unsigned char n,unsigned char *ptr);
void LocateXY(unsigned char x,unsigned char y);
void Disp1Char(unsigned char x,unsigned char y,unsigned char data1);
void LcdReset(void);
void LcdWriteCommand(unsigned char cmd,unsigned char chk);
void LcdWriteData( unsigned char data1 );
void WaitForEnable(void);
void LcdClear(void);
void DispNum(unsigned char x, unsigned char y, unsigned int Dis_dat, unsigned char Dis_Len);

#define LCD_Init          LcdReset
#define LCD_Write_Char    Disp1Char
#define LCD_Write_String  DispStr
#define LCD_Clear         LcdClear
#define LCD_Write_Number	DispNum
   
#endif
