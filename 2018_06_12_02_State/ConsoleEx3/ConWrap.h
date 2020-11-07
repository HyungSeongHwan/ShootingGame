/********************************************************************
  ConWrap.h

  Win32 콘솔 입출력 사용자 설정 인터페이스 / Header

  Compiler : Visual C/C++ 6.0 & WIN32 Console API
  Platform : WINDOWS 9X/2000 /w SP3 
 ********************************************************************

  [] Update	

    * 2001.06.05 - 최초 작업
    * 2001.12.08 - 구조체/함수구조로 바꿈
    * 2002.03.15 - '캐릭터 버퍼' 추가
                 - 키보드/마우스 입력 수정
    * 2002.04.08 - 구조체 이름 전면 수정
												       by klayman@gs

    * 2002.10.05 - 키보드 루틴 수정.
	* 2002.11.10 - 콘솔 스크린 I/O 루틴 수정. 
	* 2002.11.11 - 마우스 / 2중버퍼 코드 수정 및 추가.
	* 2003.11.11 - 이후 변경 작업은 '개발 일지.txt' 참조.
													   by Mad_Dog
********************************************************************/

#pragma once
#ifndef __CONSOLE_WRAPPER__
#define __CONSOLE_WRAPPER__

#define WRAPPER_RELEASE_VERSION_		"WIN32 CONSOLE WRAPPER EX3.0"
#define WRAPPER_BUILD_VERSION_			"2003.01.26.23.00"

//@@/////////////////////////////////////////////////////////////////
// include
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <process.h> // for 'system()'



//@@/////////////////////////////////////////////////////////////////
// 콘솔 관련 헤더

#include "ConWrapColors.h"
#include "ConWrapDefines.h"

//	for PlaySound() 2003.01.05.2100
//  C/C++ 초심자를 위하여 선행처리기를 통한 
//  사운드 라이브러리를 로드한다.
#include "mmsystem.h"	
#pragma comment(lib, "winmm.lib")
 


//
// 더블 버퍼링 관련 헤더 파일. : 화면으로의 직업 렌더링 혹은 싱글 버퍼링은 '추천'하지 않는다. 
//
#if defined(_DOUBLE_BUFFER__)
#undef _DOUBLE_BUFFER__
#endif
#define _DOUBLE_BUFFER__	//더블 버퍼링...ON!!  



//@@/////////////////////////////////////////////////////////////////
// 구조체

// CONDISPLAY : 콘솔 디스플레이  /화면   ( Console Screen Buffer )
// CONBUFFER  : 콘솔 캐릭터 버퍼 /화면   ( Console Screen Character Buffer )
// CONINPUT   : 콘솔 입력 /키보드,마우스 ( Console Input )

typedef struct {

	HANDLE						hCS;
	CONSOLE_SCREEN_BUFFER_INFO	CSBufInfo;
   
} CONDISPLAY, *LPCONDISPLAY;


typedef struct {
	CHAR_INFO*	pBufArray;
	COORD		bufSize;
 
}CONBUFFER, *LPCONBUFFER;
 

typedef struct {

   HANDLE		hCI;
   INPUT_RECORD	InputRecord;
   COORD		MousePos;

} CONINPUT, *LPCONINPUT;



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 추가 전역변수. 
//
extern CONINPUT		g_Input;		//콘솔입력
extern CONDISPLAY	g_Display;		//콘솔 화면

#ifdef _DOUBLEBUFFER__
extern CONBUFFER	g_Buffers[2];
extern LPCONBUFFER	g_pPriBuffer, g_pBkBuffer;
#else
extern CONBUFFER	g_Buffer;		//콘솔 출력 문자버퍼.(80 * 25)개의 배열이다.
#endif
//SYSTIMER	g_Timer;


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  콘솔 I/O 관련.
//
//
// 마우스 키값 재정의 : 추후 업데이트 될 것임.
//
enum MOUSEBUTTON_ {
	MB_LEFT_,
	MB_MIDDLE_,
	MB_RIGHT_,

	MB_LCTRL_,
	MB_RCTRL_,
	MB_LSHIFT_,
	MB_RSHIFT_,
	MB_LALT_,
	MB_RALT_,

	MB_MAX_
};


//
// 마우스 좌표값 구조체.
// 
typedef struct {
	int x,y;
}MOUSEPT;

//
//  키보드 관련..
//
extern BYTE		g_KeyVal[256];				//키보드 값을 읽기위한 전역 배열. 2002.10.31. 기홍.
extern BYTE	 	g_KeyUpVal[256] ;		//KEY UP 되면 TRUE 셋팅.. 
extern MOUSEPT	g_MousePt;					//마우스 좌표값. 
extern DWORD	g_MouseVal[MB_MAX_];

#define IsKey(key) \
		(g_KeyVal[key]?TRUE:FALSE)			//키가 눌린상태면 TRUE 리턴. --> CONWRAP.H 

