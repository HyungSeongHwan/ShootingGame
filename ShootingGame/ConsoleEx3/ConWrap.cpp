/********************************************************************
  ConWrap.cpp

  Win32 콘솔 입출력 사용자 설정 인터페이스 / Implementation

  Compiler : Visual C/C++ 6.0 & Win32 Console API.
  Platfrom : WINDOWS 9X/2000 /w SP3. 
             It's not tested under WINDOWS ME/XP.

  원 본 렙퍼 : klayman808@hotmail.com
  1/2차 수정 : mad_dog3182@hotmail.com 
  3차 수정 : djdurk@homibox.com
********************************************************************/



#include "ConWrap.h"  //파일 패스 수정. 2002.10.31. 기홍.



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 전역 변수 
//
// 이하 변수들은  Wrapper 이외에서는 직접 접근의 필요가 없다.
//
DWORD		g_MouseVal[MB_MAX_] = { 0, };	//마우스 값.
MOUSEPT		g_MousePt = { 0, 0 };			//마우스 좌표값. 
BYTE		g_KeyVal[256] = { 0, };			//키 값.  
BYTE		g_KeyUpVal[256] = { YES_, };		//KEY UP 되면 TRUE 셋팅..

CONINPUT	g_Input;						//콘솔입력
CONDISPLAY	g_Display;						//콘솔 화면

 
#ifdef _DOUBLE_BUFFER__
CONBUFFER	g_Buffers[2]; 					//더블 버퍼링을 위한 변수들.
LPCONBUFFER	g_pPriBuffer = NULL;			//백버퍼 포인터...
LPCONBUFFER g_pBkBuffer = NULL;				//프라이 머리 포인터.
#else
CONBUFFER	g_Buffer;						//콘솔 출력 문자버퍼.(80 * 25)개의 배열이다.
#endif
//SYSTIMER	g_Timer;						//2002.11.11.일단 사용하지 않음.



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//								   //	
// 추가 함수. 2002. 11.05. 기홍.   //
//                                 //
/////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
// 
//  FPS 출력함수. : 2003.7.3. 김기홍 
//
void PutFPS()
{
	static int oldtime = 0; 
	static int frmcnt = 0; 
	static float fps = .0;

	frmcnt++;
	int time = GetTickCount() - oldtime;
	if(time > 1000)
	{
		oldtime = GetTickCount();
		fps = (float)((float)(frmcnt*1000)/(float)time);
		frmcnt = 0;
	}
		
	char msg[80] = ""; sprintf(msg, "FPS=%.2f", fps);
	DrawStrEx3(0, 0, msg, RED, WHITE);			//최신 버전으로 업!
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void InitialConsole() : 콘솔 초기화 함수. - 프로그램 시작부분에서 제일 먼저 호출해야 한다.
//
// 리턴값 : 없음  
// 인  자 : 없음
//
void InitialConsole()
{
	CD_InitMember(&g_Display);
	CD_Create(&g_Display, ENG);

	CI_InitMember(&g_Input);
	CI_Create(&g_Input);

#ifdef _DOUBLE_BUFFER__
	for(int i=0; i<2; i++)
	{
		CB_InitMember(&g_Buffers[i]);
		CB_Create(&g_Buffers[i], CON_W, CON_H);
	}
	 
	//백버퍼의 포인터 할당.
	g_pBkBuffer = &g_Buffers[1];		//0: Primary, 1: secondary/backbuffer.
	g_pPriBuffer = &g_Buffers[0];

#else
	CB_InitMember(&g_Buffer);
	CB_Create(&g_Buffer, CON_W, CON_H);
#endif

	//키보드 값 셋팅.
	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));
	memset(g_KeyUpVal, YES_, sizeof(g_KeyUpVal));
	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));  
	g_MousePt.x = 0; 
	g_MousePt.y = 0;  


}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void ReleaseConsole() : 콘솔 제거 함수. - 프로그램 종료시 꼭 호출해야 함.
//
// 리턴값 : 없음  
// 인  자 : 없음
//
void ReleaseConsole()
{
	CD_Delete(&g_Display);
	CI_Delete(&g_Input);

#ifdef _DOUBLE_BUFFER__
	for(int i=0; i<2; i++)
	{
		CB_Delete(&g_Buffers[i]);
	}

	g_pPriBuffer = NULL;
	g_pBkBuffer = NULL;
		 
#else
	CB_Delete(&g_Buffer);
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  int GetNumber() : 콘솔입력 스트림에서 부호있는 정수형 값을 입력 받는다.
//
//  인자 : int형 포인터 pNum, ECHO 출력좌표 x,y
//  리턴값 : 성공하면 pNum 의 값, 실패하면 0x80000000 
//
int GetNumber(int* pNum, int x, int y) 
{
	COORD pos = { x, y};
	SetConsoleCursorPosition(g_Display.hCS, pos);

	if(scanf("%d", pNum) == 0)		//실패시...
	{
		//_flushall();				//stream  buffer  클리어.
		*pNum = FAIL_GETNUMBER_ ;	//0x80000000; 변수값 초기화...(음의 최대값 : -2147483648)
	}
	
	_flushall();				//stream  buffer  클리어.
	return *pNum;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// int GetString() : 콘솔입력 스트림에서 문자열을 입력 받는다.
//
// 인자 : 문자열 포인터, ECHO 출력좌표 x,y
// 리턴값 : 실제로 읽어 들인 문자열의 길이.(byte 단위)
//
int GetString(char* pStr, int x, int y)  
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(g_Display.hCS, pos);

	gets_s(pStr, sizeof(pStr));
	//canf("%s", pStr);
	 
	_flushall();

	return strlen(pStr);
}

/*
int GetString2(char* pStr, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(g_Display.hCS, pos);

	//gets(pStr);
	scanf("%s", pStr);
	
	char echo[80] = "";

	if(bIsEcho)
	{
		sprintf(echo, "%s", pStr);

		if(bIsScreen) DrawStr(x, y, echo, fcolor, bkcolor);
		else{  DrawStrEx3(x, y, echo, fcolor, bkcolor); Flip(); }
	}

	return strlen(pStr);
}

/*int GetStr(BOOL bIsNum, void* strbuff, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor)
{
	COORD coord = {x, y};

	SetConsoleCursorPosition(g_Display.hCS, coord);

 	int readcnt = 0;   
 	//readcnt = 
		//gets(strbuff);
	if(bIsNum) scanf("%d", (int*)strbuff);
	else gets((char*)strbuff);

  
	if(bIsEcho)
	{
		if(bIsScreen)
		{
			//ClearScreen(BLACK);
			if(bIsNum == NUMBER_)	
			{
				char temp[80]="";
				_itoa( *(int*)strbuff, temp, 10 );
				DrawStr(x, y, temp, fcolor, bkcolor);
			}
			else
			{	DrawStr(x, y, (char*)strbuff, fcolor, bkcolor);
			}
			
			
		}
		else
		{
			//ClearScreenEx3(BLACK);
			if(bIsNum == NUMBER_)	
			{
				char temp[80]="";
				_itoa( *((int*)strbuff), temp, 10 );
				DrawStrEx3(x, y, temp, fcolor, bkcolor);
			}
			else
			{	DrawStrEx3(x, y, (char*)strbuff, fcolor, bkcolor);
			}
			//DrawStrEx3(x, y, (char*)strbuff, fcolor, bkcolor);
		}
	}

	return  readcnt;
}

int GetStrold(char* strbuff, BOOL bIsEcho, BOOL bIsScreen, int x, int y, WORD fcolor, WORD bkcolor)
{
	COORD coord = {x, y};

	SetConsoleCursorPosition(g_Display.hCS, coord);

 	int readcnt = 0;   
 	//readcnt = 
		gets(strbuff);
 
	if(bIsEcho)
	{
		if(bIsScreen)
		{
			ClearScreen(BLACK);
			DrawStr(x, y, strbuff, fcolor, bkcolor);
		}
		else
		{
			ClearScreenEx3(BLACK);
			DrawStrEx3(x, y, strbuff, fcolor, bkcolor);
		}
	}

	return  readcnt;
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  BOOL DrawChar(..)	: 문자 출력 함수.
//
//  인자값 : 출력 좌표 (x, y), 출력할 문자 , 문자 색, 문자 배경색.
//  리턴값 : 성공 TRUE , 실패 FALSE
//
BOOL DrawChar(int x, int y, char c, WORD fcolor, WORD bcolor)
{
		// check - 클립핑.
	//if(( x < 0 ) || ( x > CON_W -1 )|| ( y < 0 ) || ( y > CON_H -1 )) 	return FALSE;
	if( x<0 || x>= CON_W || y<0 || y>= CON_H )
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : 경고! *  DrawChar() 좌표 오류 : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return FALSE;			//클립핑 코드는 수정필요.
	}

	SetConsoleTextAttribute(g_Display.hCS, CONRGB(fcolor, bcolor));

	COORD pos = {x, y};			//커서 위치 - 즉 출력할 문자의 위치....
	BOOL res = SetConsoleCursorPosition(g_Display.hCS, pos);
	
	printf("%c", c);

	return res;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  void DrawChar(...)	: 문자 출력 함수.- 스크린 버퍼링시 사용해야 함.
//
//  인자값 : 출력 좌표 (x, y), 출력할 문자 , 문자 색, 문자 배경색.
//  리턴값 : 없음.
//
void DrawCharEx3(int x, int y, char c, WORD fcolor, WORD bcolor)
{
//클립핑 코드 필요.
	if(x<0 || x >= CON_W || y<0 || y >= CON_H)
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : 경고! *  DrawCharEx3() 좌표 오류 : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return;	
	}
	
#ifdef _DOUBLE_BUFFER__
	int pos = g_pBkBuffer->bufSize.X * y + x;
 

	g_pBkBuffer->pBufArray[pos].Char.AsciiChar = c;
	g_pBkBuffer->pBufArray[pos].Attributes = CONRGB(fcolor, bcolor);
	 
#else
	int pos = g_Buffer.bufSize.X * y + x;
  
	g_Buffer.pBufArray[pos].Char.AsciiChar = c;
	g_Buffer.pBufArray[pos].Attributes = CONRGB(fcolor, bcolor);

#endif
	 
}//end of void DrawCharEx3(..)




////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WORD GetAttr(...) : 속성읽어 오기.  실패해도 '검은색'은 리턴하게 된다. 
//
// 인자값 : 읽어올 x, y좌표, 화면에서 읽어올경우 TRUE / 버퍼에서 읽어올경우 FALSE
// 리턴값 : x,y좌표상의 속성값.
//
WORD GetAttrEx3(int x, int y, BOOL bFromScreen)
{
	if( x< 0 || x >= CON_W || y < 0 || y >= CON_H) return 0x00;

	WORD attr = 0x00;
 
	if(bFromScreen)
	{
		DWORD readnum=0;
		COORD pos = { x, y};
		ReadConsoleOutputAttribute( //콘솔 스크린의 속성을 읽어온다.
			g_Display.hCS, &attr, 1, pos, &readnum);
	}
	else
	{
#ifdef _DOUBLE_BUFFER__						//더블 버퍼링시 '백버퍼'에서 읽어온다.
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	attr =  g_pBkBuffer->pBufArray[pos].Attributes;
#else
	int pos = g_Buffer.bufSize.X * y + x;
	attr = g_Buffer.pBufArray[pos].Attributes; 
#endif
	}

	return attr>>4;

}//end of void GetAttr(..)


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WORD GetCharEx3() : 문자값 읽어 오기.  실패해도 'NUL' 은 리턴하게 된다. 
//
// 인자값 : 읽어올 x, y좌표, 화면에서 읽어올경우 TRUE / 버퍼에서 읽어올경우 FALSE
// 리턴값 : x,y좌표상의 속성값.
//
UCHAR GetCharEx3(int x, int y, BOOL bFromScreen)
{
	if( x< 0 || x >= CON_W || y < 0 || y >= CON_H)
		return 0x00;

	UCHAR Char = 0x00;
 
	if(bFromScreen)
	{
		DWORD readnum=0;
		COORD pos = { x, y};
		ReadConsoleOutputCharacter(					//콘솔 스크린의 속성을 읽어온다.
			g_Display.hCS, (LPSTR)&Char, 1, pos, &readnum);
	}
	else
	{
#ifdef _DOUBLE_BUFFER__								//더블 버퍼링시 '백버퍼'에서 읽어온다.
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	Char =  g_pBkBuffer->pBufArray[pos].Char.AsciiChar; 
#else
	int pos = g_Buffer.bufSize.X * y + x;			//싱글 버퍼링시 '단순 버퍼' 에서 읽어 온다.
	Char = g_Buffer.pBufArray[pos].Char.AsciiChar; 
#endif
	}

	return Char;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	BOOL IsAnyKey(void) : 키반응이 있다면 TRUE를 리턴한다
//
//  2002.11.13. 추가.
//
BOOL IsAnyKey(void)
{
	//BOOL res = 0;
	for(int i=0; i<256; i++)
	{
		if(g_KeyVal[i]) return TRUE; 
	}

	return FALSE; //(g_Input.InputRecord.Event.KeyEvent.bKeyDown)?TRUE:FALSE;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  BOOL DrawStr(...) : 문자열 출력함수.
//
//  인자값 : 출력 좌표 (x, y), 출력할 문자열 포인터 , 문자 색, 문자 배경색.
//  리턴값 : 성공 TRUE , 실패 FALSE
//
BOOL DrawStr(int x, int y, char* str, WORD fcolor, WORD bcolor)
{
 	// 문자열 클립핑. -------------------------------------------
	//if( x < 0 || x>= CON_W || y<0 || y>= CON_H)				// 문자열 시작 좌표 크립핑..1ST. 
	if( x >= CON_W || y<0 || y >= CON_H)						 
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : 경고! *  DrawStr() 좌표 오류 : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return FALSE;
	}
	
	int old_len = strlen(str), new_len = old_len;
	char msg[80] = "";
 
	if( x>= 0 && x < CON_W)									//x축으로 con_w 이상 잘릴경우...
	{
 		if( x + old_len > CON_W )							// 문자열이 화면 밖으로 잘릴경우...2ND. 전체 문자열에서 잘린 길이를 뺀후, 출력할 문자열 길이를 계산한다. 	
			new_len = CON_W - x; //old_len - (x + old_len - CON_W);

		strncpy(msg, str, new_len);
	}
	else if( x < 0)										// x 축 0 이하로 잘릴경우...
	{
		if( old_len <=  abs(x)) return FALSE;			//클립핑 영역보다 문자열이 작다면 출력하지 않는다.
		 
		strcpy(msg, str + abs(x)); //new_len);
		x = 0;											//출력좌표 보정.
	}

	
	//-----------------------------------------------------------
 
	SetConsoleTextAttribute(g_Display.hCS, CONRGB(fcolor, bcolor));

	 
	COORD pos = {x, y};
	BOOL res = SetConsoleCursorPosition(g_Display.hCS, pos);

 	printf("%s", msg);	//for clipping routine.
	//printf("%s", str);

	return res;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  BOOL DrawStrEx3(...) : 문자열 출력함수.
//
//  인자값 : 출력 좌표 (x, y), 출력할 문자열 포인터 , 문자 색, 문자 배경색.
//  리턴값 : 없음.
//
void DrawStrEx3(int x, int y, char* str, WORD fcolor, WORD bcolor)
{
	if( x >= CON_W || y<0 || y>= CON_H)
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : 경고! *  DrawStrEx3() 좌표 오류 : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return;					//클립핑 시작 좌표. 1st.
	}

	int old_len = strlen(str);
	int new_len = old_len;
	char temp[80] = ""; 
	
	
	if( x >= 0 && x < CON_W)		//x축이 CON_W 보다 클 경우...
	{
		if((x + old_len) > CON_W)
			new_len =  CON_W - x ; //old_len - (x + old_len - CON_W);
		strncpy(temp, str, new_len);
	}
	else if( x < 0)	//x축 0 보다 작은 경우..클립핑...
	{
		 
		if( old_len <= abs(x) )		//출력할 문자열길이 보다 출력 좌표가 더 마이너스 값이라면... 
			return;
		strcpy(temp, str + abs(x));   //temp += (x);				//문자열 주소 보정..
 		x = 0;						//출력 좌표 보정.
	}
	
#ifdef _DOUBLE_BUFFER__
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	int len = strlen(temp);

	for( int i=0; i<len; i++)
	{
//		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//문자열 클립핑  X축 con_w 보다 클경우 2nd.
		
		g_pBkBuffer->pBufArray[pos + i].Char.AsciiChar = temp[i]; //str[i];
		g_pBkBuffer->pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}

#else
	int pos = g_Buffer.bufSize.X * y + x;
	int len = strlen(str);

	for( int i=0; i<len; i++)
	{
 //		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//문자열 클립핑 X 축 2nd.

		g_Buffer.pBufArray[pos + i].Char.AsciiChar = str[i];
		g_Buffer.pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}
#endif

}

/*
#ifdef _DOUBLE_BUFFER__
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	int len = strlen(str);

	for( int i=0; i<len; i++)
	{
		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//문자열 클립핑  X축 2nd.

		g_pBkBuffer->pBufArray[pos + i].Char.AsciiChar = str[i];
		g_pBkBuffer->pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}

#else
	int pos = g_Buffer.bufSize.X * y + x;
	int len = strlen(str);

	for( int i=0; i<len; i++)
	{
 		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//문자열 클립핑 X 축 2nd.

		g_Buffer.pBufArray[pos + i].Char.AsciiChar = str[i];
		g_Buffer.pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}
#endif
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLine(...) : 수평선 그리기. 
// 
//인자 : 시작 위치 (sx, sy),  끝 위치 ex , 선 색상 color
//리턴 : 없음.
//
// 사용하지 않음. ex 이상의 함수를 사용할것. 이전버전의 호환성을 위해 남겨둠.
//
void DrawHLine(int sx, int sy, int ex, WORD color)
{
	// Not Available. Use a enhanced functions : DrawHLineEx, DrawHLineEx2 or DrawHLineEx3
	OutputDebugString("** DrawHLine() : Not Available. Use a enhanced functions : DrawBoxEx, DrawBoxEx2\n");
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLinEx(...) : 수평선 그리기. 
// 
// 인자 : 시작 위치(sx,sy) , 수평선의 길이 width, 선 색상 color
// 리턴 : 없음.
//
// 콘솔 스크린으로 바로 출력 : 문자값 없이 배경색만 출력.
//
// 2002. 11.13. 클립핑 ok! 하지만 사용하지는 않음. 
void DrawHLineEx(int sx, int sy, int width, WORD color)
{
	// 클립핑 코드.
	//if(sx < 0 || sx >= CON_W || sy < 0 || sy >= CON_H) return;		//1st clipping
	//int new_width = width;
	//if(sx + width >= CON_W)  new_width = width - (sx + width - CON_W);		//2nd clipping

	COORD sp = {sx, sy};
	DWORD dwWritten;
	FillConsoleOutputAttribute(g_Display.hCS, CONRGB(BLACK, color),	width, sp, &dwWritten);
	FillConsoleOutputCharacter(g_Display.hCS, ' ', width , sp, &dwWritten);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLinEx2(...) : 수평선 그리기. 
// 
// 인자 : 시작 위치(sx,sy) , 수평선의 길이 width,  출력 문자값 , 문자 색상 fcolor, 문자 배경 bcolor
// 리턴 : 없음.
//
//
// 콘솔 스크린으로 바로 출력 : 문자값 출력가능.
//
void DrawHLineEx2(int sx, int sy, int width, char c, WORD fcolor, WORD bcolor)
{
	COORD sp = {sx, sy};
	DWORD dwWritten;
	FillConsoleOutputAttribute(g_Display.hCS, CONRGB(fcolor, bcolor), width, sp, &dwWritten);
	FillConsoleOutputCharacter(g_Display.hCS, c, width, sp, &dwWritten);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLinEx3(...) : 수평선 그리기. 
// 
// 인자 : 시작 위치(sx,sy) , 수평선의 길이 width, 선 색상 color
// 리턴 : 없음.
//
//
// 버퍼에 수평선 출력 : 버퍼링시 사용해야함.
//
void DrawHLineEx3(int sx, int sy, int width, WORD bkcolor)
{
 	for(int i=0; i<width; i++)
	{
		DrawCharEx3(sx + i, sy, ' ', BLACK, bkcolor);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLinCharEx3(...) : 문자가 있는 수평선 그리기. 
// 
// 인자 : 시작 위치(sx,sy) , 수평선의 길이 width, 문자값 Char, 문자색상 fcolor,  선 색상 bkcolor
// 리턴 : 없음.
//
//
// 버퍼에 수평선 출력 : 버퍼링시 사용해야함.
//
void DrawHLineCharEx3(int sx, int sy, int width, UCHAR Char, WORD fcolor, WORD bkcolor)
{
	for(int i=0; i<width; i++)
	{
		DrawCharEx3(sx + i, sy, Char, fcolor, bkcolor);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLin(...) : 수직선 그리기. 
// 
// 인자 : 시작 위치(sx,sy) , 수직선의 끝점 ey , 선 색상 color
// 리턴 : 없음.
//
void DrawVLine(int sx, int sy, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawVLineEx, DrawVLineEx2 or DrawVLineEx3
	 
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLinEx(...) : 수직선 그리기, 콘솔 스크린에 바로 출력.
// 
// 인자 : 시작 위치(sx,sy) , 수직선의 폭. height, 선 색상  bkcolor
// 리턴 : 없음.
//
void DrawVLineEx(int sx, int sy, int height, WORD bkcolor)
{
 	SetConsoleTextAttribute(g_Display.hCS, CONRGB(BLACK, bkcolor));
	COORD pos;

	for(int j=0; j<height; j++)
	{
 		pos.X = sx; pos.Y = sy+j;
		SetConsoleCursorPosition(g_Display.hCS, pos);
		printf("%c", ' ');
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLinEx2(...) : 수직선 그리기.- 콘솔 스크린에 바로 출력 문자값 포함.
// 
// 인자 : 시작 위치(sx,sy) , 수직선의 폭. height, 문자값 c, 문자 색상 fcolor, 선 색상 bkcolor
// 리턴 : 없음.
//
void DrawVLineEx2(int sx, int sy, int height, char c, WORD fcolor, WORD bkcolor)
{
	SetConsoleTextAttribute(g_Display.hCS, CONRGB(fcolor, bkcolor));
	COORD pos;

	for(int j=0; j<height; j++)
	{
 		pos.X = sx; pos.Y = sy+j;
		SetConsoleCursorPosition(g_Display.hCS, pos);
		printf("%c", c); 
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLinEx3(...) : 수직선 그리기.- 콘솔 버퍼에 출력.
// 
// 인자 : 시작 위치(sx,sy) , 수직선의 폭. height, 선 색상 color
// 리턴 : 없음.
//
void DrawVLineEx3(int sx, int sy, int height, WORD bkcolor)
{
 	for(int i=0; i<height; i++)
	{
		DrawCharEx3(sx, sy+i, ' ', BLACK, bkcolor);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLinCharEx3(...) : 문자가 있는 수직선 그리기.- 콘솔 버퍼에 출력.
// 
// 인자 : 시작 위치(sx,sy) , 수직선의 폭. height, 문자값 Char, 문자 색상 fcolor, 선 색상 color
// 리턴 : 없음.
//
void DrawVLineCharEx3(int sx, int sy, int height, UCHAR Char, WORD fcolor, WORD bkcolor)
{
 	for(int i=0; i<height; i++)
	{
		DrawCharEx3(sx, sy+i, Char, fcolor, bkcolor);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBox(...) : 박스 그리기 - 스크린에 바로출력.
// 
//  인자 : 박스 좌측상단 좌표 ( sx, sy), 박스 좌측하단 좌표(ex, ey), 선 색상 color
//  리턴 : 없음.
//
void DrawBox(int sx, int sy, int ex, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawBoxEx, DrawBoxEx2 or DrawBoxEx3
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBoxEx(...) : 박스 그리기 - 스크린에 바로출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 선 색상 color
//  리턴 : 없음.
//
void DrawBoxEx(int sx, int sy, int width, int height, WORD color)
{
	DrawHLineEx(sx, sy, width, color); 
	DrawHLineEx(sx, sy+height-1, width, color);
	DrawVLineEx(sx, sy, height, color);
	DrawVLineEx(sx+width-1, sy, height, color);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBoxEx2(...) : 박스 그리기 - 스크린에 바로출력. 문자값 포함.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 
//         박스 너비 width, 박스 높이 height, 문자 값 c, 문자 색 fcoor, 선 색상 bkcolor
//  리턴 : 없음.
//
void DrawBoxEx2(int sx, int sy, int width, int height, char c, WORD fcolor, WORD bkcolor)
{
	DrawHLineEx2(sx, sy, width, c, fcolor, bkcolor);
	DrawHLineEx2(sx, sy+height-1, width, c, fcolor, bkcolor);
	DrawVLineEx2(sx, sy, height, c, fcolor, bkcolor);
	DrawVLineEx2(sx+width-1, sy, height, c, fcolor, bkcolor);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBoxEx3(...) : 박스 그리기 - 콘솔 버퍼에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 선 색상 color
//  리턴 : 없음.
//
void DrawBoxEx3(int sx, int sy, int width, int height, WORD bkcolor)
{
	DrawHLineEx3(sx, sy, width, bkcolor);
	DrawHLineEx3(sx, sy+height-1, width, bkcolor);
	DrawVLineEx3(sx, sy, height, bkcolor);
	DrawVLineEx3(sx+width-1, sy, height, bkcolor);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBoxCharEx3(...) : 문자가 있는 박스 그리기 - 콘솔 버퍼에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 문자값 Char, 문자 색상 fcolor, 선 색상 bkcolor
//  리턴 : 없음.
//
void DrawBoxCharEx3(int sx, int sy, int width, int height, UCHAR Char, WORD fcolor, WORD bkcolor)
{
	DrawHLineCharEx3(sx, sy, width, Char, fcolor, bkcolor);
	DrawHLineCharEx3(sx, sy+height-1, width, Char, fcolor, bkcolor);
	DrawVLineCharEx3(sx, sy, height, Char, fcolor, bkcolor);
	DrawVLineCharEx3(sx+width-1, sy, height, Char, fcolor, bkcolor);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBox(...) : 채워진 박스 그리기 - 스크린에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 우측 하단 좌표(ex, ey), 선 색상 color
//  리턴 : 없음.
//
void DrawFillBox(int sx, int sy, int ex, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawFillBoxEx , DrawFillBoxEx2 or DrawFillBoxEx3 
	OutputDebugString("** DrawFillBox : Not Available. Use a enhanced functions : DrawFillBoxEx , DrawFillBoxEx2\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx(...) : 채워진 박스 그리기 - 스크린에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 선 색상 color
//  리턴 : 없음.
//
void DrawFillBoxEx(int sx, int sy, int width, int height, WORD color)
{
	for(int i=0; i<height; i++)
		DrawHLineEx(sx, sy+i, width, color);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx2(...) : 채워진 박스 그리기 - 스크린에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 
//		   박스 너비 width, 박스 높이 height, 문자 값 c, 문자 색상 fcolor, 선 색상 bcolor
//  리턴 : 없음.
//
void DrawFillBoxEx2(int sx, int sy, int width, int height, char c, WORD fcolor, WORD bcolor)
{
	for(int i=0; i<height; i++)
		DrawHLineEx2(sx, sy+i, width, c, fcolor, bcolor);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx3(...) : 채워진 박스 그리기 - 콘솔 버퍼에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 선 색상 color
//  리턴 : 없음.
//
void DrawFillBoxEx3(int sx, int sy, int width, int height, WORD bcolor)
{
	for(int i=0; i<height; i++)
		DrawHLineEx3(sx, sy+i, width, bcolor);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxCharEx3(...) : 문자가 있는 채워진 박스 그리기 - 콘솔 버퍼에 출력.
// 
//  인자 : 박스 좌측상단 좌표 (sx, sy), 박스 너비 width, 박스 높이 height, 
//			문자 값 Char, 문자 색상 fcolor, 선 색상 bkcolor
//  리턴 : 없음.
//
void DrawFillBoxCharEx3(int sx, int sy, int width, int height, UCHAR Char, WORD fcolor, WORD bkcolor)
{
	for(int i=0; i<height; i++)
		DrawHLineCharEx3(sx, sy+i, width, Char, fcolor, bkcolor);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Not Available. Do not use.
//void line2( int x1, int y1, int x2, int y2, char color )
void DrawBLine(int x1, int y1, int x2, int y2, char c, WORD fcolor, WORD bcolor)
{
	int x, y; //, temp;
	int delta_x, delta_y, half, error = 0;
  
	/* 항상 x2 >= x1, y2 > y1 이 되도록 한다. */
	 if( x1 > x2 )
	 {
  		 x1 ^= x2;	 x2 ^= x1;	 x1 ^= x2;
	 }

	 if( y1 > y2 )
	 {
  		y1 ^= y2;		 y2 ^= y1;		 y1 ^= y2;
 	 }
      
	/* x, y의 변화량을 구한다. */
	delta_x = x2 - x1;
	delta_y = y2 - y1;
//	delta_x = abs(x2 - x1);
//	delta_y = abs(y2 - y1);

  
	/* 처음 시작점을 찍는다. */
	//put_pixel( x1, y1, color );
	DrawChar(x1, y1, c, fcolor, bcolor);

	/* 각 좌표의 기울에 따라 선을 긋는다. */
	if( delta_x > delta_y )
	{
		y = y1;
		half = (int)( delta_x / 2 );

		for( x = x1+1; x <= x2; x++ )
		{
			error += delta_y;
			if( error > half )
			{
				y++;
				error -= delta_x;
			}
				//put_pixel( x, y, color );
			DrawChar(x, y, c, fcolor, bcolor);
		}

	} 
	else 
	{
		x = x1;
		half = (int)( delta_y / 2 );

		for( y = y1+1; y <= y2; y++ )
		{
			error += delta_x;
			if( error > half )
			{
				x++;
				error -= delta_y;
			}
			//put_pixel( x, y, color );
			DrawChar(x, y, c, fcolor, bcolor);
		}
   }
}//end of DrawBLine() 




