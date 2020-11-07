/********************************************************************
  ConWrapColors.h

  Win32 콘솔 입출력 사용자 설정 인터페이스 / Header

  - 색상 관련

********************************************************************/


#ifndef __CON_WRAPPER_COLORS__
#define __CON_WRAPPER_COLORS__



/////////////////////////////////////////////////
//
#define CONRGB(fore,back) ( (WORD)(fore|(back<<4)) )



/////////////////////////////////////////////////
// Visual C++ 이미 정의되어있는 색상

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
// 사용자 지정 색상 : 전경 0-15, 배경  0-7 (아마도)

#define COLOR_ALL    16

#define BLACK		  0 //검정
#define BLUE		  1 //파랑
#define GREEN		  2 //초록
#define CYAN		  3 //시안   (파랑+초록)
#define RED			  4 //빨강
#define MAGENTA		  5 //마젠타 (파랑+빨강)
#define BROWN		  6 //갈색   (초록+빨강)
#define LIGHTGRAY	  7 //흰색   (파랑+초록+빨강)
#define DARKGRAY	  8 //회색   (LIGHTBLACK) 
#define LIGHTBLUE	  9 //밝은 파랑
#define LIGHTGREEN	 10 //밝은 녹색
#define LIGHTCYAN	 11 //밝은 시안
#define LIGHTRED	 12 //밝은 빨강
#define LIGHTMAGENTA 13 //밝은 마젠타
#define YELLOW		 14 //밝은 노랑
#define WHITE		 15 //밝은 하얀색




#endif//__CON_WRAPPER_COLORS__