//
// 마우스 관련 루틴은 향후 업데이트 될것임.
//
#define IsMButtonDown(b) \
		(g_MouseVal[b]?TRUE:FALSE)			//특정 마우스 버튼이 눌리면 TRUE.

//
// 가상 키 코드 값. 
//
/* 일반 키보드 값 재정의 */
enum VIRTUALKEY_ {
	VK_0 = 0x30, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
	VK_A = 0x41, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J, VK_K, VK_L, 
	VK_M, VK_N, VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z 
};

/*  SHIFT/CONTROL/ALT(WINDOWS MENU) KEY 의 재정의 */
#define VK_RETURN         0x0D		//'ENTER' KEY.  VK_ENTER 는 사용 못함.

/* 밑의 3개의 가상키값은 VK_L*, VK_R* 등의 가상키 값을 사용 할 것을 권장한다.    */
/* UPDATE 2003.01.26.23.00														 */
//#define VK_SHIFT          0x10
//#define VK_CONTROL        0x11
//#define VK_MENU           0x12
#define VK_LSHIFT         0xA0		//SHIFT KEY.
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2		//CONTROL KEY.
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4		//MENU - ALT KEY.
#define VK_RMENU          0xA5 
#define VK_LALT			VK_LMENU	//VK_LMENU 보다는 VK_LALT 를 권장함.
#define VK_RALT			VK_RMENU


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 추가 함수.
//
//
// 2002. 11.11. 추가 함수는 EX3 계열 이상의 함수를 사용하는 것을 권장합니다. 
//              --> EX3 함수는 콘솔버퍼에 기록함.


//-------------------------------------------------------------------------------------------------------
// FPS 출력함수.
void PutFPS();


//-------------------------------------------------------------------------------------------------------
// Initial methods for Win32 Console API Wrappers.
void InitialConsole();
void ReleaseConsole();


//-------------------------------------------------------------------------------------------------------
//Screen Buffer methods.
BOOL DrawBuffer();										
WORD GetAttrEx3(int x, int y, BOOL bFromScreen);
UCHAR GetCharEx3(int x, int y, BOOL bFromScreen);

void ClearScreen(WORD bkcolor);
void ClearScreenEx3(WORD bkcolor);

void Blt();

//#ifdef _DOUBLE_BUFFER__
void Flip();
//#endif


//-------------------------------------------------------------------------------------------------------
//Input methods.
void GetMousePt();										 
void CheckInput();				//Check a Input Events.
void ClearInputData();			//2002. 11.14. added.l

BOOL IsAnyKey();				//2002. 11.13. added./  2002.11.15. edited.
BOOL IsKeyUp(int vk_val);		//2002. 11.14. / 2002. 11.15 edited.

#define NUMBER_ 1
#define STRING_ 0
//int GetStr(BOOL num , void* strbuff, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor);	
// add. 2002.11.21.
#define FAIL_GETNUMBER_ 0x80000000
int GetNumber(int* pNum, int x, int y);
//int GetNumber(int* pNum, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor); 
int GetString(char* pStr, int x, int y); 
//int GetString(char* pStr, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor);

//-------------------------------------------------------------------------------------------------------
//Drawing Methods.
BOOL DrawChar(int x, int y, char c, WORD fcolor, WORD bkcolor);
void DrawCharEx3(int x, int y, char c, WORD fcolor, WORD bkcolor);	
BOOL DrawStr(int x, int y, char* str, WORD fcolor, WORD bkcolor); 
void DrawStrEx3(int x, int y, char* str, WORD fcolor, WORD bkcolor);

void DrawHLine(int sx, int sy, int width, WORD bkcolor);
void DrawHLineEx(int sx, int sy, int width, WORD bkcolor);
void DrawHLineEx2(int sx, int sy, int width, UCHAR character, WORD fcolor, WORD bkcolor);
void DrawHLineEx3(int sx, int sy, int width, WORD bkcolor);
void DrawHLineCharEx3(int sx, int sy, int width, UCHAR character, WORD fcolor, WORD bkcolor);

void DrawVLine(int sx, int sy, int ey, WORD bkcolor);
void DrawVLineEx(int sx, int sy, int height, WORD bkcolor);
void DrawVLineEx2(int sx, int sy, int height, UCHAR character, WORD fcolor, WORD bkcolor);
void DrawVLineEx3(int sx, int sy, int height, WORD bkcolor);
void DrawVLineCharEx3(int sx, int sy, int height, UCHAR character, WORD fcolor, WORD bkcolor);

void DrawBox(int sx, int sy, int ex, int ey, WORD bkcolor);
void DrawBoxEx(int sx, int sy, int width, int height, WORD bkcolor); 
void DrawBoxEx2(int sx, int sy, int width, int height, UCHAR character, WORD fcolor, WORD bkcolor); 
void DrawBoxEx3(int sx, int sy, int width, int height, WORD bkcolor); 
void DrawBoxCharEx3(int sx, int sy, int width, int height, UCHAR character, WORD fcolor, WORD bkcolor);