/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void ClearScreen(...) : 원하는 색상으로 화면 클리어 하기. 
// 
//  인자 : 화면을 '클리어' 할 색상 bkcolor 
//  리턴 : 없음.
//
void ClearScreen(WORD bkcolor)
{
	COORD sp = { 0, 0};
	DWORD dwWritten;

	FillConsoleOutputAttribute( g_Display.hCS, CONRGB(BLACK, bkcolor), 
								CON_W*CON_H, sp, &dwWritten);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void ClearScreenEx3(...) : 원하는 색상으로  스크린 버퍼 클리어 하기. 
// 
//  인자 : 화면을 '클리어' 할 색상 bkcolor 
//  리턴 : 없음.
//
void ClearScreenEx3(WORD bkcolor)
{
	 CHAR_INFO temp;
	 temp.Char.AsciiChar = ' '; 
	 temp.Attributes = CONRGB(BLACK, bkcolor);

	 int size = CON_W * CON_H;


	 for(int i=0; i<size; i++)
	 {
#ifdef _DOUBLE_BUFFER__
		 g_pBkBuffer->
#else
		 g_Buffer.
#endif
			 pBufArray[i] = temp;
	 }
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void Flip() :  더블/싱글 버퍼링 시에만 사용.
//
// 인자 : 없음.
// 리턴 : 없음.
//

void Flip()
{
#ifdef _DOUBLE_BUFFER__
	static int flipcnt = 0;
	g_pBkBuffer = &g_Buffers[flipcnt];						//백버퍼 포인터 스왑.
	g_pPriBuffer = &g_Buffers[flipcnt^=1];

#ifdef _DEBUG
	char msg[80]; sprintf(msg, "p:0x%08x, b:0x%08x", g_pPriBuffer, g_pBkBuffer);
	//DrawStr(0, 24, msg, WHITE, BLACK); 
	//Sleep(500);
	strcat(msg, "\n");	
	OutputDebugString(msg);
#endif //_DEBUG

#endif // _DOUBLE_BUFFER__		
 
	DrawBuffer();											//프라이머리->화면 복사.		
}//end of void Flip()




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void Blt(void) : 백퍼의 내용을 프라이머리 버퍼에 복사한다. 
//
void Blt(void)
{
	//n/a
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOOL DrawBufer(void) : 버퍼의 내용을 화면에 그린다. (1:1)
//
// 인자 : 없음 
// 리턴 : 실패하면 0, 성공하면 0 이외의 값.
//
BOOL DrawBuffer(void)
{
	COORD pos = { 0, 0};
	SMALL_RECT rc = { 0, 0, CON_W-1, CON_H-1};

	return WriteConsoleOutput(g_Display.hCS, 
#ifdef _DOUBLE_BUFFER__
		//g_Primary.pBufArray, g_Primary.bufSize,		//무조건 프라이머리의 내용을 그린다.
		g_pPriBuffer->pBufArray, g_pPriBuffer->bufSize,
#else
		g_Buffer.pBufArray, g_Buffer.bufSize, 
#endif
		pos, &rc);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void GetMousePt() : 마우스 좌표 얻기. 
// 
//  인자 : 없음.
//  리턴 : 없음.
//
void GetMousePt(void)
{
	g_MousePt.x = g_Input.InputRecord.Event.MouseEvent.dwMousePosition.X;
	g_MousePt.y = g_Input.InputRecord.Event.MouseEvent.dwMousePosition.Y;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void CheckInput() : 입력 이벤트 값을 판별한다. 
//                     이벤트 큐의 읽지 않은 값들을 모두 체크한다.
// 인자 : 없음.
// 리턴 : 없음.
//
void CheckInput()
{
	DWORD dwUnread = 0, dwRead = 0;

	GetNumberOfConsoleInputEvents(g_Input.hCI, &dwUnread);
	if(dwUnread == 0) return;

	ZeroMemory(&g_Input.InputRecord, sizeof(INPUT_RECORD));
	//키보드 버퍼를 클리어 한다. --> 활성화 시키면 키가 1개 밖에는 작동하지 않는다.
	//ZeroMemory(g_KeyVal, sizeof(g_KeyVal));
 
	for(DWORD i=0; i<dwUnread; i++)
	{
		ReadConsoleInput(g_Input.hCI, &g_Input.InputRecord, 1, &dwRead);

		switch(g_Input.InputRecord.EventType)
		{
		case KEY_EVENT:
			{
				WORD keycode = g_Input.InputRecord.Event.KeyEvent.wVirtualKeyCode;
				BOOL bkeydown = g_Input.InputRecord.Event.KeyEvent.bKeyDown;

				g_KeyVal[keycode] = bkeydown;	//룰린 키 셋팅....

				if( bkeydown == YES_ )			//처음 눌렸다면, 
					g_KeyUpVal[keycode] = NO_;	//키가 눌린것으로 간주..
				
				//else g_KeyUpVal[keycode] = YES_;	//키가 띄어 진것으로 간주...처음 시작할때는 모든 키가 '떨어져' 있다.

			}//end of temp block.
				 
			break;

		case MOUSE_EVENT:

			ZeroMemory(g_MouseVal, sizeof(g_MouseVal));		//TEMP. MOUSE TEST CODE. 

 			switch(g_Input.InputRecord.Event.MouseEvent.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED: g_MouseVal[MB_LEFT_] = 1;
				break;
			case RIGHTMOST_BUTTON_PRESSED : g_MouseVal[MB_RIGHT_] = 1;
				break;
			case FROM_LEFT_2ND_BUTTON_PRESSED: g_MouseVal[MB_MIDDLE_] = 1;
				break;
			}

			GetMousePt();
			//g_MouseVal[g_Input.InputRecord.Event.MouseEvent.
			break;

		case FOCUS_EVENT:	//더블클릭인지 처리 코드 부분 - 잔여 작업 
			break;
		}
	}//end of for()

	//update. 2003.01.26. : SHIFT/CONSTROL/ALT(MENU) KEY 체크.(왼쪽 오른쪽 독립적으로)
	for(int i=0xa0; i<0xa6; i++)
	{
		g_KeyVal[i] = GetAsyncKeyState(i)?TRUE:FALSE;	

		if(g_KeyVal[i] == TRUE)					//키가 처음 눌렸다면, 
			g_KeyUpVal[i] = FALSE;				//키가 눌린것으로 간주.  
	}


	FlushConsoleInputBuffer(g_Input.hCI);

}//end of void ChekcInput()


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void ClearInputData() :  키보드/마우스 입력 데이터 클리어..
//
void ClearInputData()
{
	
	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));
	memset(g_KeyUpVal, YES_, sizeof(g_KeyUpVal));
	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));  
	g_MousePt.x = 0; 
	g_MousePt.y = 0;  

//	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));			//키보드 값 클리어.
//	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));		//마우스 값 클리어.
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOOL IsKeyUp(int vk_val)  : 키가  눌렸다가...떨어지면 TRUE 를 리턴한다.
//
BOOL IsKeyUp(int vk_val)
{
	//if(g_KeyUpVal[vk_val] == NO_)		//키가 눌린 상태에서...키가 떨어지면..
	if(g_KeyVal[vk_val] == NO_ && g_KeyUpVal[vk_val] == NO_)	
	{
		g_KeyUpVal[vk_val] = YES_;		// 원래 초기화 값으로 키값 셋팅.
		return TRUE;					//'눌렸다 떨어졌음' 을 리턴한다.
	}
	

	return 0;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//#define SND_PLAYONCE_   SND_ASYNC | SND_NODEFAULT
//#define SND_PLAYLOOP_	SND_LOOP | SND_ASYNC | SND_NODEFAULT


void PlaySound(const char* filename, unsigned int playtype)
{
	sndPlaySound( filename, (UINT)playtype );
	//PlaySound(filename, NULL, SND_ASYNC | SND_FILENAME |  SND_NODEFAULT | SND_NOWAIT);
}

void PlaySound2(const char* filename)
{
//	PlaySound(filename, NULL, SND_ASYNC | SND_FILENAME |  SND_NODEFAULT | SND_NOSTOP | SND_NOWAIT );

}
//static void PlaySound(LPCTSTR lpszSound)
//{
	//if(m_bSound)
/*	if(1)
	{
		HRSRC hRes; // resource handle to wave file
		HGLOBAL hData;
		BOOL bOk = FALSE;
		if ((hRes = ::FindResource(AfxGetResourceHandle(), lpszSound,
		  _T("WAVE"))) != NULL &&
		  (hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
		{
			// found the resource, play it
			bOk = sndPlaySound((LPCTSTR)::LockResource(hData),
				SND_MEMORY|SND_ASYNC|SND_NODEFAULT);
			FreeResource(hData);
		}
	}*/
//}

//inline static void PlaySound(UINT nIDS)	{ PlaySound(MAKEINTRESOURCE(nIDS)); }


/////////////////////////////////////////////////////////////////////////////////////////
// 
void EngineSync(DWORD frm)
{ 
	static int oldtime = 0;
	while(GetTickCount() - oldtime < 1000/frm);
	oldtime = GetTickCount();
			  
}



/////////////////////////////////////////////////////////////////////////////////////////
// 
// BOOL MsgBox(const char* msg)  : 메세지 박스 출력하기.
// 
// 인자 : 출력할 문자열.
// 리턴값 : OK 버튼을 누르면 TRUE , CANCEL 버튼을 누르면 FALSE 리턴.
BOOL MsgBox(const char* msg)
{
	int res =  MessageBox(NULL, msg, "Console Wrapper Ex3.0", MB_OKCANCEL | MB_ICONINFORMATION);
	if(res == IDOK) return TRUE;
	
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////////////////
// 
//	void ChangeCodePage(BOOL bIsKoread)
//
//	인자 : TRUE - 한글 모드 FALSE - 영문모드.
//  리턴값 : 없음.
void ChangeCodePage(BOOL bIsKorean)
{
#ifdef _DEBUG
	char msg[80];
#endif
 	if(bIsKorean) 
#ifdef _DEBUG
	{
		sprintf(msg, "** ConWrapper : Change Code Page. 949 : 한글 모드로 전환..\n");
#endif
		system("chcp 949");  //SetConsoleCP(..)
#ifdef _DEBUG
	}
#endif
	else
#ifdef _DEBUG
	{
		sprintf(msg, "** ConWrapper : Change Code Page. 437 : 영문 모드로 전환..\n");
#endif
		system("chcp 437"); //SetConsoleCP(..)
#ifdef _DEBUG
	}

	OutputDebugString(msg);
#endif




}


/////////////////////////////////////////////////////////////////////////////////////////
// 
void SetWindowTitle(const char* titlename)
{
	SetConsoleTitle(titlename);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////// 
// 콘솔 디스플레이                                                 //
/////////////////////////////////////////////////////////////////////
// 2차 수정. 2002. 11.05   기홍. 
// 아래의 랩퍼들을 직접 호출하는 것은 권장하지 않는다.
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void CD_InitMember ( CONDISPLAY* pCD )
{
	ZeroMemory( pCD, sizeof( CONDISPLAY ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void CD_Create( CONDISPLAY* pCD, CODEPAGE codePage )
{

	CD_SetCodePage( codePage );


	// case : output display

	// Get Console Handle (Output)
	pCD->hCS = GetStdHandle( STD_OUTPUT_HANDLE );


//	// case : non-output display (non-active)
//
//	// create common console-screen-buffer 
//	pCD->hCS = CreateConsoleScreenBuffer(
//						GENERIC_READ|GENERIC_WRITE,
//						FILE_SHARE_READ|FILE_SHARE_WRITE,
//						NULL,
//						CONSOLE_TEXTMODE_BUFFER,
//						NULL );


	// error check 
	IS_NOT( pCD->hCS, INVALID_HANDLE_VALUE, 
			"CD_Create() : pCD->hCS 비정상" );



	// Set Screen Buffer
	COORD ScreenSize = {CON_W,CON_H};
	SetConsoleScreenBufferSize( pCD->hCS, ScreenSize );
	GetConsoleScreenBufferInfo( pCD->hCS, &pCD->CSBufInfo );

	// hide cursor
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 100;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo( pCD->hCS, &CurInfo );

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CD_Delete ( CONDISPLAY* pCD )
{
	//
	CD_InitMember( pCD );
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL CD_DrawChar( CONDISPLAY* pCD, int x, int y,  char c,  WORD wColor )
{
	// check - 클립핑.
	if(( x < 0 ) || ( x > CON_W -1 )|| ( y < 0 ) || ( y > CON_H -1 )) 	return FALSE;


	BOOL res = FALSE;

	SetConsoleTextAttribute( pCD->hCS, wColor );

	COORD CursorPos = {x,y};
	res = SetConsoleCursorPosition( pCD->hCS, CursorPos );

	printf( "%c", c );

	return res;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CD_DrawStr( CONDISPLAY* pCD,
				 int x, int y, 
				 char* str,
				 WORD wColor )
{
	// check - 클립핑 : 문자열인데?? -,-;
	if(( x < 0 ) || ( x > CON_W -1 )||( y < 0 ) || ( y > CON_H -1 ) ) return FALSE;


	BOOL Res = FALSE;

	SetConsoleTextAttribute( pCD->hCS, wColor );

	COORD CursorPos = {x,y};
	Res = SetConsoleCursorPosition( pCD->hCS, CursorPos );

	printf( "%s", str );

	return Res;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL CD_FillChar( CONDISPLAY* pCD, 
				  char c, 
				  WORD wColor )
{
	BOOL ResAttr = FALSE, ResChar = FALSE;

	COORD coStart = {0,0};
	DWORD dwWritten;

	ResAttr = FillConsoleOutputAttribute(	pCD->hCS, 
							wColor, CON_W*CON_H,
							coStart, &dwWritten );

	ResChar = FillConsoleOutputCharacter(	pCD->hCS,
							c, 	     CON_W*CON_H,
							coStart, &dwWritten );

	return ( ResAttr && ResChar );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CD_SetTitle( char* szTitle )
{
	SetConsoleTitle( szTitle );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CD_SetCodePage( CODEPAGE codePage )
{
	if( codePage == KOR ) system("chcp 949");
	else
	if( codePage == ENG ) system("chcp 437");
}


//} end // Console Display 





///////////////////////////////////////////////////////////////////// 
// 콘솔 디스플레이 버퍼                                            //
/////////////////////////////////////////////////////////////////////
// 2차 수정. 2002. 11.05   기홍. 
// 아래의 렙퍼들을 직접 호출하는 것은 권장하지 않는다.

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CB_InitMember( CONBUFFER* pCB )
{
	ZeroMemory( pCB, sizeof( CONBUFFER ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CB_Create( CONBUFFER* pCB, int width, int height )
{
	pCB->bufSize.X = width;
	pCB->bufSize.Y = height;

	pCB->pBufArray = (CHAR_INFO *)malloc( width*height*sizeof(CHAR_INFO) );

	IS_NOT( pCB->pBufArray, NULL,
			"CB_Create() : pCB->pBufArray 생성실패" );

	ZeroMemory( pCB->pBufArray, width*height*sizeof(CHAR_INFO) );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CB_Delete( CONBUFFER* pCB )
{
	SAFE_FREE( pCB->pBufArray );
	CB_InitMember( pCB );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL CB_DrawChar( CONBUFFER* pCB, int bufX, int bufY, char c, WORD wColor )
{
	// check
	if(( bufX < 0 ) || ( bufX > pCB->bufSize.X-1 )
	    || ( bufY < 0 ) || ( bufY > pCB->bufSize.Y-1 ) )
		return FALSE;	


	int w = pCB->bufSize.X;
	pCB->pBufArray[ w*bufY +bufX ].Char.AsciiChar = c;
	pCB->pBufArray[ w*bufY +bufX ].Attributes = wColor;
	
	return TRUE;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CB_DrawStr( CONBUFFER* pCB, int bufX, int bufY, char* str, WORD wColor )
{
	int len = strlen(str);

	// check
	if(    ( bufX < 0 ) || ( bufX+len > pCB->bufSize.X )
	    || ( bufY < 0 ) || ( bufY > pCB->bufSize.Y-1 ) )
		return FALSE;	


	int w = pCB->bufSize.X;

	for( int i=0; i<len; i++ )
	{								
		pCB->pBufArray[ w*bufY +bufX +i ].Char.AsciiChar = *(str++);
		pCB->pBufArray[ w*bufY +bufX +i ].Attributes = wColor;
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 화면 클리어.(EX: 검은색)
//
BOOL CB_FillChar( CONBUFFER* pCB,
				   char c, 
				   WORD wColor )
{
	int w = pCB->bufSize.X;
	int h = pCB->bufSize.Y;

	for( int y=0; y<h; y++ )
		for( int x=0; x<w; x++ )
		{
			pCB->pBufArray[ w*y +x ].Char.AsciiChar = c;
			pCB->pBufArray[ w*y +x ].Attributes	 = wColor;
		}

	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CB_Copy ( CONBUFFER* pCBSrc,
			   int selX, int selY, int selW, int selH,
			   CONBUFFER* pCBDest,
			   int destX, int destY )
{
	// check
	if(    (selX < 0) 
		|| (selY < 0) 

		|| (destX< 0) 
		|| (destY< 0) 

		|| (destX+selW > pCBDest->bufSize.X)
        || (destY+selH > pCBDest->bufSize.Y)
	  )
		return FALSE;


//	int destW = pCBDest->bufSize.X;
//	int destH = pCBDest->bufSize.Y;


//	//// method 1
//	int srcW  = pCBSrc->bufSize.X;
//	int destW = pCBDest->bufSize.X;
//
//	for( int y=selY; y<selY+selH; y++ )	
//	{
//		for( int x=selX; x<selX+selW; x++ ) 
//		{
//			pCBDest->pBufArray[ destW*(y+destY) +(x+destX) ]
//				= pCBSrc->pBufArray[ srcW*y +x ];
//		}
//	}


	//// method 2
	int srcW  = pCBSrc->bufSize.X;
	int destW = pCBDest->bufSize.X;

	CHAR_INFO* srcCur  = pCBSrc->pBufArray  +srcW *(selY)  +(selX);
	CHAR_INFO* destCur = pCBDest->pBufArray +destW*(destY) +(destX);

	for( int y=0; y<selH; y++ )	
	{
		memcpy( destCur, srcCur, sizeof(CHAR_INFO)*selW );
		srcCur  += srcW;
		destCur += destW;
	}

	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL CB_ToDisplay ( CONBUFFER* pCB,
					int bufX, int bufY, int bufW, int bufH,
					CONDISPLAY* pCD, 
					int disX, int disY )
{
	// check
	if((bufX < 0) || (bufY < 0) || (disX < 0) || (disY < 0)
		|| (disX+bufW > CON_W)	|| (disY+bufH > CON_H) 
		)
		return FALSE;


	COORD		bufCoord = { bufX, bufY };
	SMALL_RECT	drawRect = { disX, 	disY,  disX +(bufW-1), disY +(bufH-1) };

	return WriteConsoleOutput( pCD->hCS, pCB->pBufArray, pCB->bufSize, bufCoord, &drawRect );
}

//} end
/**/ // Console Char Buffer






///////////////////////////////////////////////////////////////////// 
// 콘솔 입력 - 마우스 / 키보드                                     //
/////////////////////////////////////////////////////////////////////
// 2차 수정. 2002. 11.05   기홍.  
// 아래의 렙퍼들을 직접 호출하는 것은 권장하지 않는다.

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void CI_InitMember( CONINPUT* pCI )
{
	ZeroMemory( pCI, sizeof(CONINPUT) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void CI_Create( CONINPUT* pCI )
{
	CI_InitMember( pCI );  //멤버 초기화.

	// get input handle
	pCI->hCI = GetStdHandle( STD_INPUT_HANDLE );	

	IS_NOT( pCI->hCI, INVALID_HANDLE_VALUE, 
		    "CI_Create() : pCI->hCI 비정상" );

	
	// enable mouse input
	DWORD modeOld, modeNew;
	GetConsoleMode( pCI->hCI, &modeOld );
	//modeNew = modeOld & ~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	modeNew = modeOld;// | (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	//modeNew = modeOld & ~(ENABLE_ECHO_INPUT);
	modeNew = modeNew | ENABLE_MOUSE_INPUT;

	IS_OK( SetConsoleMode( pCI->hCI, modeNew ),
		   TRUE, 
		   "CI_Create() : SetConsoleMode() 실패" ); 

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void CI_Delete( CONINPUT* pCI )
{
	CI_InitMember( pCI );
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CI_Read( CONINPUT* pCI, READMODE read, RECMODE rec )
{

	DWORD dwUnread=0, dwRead=0;
	
//	BOOL res = 
	GetNumberOfConsoleInputEvents( pCI->hCI, &dwUnread );  //읽지 않은 콘솔 입력 이벤트 개수를 읽어 온다.
//	if( res == 0)
//	{
//		OutputDebugString("** GetNumberOfConsoleInputEvents failed...\n");
//	}

	if( dwUnread == 0 ) return;		//읽지 않은 값이 없다면 리턴. 

  	if( rec == REC_ERASE )		//이전 키값 삭제.
		ZeroMemory( &pCI->InputRecord, sizeof(INPUT_RECORD) );
 

	if( read == READ_WAIT )		//입력 이벤트가 있을때까지 대기한다.
	{
/*		for(int i=0; i<dwUnRead; i++)
		{
			ReadConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead );
			//키보드 값이면..
			if(

 
		{
			FlushConsoleInputBuffer( pCI->hCI );
		}*/
	}
	else if( read == READ_NOWAIT )	//입력이 없더라도 대기하지 않고 바로 리턴. 
	{
		for(DWORD i=0; i<dwUnread; i++)
		{
			//PeekConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead);
			ReadConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead);
			//키보드 메세지 냐?
			switch(pCI->InputRecord.EventType)
			{
			case KEY_EVENT:
 				g_KeyVal[pCI->InputRecord.Event.KeyEvent.wVirtualKeyCode] =
					pCI->InputRecord.Event.KeyEvent.bKeyDown;
	 
				break;
			case MOUSE_EVENT:
				break;
			case FOCUS_EVENT:
				break;
			}

		}


		BOOL res = FlushConsoleInputBuffer( pCI->hCI );

	 
	}


}
 


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 어떤 키라도 눌렸는지 검사한다. 
//
BOOL CIK_IsAnyKey( CONINPUT* pCI )
{
	if( pCI->InputRecord.Event.KeyEvent.bKeyDown )	return TRUE;
	else	return FALSE;
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 입력 이벤트의 가상키 값을 검사한다.
//
// --> 매크로를 사용할것. 
//#define IsKey(key) (g_KeyVal[key]?TRUE:FALSE)		//키가 눌린상태면 TRUE 리턴. --> CONWRAP.H 
// 
BOOL CIK_IsVKey( CONINPUT* pCI, DWORD dwVKey ) 
{
//	if( pCI->InputRecord.Event.KeyEvent.wVirtualKeyCode	== dwVKey )	return TRUE;
//	else	return FALSE;
	return (g_KeyVal[dwVKey])?TRUE:FALSE;
}
 

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 입력이벤트의 아스키 코드값을 검사한다.
// BOOL CIK_IsAscii( CONINPUT* pCI, wchar uAscii )
BOOL CIK_IsAscii( CONINPUT* pCI, char cAscii )	
{
	// UNICODE
	//if( pCI->InputRecord.Event.KeyEvent.uChar.UnicodeChar == uAscii )

	// CHAR, 
	if( pCI->InputRecord.Event.KeyEvent.uChar.AsciiChar	== cAscii )	return TRUE;
	else return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
char CIK_GetChar( CONINPUT* pCI )
{
	// UNICODE
	// return pCI->InputRecord.Event.KeyEvent.uChar.UnicodeChar;

	// CHAR, 
	return pCI->InputRecord.Event.KeyEvent.uChar.AsciiChar;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CIM_IsButtonLeft( CONINPUT* pCI )
{
	if( pCI->InputRecord.EventType != MOUSE_EVENT )
		return FALSE;

	if( pCI->InputRecord.Event.MouseEvent.dwButtonState 
		& FROM_LEFT_1ST_BUTTON_PRESSED )
	{
		return TRUE;
	}
	else
		return FALSE;
}

/*BOOL LButtonDown(void)
{
	return (g_MouseVal[MB_LBUTTON])?TRUE:FALSE;
}

BOOL RButtonDown(void)
{
	return (g_MouseVal[MB_RBUTTON])?TRUE:FALSE;
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CIM_IsButtonRight( CONINPUT* pCI )
{
	if( pCI->InputRecord.EventType != MOUSE_EVENT )
		return FALSE;

	if( pCI->InputRecord.Event.MouseEvent.dwButtonState 
		& RIGHTMOST_BUTTON_PRESSED )
	{
		return TRUE;
	}
	else
		return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
BOOL CIM_IsMoved( CONINPUT* pCI )
{
	if( pCI->InputRecord.Event.MouseEvent.dwEventFlags 
		== MOUSE_MOVED )
		return TRUE;
	else
		return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
int CIM_GetPosX( CONINPUT* pCI )
{
	pCI->MousePos.X = pCI->InputRecord.Event.MouseEvent.dwMousePosition.X;

	return pCI->MousePos.X;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
int CIM_GetPosY( CONINPUT* pCI )
{
	pCI->MousePos.Y = pCI->InputRecord.Event.MouseEvent.dwMousePosition.Y;

	return pCI->MousePos.Y;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CIM_SetPosXY( CONINPUT* pCI, int x, int y )
//{
//	pCI->MousePos.X = x;
//	pCI->MousePos.Y = y;
//}


//////////////////////////////////////////////////////////////////////
//int CIM_GetMoveX( CONINPUT* pCI )
//{
//	int moveX = 0;
//	int xOld, xNew;
//	if( pCI->InputRecord.Event.MouseEvent.dwEventFlags 
//		== MOUSE_MOVED )
//	{
//		xOld = pCI->MousePos.X;
//		xNew = pCI->InputRecord.Event.MouseEvent.dwMousePosition.X; 
//		moveX = xNew - xOld;
//		pCI->MousePos.X = xNew;	
//	}
//	return moveX;
//}

	
//////////////////////////////////////////////////////////////////////
//int CIM_GetMoveY( CONINPUT* pCI )
//{
//	int moveY = 0;
//	int yOld, yNew;
//	if( pCI->InputRecord.Event.MouseEvent.dwEventFlags 
//		== MOUSE_MOVED )
//	{
//		yOld = pCI->MousePos.Y;
//		yNew = pCI->InputRecord.Event.MouseEvent.dwMousePosition.Y;
//		moveY = yNew - yOld;
//		pCI->MousePos.Y = yNew;		
//	}
//	return moveY;
//}



//} end
/**/ // Console Input



/*************************************** end of file "conwarp.cpp" ********************************************/