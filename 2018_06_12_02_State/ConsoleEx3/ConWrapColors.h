/********************************************************************
  ConWrapColors.h

  Win32 �ܼ� ����� ����� ���� �������̽� / Header

  - ���� ����

********************************************************************/


#ifndef __CON_WRAPPER_COLORS__
#define __CON_WRAPPER_COLORS__



/////////////////////////////////////////////////
//
#define CONRGB(fore,back) ( (WORD)(fore|(back<<4)) )



/////////////////////////////////////////////////
// Visual C++ �̹� ���ǵǾ��ִ� ����

// FOREGROUND_BLUE,
// FOREGROUND_GREEN,
// FOREGROUND_RED,
// FOREGROUND_INTENSITY,
// 
// BACKGROUND_BLUE,
// BACKGROUND_GREEN,
// BACKGROUND_RED,
// BACKGROUND_INTENSITY



/////////////////////////////////////////////////
// ����� ���� ���� : ���� 0-15, ���  0-7 (�Ƹ���)

#define COLOR_ALL    16

#define BLACK		  0 //����
#define BLUE		  1 //�Ķ�
#define GREEN		  2 //�ʷ�
#define CYAN		  3 //�þ�   (�Ķ�+�ʷ�)
#define RED			  4 //����
#define MAGENTA		  5 //����Ÿ (�Ķ�+����)
#define BROWN		  6 //����   (�ʷ�+����)
#define LIGHTGRAY	  7 //���   (�Ķ�+�ʷ�+����)
#define DARKGRAY	  8 //ȸ��   (LIGHTBLACK) 
#define LIGHTBLUE	  9 //���� �Ķ�
#define LIGHTGREEN	 10 //���� ���
#define LIGHTCYAN	 11 //���� �þ�
#define LIGHTRED	 12 //���� ����
#define LIGHTMAGENTA 13 //���� ����Ÿ
#define YELLOW		 14 //���� ���
#define WHITE		 15 //���� �Ͼ��




#endif//__CON_WRAPPER_COLORS__