void DrawFillBox(int sx, int sy, int ex, int ey, WORD bkcolor);
void DrawFillBoxEx(int sx, int sy, int width, int height, WORD bkcolor);
void DrawFillBoxEx2(int sx, int sy, int width, int height, UCHAR character, WORD fcolor, WORD bkcolor);
void DrawFillBoxEx3(int sx, int sy, int width, int height, WORD bkcolor);
void DrawFillBoxCharEx3(int sx, int sy, int width, int height, UCHAR character, WORD fcolor, WORD bkcolor);

void DrawBLine(int sx, int sy, int ex, int ey, char c, WORD fcolor, WORD bcolor);	//Not Available

/////////////////////////////////////////////////////////////////////////////////////////
// 
#define CP_KOREAN_		1
#define CP_ENGLISH_		0
void ChangeCodePage(BOOL bIsKorean);			//한글, 영문 코드 페이지 전환하기. TRUE 한글.. FALSE 영문..
void SetWindowTitle(const char* msg);

void EngineSync(DWORD frm);		//엔진을 원하는 프레임으로 동기화 시키기...
BOOL MsgBox(const char* msg);	//메세지 박스. 

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 

#define SND_PLAYONCE_   SND_ASYNC | SND_NODEFAULT 					//1번 출력. 
#define SND_PLAYNOSTOP_	SND_ASYNC | SND_NODEFAULT | SND_NOSTOP		//플레이 중이라면 그냥 리턴한다.
#define SND_PLAYLOOP_	SND_LOOP | SND_ASYNC | SND_NODEFAULT		//루프....

void PlaySound(const char* filename, unsigned int playtype);


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
// 함수정의 : by KlayMan  
//

//@@ 콘솔 디스플레이

void	CD_InitMember	( CONDISPLAY* pCD );

void	CD_Create		( CONDISPLAY* pCD, CODEPAGE codePage );
void	CD_Delete		( CONDISPLAY* pCD );

BOOL	CD_DrawChar		( CONDISPLAY* pCD, int x, int y, char c, WORD wColor );
BOOL	CD_DrawStr		( CONDISPLAY* pCD, int x, int y, char *str, WORD wColor );
BOOL	CD_FillChar		( CONDISPLAY* pCD, char c, WORD wColor );

void	CD_SetCodePage	( CODEPAGE codePage );
void	CD_SetTitle		( char* szTitle );




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//@@ 콘솔 캐릭터 버퍼

void	CB_InitMember	( CONBUFFER* pCB );
void	CB_Create		( CONBUFFER* pCB, int width, int height );
void	CB_Delete		( CONBUFFER* pCB );

BOOL	CB_DrawChar		( CONBUFFER* pCB, int bufX, int bufY, char c, WORD wColor );
BOOL	CB_DrawStr		( CONBUFFER* pCB, int bufX, int bufY, char* str, WORD wColor );

BOOL	CB_FillChar		( CONBUFFER* pCB, char c, WORD wColor );
BOOL	CB_Copy			( CONBUFFER* pCBSrc, int selX, int selY, int selW, int selH,
						  CONBUFFER* pCBDest, int destX, int destY );
BOOL	CB_ToDisplay	( CONBUFFER* pCB, int bufX, int bufY, int bufW, int bufH,
						  CONDISPLAY* pCD, int disX, int disY );



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//@@ 콘솔 입력

// 공통
void	CI_InitMember			( CONINPUT* pCI ); 

void	CI_Create				( CONINPUT* pCI ); 
void	CI_Delete				( CONINPUT* pCI ); 

void	CI_Read					( CONINPUT* pCI, READMODE readMode, RECMODE  recMode );

BOOL	CIK_IsAnyKey			( CONINPUT* pCI );
BOOL	CIK_IsVKey				( CONINPUT* pCI, DWORD dwVKey );
BOOL	CIK_IsAscii				( CONINPUT* pCI, char cAscii );
char	CIK_GetChar				( CONINPUT* pCI );


// 마우스
BOOL	CIM_IsMoved				( CONINPUT* pCI );

int		CIM_GetPosX				( CONINPUT* pCI );
int		CIM_GetPosY				( CONINPUT* pCI );

BOOL	CIM_IsButtonLeft		( CONINPUT* pCI );
BOOL	CIM_IsButtonRight		( CONINPUT* pCI );

//int	CIM_GetMoveX			( CONINPUT* pCI );
//int	CIM_GetMoveY			( CONINPUT* pCI );

//void	CIM_SetPosXY			( CONINPUT* pCI, int x, int y );


#endif//__CONSOLE_WRAPPER__


/********************************* end of file "conwrap.h" *********************************************/