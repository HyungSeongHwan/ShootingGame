/********************************************************************
  ConWrap.cpp

  Win32 �ܼ� ����� ����� ���� �������̽� / Implementation

  Compiler : Visual C/C++ 6.0 & Win32 Console API.
  Platfrom : WINDOWS 9X/2000 /w SP3. 
             It's not tested under WINDOWS ME/XP.

  �� �� ���� : klayman808@hotmail.com
  1/2�� ���� : mad_dog3182@hotmail.com 
  3�� ���� : djdurk@homibox.com
********************************************************************/



#include "ConWrap.h"  //���� �н� ����. 2002.10.31. ��ȫ.



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ���� 
//
// ���� ��������  Wrapper �̿ܿ����� ���� ������ �ʿ䰡 ����.
//
DWORD		g_MouseVal[MB_MAX_] = { 0, };	//���콺 ��.
MOUSEPT		g_MousePt = { 0, 0 };			//���콺 ��ǥ��. 
BYTE		g_KeyVal[256] = { 0, };			//Ű ��.  
BYTE		g_KeyUpVal[256] = { YES_, };		//KEY UP �Ǹ� TRUE ����..

CONINPUT	g_Input;						//�ܼ��Է�
CONDISPLAY	g_Display;						//�ܼ� ȭ��

 
#ifdef _DOUBLE_BUFFER__
CONBUFFER	g_Buffers[2]; 					//���� ���۸��� ���� ������.
LPCONBUFFER	g_pPriBuffer = NULL;			//����� ������...
LPCONBUFFER g_pBkBuffer = NULL;				//������ �Ӹ� ������.
#else
CONBUFFER	g_Buffer;						//�ܼ� ��� ���ڹ���.(80 * 25)���� �迭�̴�.
#endif
//SYSTIMER	g_Timer;						//2002.11.11.�ϴ� ������� ����.



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//								   //	
// �߰� �Լ�. 2002. 11.05. ��ȫ.   //
//                                 //
/////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
// 
//  FPS ����Լ�. : 2003.7.3. ���ȫ 
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
	DrawStrEx3(0, 0, msg, RED, WHITE);			//�ֽ� �������� ��!
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void InitialConsole() : �ܼ� �ʱ�ȭ �Լ�. - ���α׷� ���ۺκп��� ���� ���� ȣ���ؾ� �Ѵ�.
//
// ���ϰ� : ����  
// ��  �� : ����
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
	 
	//������� ������ �Ҵ�.
	g_pBkBuffer = &g_Buffers[1];		//0: Primary, 1: secondary/backbuffer.
	g_pPriBuffer = &g_Buffers[0];

#else
	CB_InitMember(&g_Buffer);
	CB_Create(&g_Buffer, CON_W, CON_H);
#endif

	//Ű���� �� ����.
	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));
	memset(g_KeyUpVal, YES_, sizeof(g_KeyUpVal));
	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));  
	g_MousePt.x = 0; 
	g_MousePt.y = 0;  


}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void ReleaseConsole() : �ܼ� ���� �Լ�. - ���α׷� ����� �� ȣ���ؾ� ��.
//
// ���ϰ� : ����  
// ��  �� : ����
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
//  int GetNumber() : �ܼ��Է� ��Ʈ������ ��ȣ�ִ� ������ ���� �Է� �޴´�.
//
//  ���� : int�� ������ pNum, ECHO �����ǥ x,y
//  ���ϰ� : �����ϸ� pNum �� ��, �����ϸ� 0x80000000 
//
int GetNumber(int* pNum, int x, int y) 
{
	COORD pos = { x, y};
	SetConsoleCursorPosition(g_Display.hCS, pos);

	if(scanf("%d", pNum) == 0)		//���н�...
	{
		//_flushall();				//stream  buffer  Ŭ����.
		*pNum = FAIL_GETNUMBER_ ;	//0x80000000; ������ �ʱ�ȭ...(���� �ִ밪 : -2147483648)
	}
	
	_flushall();				//stream  buffer  Ŭ����.
	return *pNum;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// int GetString() : �ܼ��Է� ��Ʈ������ ���ڿ��� �Է� �޴´�.
//
// ���� : ���ڿ� ������, ECHO �����ǥ x,y
// ���ϰ� : ������ �о� ���� ���ڿ��� ����.(byte ����)
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
//  BOOL DrawChar(..)	: ���� ��� �Լ�.
//
//  ���ڰ� : ��� ��ǥ (x, y), ����� ���� , ���� ��, ���� ����.
//  ���ϰ� : ���� TRUE , ���� FALSE
//
BOOL DrawChar(int x, int y, char c, WORD fcolor, WORD bcolor)
{
		// check - Ŭ����.
	//if(( x < 0 ) || ( x > CON_W -1 )|| ( y < 0 ) || ( y > CON_H -1 )) 	return FALSE;
	if( x<0 || x>= CON_W || y<0 || y>= CON_H )
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : ���! *  DrawChar() ��ǥ ���� : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return FALSE;			//Ŭ���� �ڵ�� �����ʿ�.
	}

	SetConsoleTextAttribute(g_Display.hCS, CONRGB(fcolor, bcolor));

	COORD pos = {x, y};			//Ŀ�� ��ġ - �� ����� ������ ��ġ....
	BOOL res = SetConsoleCursorPosition(g_Display.hCS, pos);
	
	printf("%c", c);

	return res;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  void DrawChar(...)	: ���� ��� �Լ�.- ��ũ�� ���۸��� ����ؾ� ��.
//
//  ���ڰ� : ��� ��ǥ (x, y), ����� ���� , ���� ��, ���� ����.
//  ���ϰ� : ����.
//
void DrawCharEx3(int x, int y, char c, WORD fcolor, WORD bcolor)
{
//Ŭ���� �ڵ� �ʿ�.
	if(x<0 || x >= CON_W || y<0 || y >= CON_H)
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : ���! *  DrawCharEx3() ��ǥ ���� : x:%d\ty=%d\n", x, y );
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
// WORD GetAttr(...) : �Ӽ��о� ����.  �����ص� '������'�� �����ϰ� �ȴ�. 
//
// ���ڰ� : �о�� x, y��ǥ, ȭ�鿡�� �о�ð�� TRUE / ���ۿ��� �о�ð�� FALSE
// ���ϰ� : x,y��ǥ���� �Ӽ���.
//
WORD GetAttrEx3(int x, int y, BOOL bFromScreen)
{
	if( x< 0 || x >= CON_W || y < 0 || y >= CON_H) return 0x00;

	WORD attr = 0x00;
 
	if(bFromScreen)
	{
		DWORD readnum=0;
		COORD pos = { x, y};
		ReadConsoleOutputAttribute( //�ܼ� ��ũ���� �Ӽ��� �о�´�.
			g_Display.hCS, &attr, 1, pos, &readnum);
	}
	else
	{
#ifdef _DOUBLE_BUFFER__						//���� ���۸��� '�����'���� �о�´�.
	
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
// WORD GetCharEx3() : ���ڰ� �о� ����.  �����ص� 'NUL' �� �����ϰ� �ȴ�. 
//
// ���ڰ� : �о�� x, y��ǥ, ȭ�鿡�� �о�ð�� TRUE / ���ۿ��� �о�ð�� FALSE
// ���ϰ� : x,y��ǥ���� �Ӽ���.
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
		ReadConsoleOutputCharacter(					//�ܼ� ��ũ���� �Ӽ��� �о�´�.
			g_Display.hCS, (LPSTR)&Char, 1, pos, &readnum);
	}
	else
	{
#ifdef _DOUBLE_BUFFER__								//���� ���۸��� '�����'���� �о�´�.
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	Char =  g_pBkBuffer->pBufArray[pos].Char.AsciiChar; 
#else
	int pos = g_Buffer.bufSize.X * y + x;			//�̱� ���۸��� '�ܼ� ����' ���� �о� �´�.
	Char = g_Buffer.pBufArray[pos].Char.AsciiChar; 
#endif
	}

	return Char;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	BOOL IsAnyKey(void) : Ű������ �ִٸ� TRUE�� �����Ѵ�
//
//  2002.11.13. �߰�.
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
//  BOOL DrawStr(...) : ���ڿ� ����Լ�.
//
//  ���ڰ� : ��� ��ǥ (x, y), ����� ���ڿ� ������ , ���� ��, ���� ����.
//  ���ϰ� : ���� TRUE , ���� FALSE
//
BOOL DrawStr(int x, int y, char* str, WORD fcolor, WORD bcolor)
{
 	// ���ڿ� Ŭ����. -------------------------------------------
	//if( x < 0 || x>= CON_W || y<0 || y>= CON_H)				// ���ڿ� ���� ��ǥ ũ����..1ST. 
	if( x >= CON_W || y<0 || y >= CON_H)						 
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : ���! *  DrawStr() ��ǥ ���� : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return FALSE;
	}
	
	int old_len = strlen(str), new_len = old_len;
	char msg[80] = "";
 
	if( x>= 0 && x < CON_W)									//x������ con_w �̻� �߸����...
	{
 		if( x + old_len > CON_W )							// ���ڿ��� ȭ�� ������ �߸����...2ND. ��ü ���ڿ����� �߸� ���̸� ����, ����� ���ڿ� ���̸� ����Ѵ�. 	
			new_len = CON_W - x; //old_len - (x + old_len - CON_W);

		strncpy(msg, str, new_len);
	}
	else if( x < 0)										// x �� 0 ���Ϸ� �߸����...
	{
		if( old_len <=  abs(x)) return FALSE;			//Ŭ���� �������� ���ڿ��� �۴ٸ� ������� �ʴ´�.
		 
		strcpy(msg, str + abs(x)); //new_len);
		x = 0;											//�����ǥ ����.
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
//  BOOL DrawStrEx3(...) : ���ڿ� ����Լ�.
//
//  ���ڰ� : ��� ��ǥ (x, y), ����� ���ڿ� ������ , ���� ��, ���� ����.
//  ���ϰ� : ����.
//
void DrawStrEx3(int x, int y, char* str, WORD fcolor, WORD bcolor)
{
	if( x >= CON_W || y<0 || y>= CON_H)
	{
#ifdef  _DEBUG
 		char msg[80]; sprintf(msg, "* ConWrap Ex3.0 : ���! *  DrawStrEx3() ��ǥ ���� : x:%d\ty=%d\n", x, y );
		OutputDebugString(msg);
		
#endif //_DEBUG
		return;					//Ŭ���� ���� ��ǥ. 1st.
	}

	int old_len = strlen(str);
	int new_len = old_len;
	char temp[80] = ""; 
	
	
	if( x >= 0 && x < CON_W)		//x���� CON_W ���� Ŭ ���...
	{
		if((x + old_len) > CON_W)
			new_len =  CON_W - x ; //old_len - (x + old_len - CON_W);
		strncpy(temp, str, new_len);
	}
	else if( x < 0)	//x�� 0 ���� ���� ���..Ŭ����...
	{
		 
		if( old_len <= abs(x) )		//����� ���ڿ����� ���� ��� ��ǥ�� �� ���̳ʽ� ���̶��... 
			return;
		strcpy(temp, str + abs(x));   //temp += (x);				//���ڿ� �ּ� ����..
 		x = 0;						//��� ��ǥ ����.
	}
	
#ifdef _DOUBLE_BUFFER__
	
	int pos = g_pBkBuffer->bufSize.X * y + x;
	int len = strlen(temp);

	for( int i=0; i<len; i++)
	{
//		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//���ڿ� Ŭ����  X�� con_w ���� Ŭ��� 2nd.
		
		g_pBkBuffer->pBufArray[pos + i].Char.AsciiChar = temp[i]; //str[i];
		g_pBkBuffer->pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}

#else
	int pos = g_Buffer.bufSize.X * y + x;
	int len = strlen(str);

	for( int i=0; i<len; i++)
	{
 //		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//���ڿ� Ŭ���� X �� 2nd.

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
		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//���ڿ� Ŭ����  X�� 2nd.

		g_pBkBuffer->pBufArray[pos + i].Char.AsciiChar = str[i];
		g_pBkBuffer->pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}

#else
	int pos = g_Buffer.bufSize.X * y + x;
	int len = strlen(str);

	for( int i=0; i<len; i++)
	{
 		if( (pos + i)%g_pBkBuffer->bufSize.X == 0 )	return;				//���ڿ� Ŭ���� X �� 2nd.

		g_Buffer.pBufArray[pos + i].Char.AsciiChar = str[i];
		g_Buffer.pBufArray[pos + i].Attributes = CONRGB(fcolor, bcolor);
	}
#endif
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLine(...) : ���� �׸���. 
// 
//���� : ���� ��ġ (sx, sy),  �� ��ġ ex , �� ���� color
//���� : ����.
//
// ������� ����. ex �̻��� �Լ��� ����Ұ�. ���������� ȣȯ���� ���� ���ܵ�.
//
void DrawHLine(int sx, int sy, int ex, WORD color)
{
	// Not Available. Use a enhanced functions : DrawHLineEx, DrawHLineEx2 or DrawHLineEx3
	OutputDebugString("** DrawHLine() : Not Available. Use a enhanced functions : DrawBoxEx, DrawBoxEx2\n");
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawHLinEx(...) : ���� �׸���. 
// 
// ���� : ���� ��ġ(sx,sy) , ������ ���� width, �� ���� color
// ���� : ����.
//
// �ܼ� ��ũ������ �ٷ� ��� : ���ڰ� ���� ������ ���.
//
// 2002. 11.13. Ŭ���� ok! ������ ��������� ����. 
void DrawHLineEx(int sx, int sy, int width, WORD color)
{
	// Ŭ���� �ڵ�.
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
// void DrawHLinEx2(...) : ���� �׸���. 
// 
// ���� : ���� ��ġ(sx,sy) , ������ ���� width,  ��� ���ڰ� , ���� ���� fcolor, ���� ��� bcolor
// ���� : ����.
//
//
// �ܼ� ��ũ������ �ٷ� ��� : ���ڰ� ��°���.
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
// void DrawHLinEx3(...) : ���� �׸���. 
// 
// ���� : ���� ��ġ(sx,sy) , ������ ���� width, �� ���� color
// ���� : ����.
//
//
// ���ۿ� ���� ��� : ���۸��� ����ؾ���.
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
// void DrawHLinCharEx3(...) : ���ڰ� �ִ� ���� �׸���. 
// 
// ���� : ���� ��ġ(sx,sy) , ������ ���� width, ���ڰ� Char, ���ڻ��� fcolor,  �� ���� bkcolor
// ���� : ����.
//
//
// ���ۿ� ���� ��� : ���۸��� ����ؾ���.
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
// void DrawVLin(...) : ������ �׸���. 
// 
// ���� : ���� ��ġ(sx,sy) , �������� ���� ey , �� ���� color
// ���� : ����.
//
void DrawVLine(int sx, int sy, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawVLineEx, DrawVLineEx2 or DrawVLineEx3
	 
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DrawVLinEx(...) : ������ �׸���, �ܼ� ��ũ���� �ٷ� ���.
// 
// ���� : ���� ��ġ(sx,sy) , �������� ��. height, �� ����  bkcolor
// ���� : ����.
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
// void DrawVLinEx2(...) : ������ �׸���.- �ܼ� ��ũ���� �ٷ� ��� ���ڰ� ����.
// 
// ���� : ���� ��ġ(sx,sy) , �������� ��. height, ���ڰ� c, ���� ���� fcolor, �� ���� bkcolor
// ���� : ����.
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
// void DrawVLinEx3(...) : ������ �׸���.- �ܼ� ���ۿ� ���.
// 
// ���� : ���� ��ġ(sx,sy) , �������� ��. height, �� ���� color
// ���� : ����.
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
// void DrawVLinCharEx3(...) : ���ڰ� �ִ� ������ �׸���.- �ܼ� ���ۿ� ���.
// 
// ���� : ���� ��ġ(sx,sy) , �������� ��. height, ���ڰ� Char, ���� ���� fcolor, �� ���� color
// ���� : ����.
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
//  void DrawBox(...) : �ڽ� �׸��� - ��ũ���� �ٷ����.
// 
//  ���� : �ڽ� ������� ��ǥ ( sx, sy), �ڽ� �����ϴ� ��ǥ(ex, ey), �� ���� color
//  ���� : ����.
//
void DrawBox(int sx, int sy, int ex, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawBoxEx, DrawBoxEx2 or DrawBoxEx3
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawBoxEx(...) : �ڽ� �׸��� - ��ũ���� �ٷ����.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, �� ���� color
//  ���� : ����.
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
//  void DrawBoxEx2(...) : �ڽ� �׸��� - ��ũ���� �ٷ����. ���ڰ� ����.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), 
//         �ڽ� �ʺ� width, �ڽ� ���� height, ���� �� c, ���� �� fcoor, �� ���� bkcolor
//  ���� : ����.
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
//  void DrawBoxEx3(...) : �ڽ� �׸��� - �ܼ� ���ۿ� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, �� ���� color
//  ���� : ����.
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
//  void DrawBoxCharEx3(...) : ���ڰ� �ִ� �ڽ� �׸��� - �ܼ� ���ۿ� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, ���ڰ� Char, ���� ���� fcolor, �� ���� bkcolor
//  ���� : ����.
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
//  void DrawFillBox(...) : ä���� �ڽ� �׸��� - ��ũ���� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� ���� �ϴ� ��ǥ(ex, ey), �� ���� color
//  ���� : ����.
//
void DrawFillBox(int sx, int sy, int ex, int ey, WORD color)
{
	// Not Available. Use a enhanced functions : DrawFillBoxEx , DrawFillBoxEx2 or DrawFillBoxEx3 
	OutputDebugString("** DrawFillBox : Not Available. Use a enhanced functions : DrawFillBoxEx , DrawFillBoxEx2\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx(...) : ä���� �ڽ� �׸��� - ��ũ���� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, �� ���� color
//  ���� : ����.
//
void DrawFillBoxEx(int sx, int sy, int width, int height, WORD color)
{
	for(int i=0; i<height; i++)
		DrawHLineEx(sx, sy+i, width, color);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx2(...) : ä���� �ڽ� �׸��� - ��ũ���� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), 
//		   �ڽ� �ʺ� width, �ڽ� ���� height, ���� �� c, ���� ���� fcolor, �� ���� bcolor
//  ���� : ����.
//
void DrawFillBoxEx2(int sx, int sy, int width, int height, char c, WORD fcolor, WORD bcolor)
{
	for(int i=0; i<height; i++)
		DrawHLineEx2(sx, sy+i, width, c, fcolor, bcolor);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxEx3(...) : ä���� �ڽ� �׸��� - �ܼ� ���ۿ� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, �� ���� color
//  ���� : ����.
//
void DrawFillBoxEx3(int sx, int sy, int width, int height, WORD bcolor)
{
	for(int i=0; i<height; i++)
		DrawHLineEx3(sx, sy+i, width, bcolor);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void DrawFillBoxCharEx3(...) : ���ڰ� �ִ� ä���� �ڽ� �׸��� - �ܼ� ���ۿ� ���.
// 
//  ���� : �ڽ� ������� ��ǥ (sx, sy), �ڽ� �ʺ� width, �ڽ� ���� height, 
//			���� �� Char, ���� ���� fcolor, �� ���� bkcolor
//  ���� : ����.
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
  
	/* �׻� x2 >= x1, y2 > y1 �� �ǵ��� �Ѵ�. */
	 if( x1 > x2 )
	 {
  		 x1 ^= x2;	 x2 ^= x1;	 x1 ^= x2;
	 }

	 if( y1 > y2 )
	 {
  		y1 ^= y2;		 y2 ^= y1;		 y1 ^= y2;
 	 }
      
	/* x, y�� ��ȭ���� ���Ѵ�. */
	delta_x = x2 - x1;
	delta_y = y2 - y1;
//	delta_x = abs(x2 - x1);
//	delta_y = abs(y2 - y1);

  
	/* ó�� �������� ��´�. */
	//put_pixel( x1, y1, color );
	DrawChar(x1, y1, c, fcolor, bcolor);

	/* �� ��ǥ�� ��￡ ���� ���� �ߴ´�. */
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
//  void ClearScreen(...) : ���ϴ� �������� ȭ�� Ŭ���� �ϱ�. 
// 
//  ���� : ȭ���� 'Ŭ����' �� ���� bkcolor 
//  ���� : ����.
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
//  void ClearScreenEx3(...) : ���ϴ� ��������  ��ũ�� ���� Ŭ���� �ϱ�. 
// 
//  ���� : ȭ���� 'Ŭ����' �� ���� bkcolor 
//  ���� : ����.
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
// void Flip() :  ����/�̱� ���۸� �ÿ��� ���.
//
// ���� : ����.
// ���� : ����.
//

void Flip()
{
#ifdef _DOUBLE_BUFFER__
	static int flipcnt = 0;
	g_pBkBuffer = &g_Buffers[flipcnt];						//����� ������ ����.
	g_pPriBuffer = &g_Buffers[flipcnt^=1];

#ifdef _DEBUG
	char msg[80]; sprintf(msg, "p:0x%08x, b:0x%08x", g_pPriBuffer, g_pBkBuffer);
	//DrawStr(0, 24, msg, WHITE, BLACK); 
	//Sleep(500);
	strcat(msg, "\n");	
	OutputDebugString(msg);
#endif //_DEBUG

#endif // _DOUBLE_BUFFER__		
 
	DrawBuffer();											//�����̸Ӹ�->ȭ�� ����.		
}//end of void Flip()




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	void Blt(void) : ������ ������ �����̸Ӹ� ���ۿ� �����Ѵ�. 
//
void Blt(void)
{
	//n/a
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOOL DrawBufer(void) : ������ ������ ȭ�鿡 �׸���. (1:1)
//
// ���� : ���� 
// ���� : �����ϸ� 0, �����ϸ� 0 �̿��� ��.
//
BOOL DrawBuffer(void)
{
	COORD pos = { 0, 0};
	SMALL_RECT rc = { 0, 0, CON_W-1, CON_H-1};

	return WriteConsoleOutput(g_Display.hCS, 
#ifdef _DOUBLE_BUFFER__
		//g_Primary.pBufArray, g_Primary.bufSize,		//������ �����̸Ӹ��� ������ �׸���.
		g_pPriBuffer->pBufArray, g_pPriBuffer->bufSize,
#else
		g_Buffer.pBufArray, g_Buffer.bufSize, 
#endif
		pos, &rc);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  void GetMousePt() : ���콺 ��ǥ ���. 
// 
//  ���� : ����.
//  ���� : ����.
//
void GetMousePt(void)
{
	g_MousePt.x = g_Input.InputRecord.Event.MouseEvent.dwMousePosition.X;
	g_MousePt.y = g_Input.InputRecord.Event.MouseEvent.dwMousePosition.Y;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void CheckInput() : �Է� �̺�Ʈ ���� �Ǻ��Ѵ�. 
//                     �̺�Ʈ ť�� ���� ���� ������ ��� üũ�Ѵ�.
// ���� : ����.
// ���� : ����.
//
void CheckInput()
{
	DWORD dwUnread = 0, dwRead = 0;

	GetNumberOfConsoleInputEvents(g_Input.hCI, &dwUnread);
	if(dwUnread == 0) return;

	ZeroMemory(&g_Input.InputRecord, sizeof(INPUT_RECORD));
	//Ű���� ���۸� Ŭ���� �Ѵ�. --> Ȱ��ȭ ��Ű�� Ű�� 1�� �ۿ��� �۵����� �ʴ´�.
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

				g_KeyVal[keycode] = bkeydown;	//�기 Ű ����....

				if( bkeydown == YES_ )			//ó�� ���ȴٸ�, 
					g_KeyUpVal[keycode] = NO_;	//Ű�� ���������� ����..
				
				//else g_KeyUpVal[keycode] = YES_;	//Ű�� ��� �������� ����...ó�� �����Ҷ��� ��� Ű�� '������' �ִ�.

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

		case FOCUS_EVENT:	//����Ŭ������ ó�� �ڵ� �κ� - �ܿ� �۾� 
			break;
		}
	}//end of for()

	//update. 2003.01.26. : SHIFT/CONSTROL/ALT(MENU) KEY üũ.(���� ������ ����������)
	for(int i=0xa0; i<0xa6; i++)
	{
		g_KeyVal[i] = GetAsyncKeyState(i)?TRUE:FALSE;	

		if(g_KeyVal[i] == TRUE)					//Ű�� ó�� ���ȴٸ�, 
			g_KeyUpVal[i] = FALSE;				//Ű�� ���������� ����.  
	}


	FlushConsoleInputBuffer(g_Input.hCI);

}//end of void ChekcInput()


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void ClearInputData() :  Ű����/���콺 �Է� ������ Ŭ����..
//
void ClearInputData()
{
	
	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));
	memset(g_KeyUpVal, YES_, sizeof(g_KeyUpVal));
	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));  
	g_MousePt.x = 0; 
	g_MousePt.y = 0;  

//	ZeroMemory(g_KeyVal, sizeof(g_KeyVal));			//Ű���� �� Ŭ����.
//	ZeroMemory(g_MouseVal, sizeof(g_MouseVal));		//���콺 �� Ŭ����.
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOOL IsKeyUp(int vk_val)  : Ű��  ���ȴٰ�...�������� TRUE �� �����Ѵ�.
//
BOOL IsKeyUp(int vk_val)
{
	//if(g_KeyUpVal[vk_val] == NO_)		//Ű�� ���� ���¿���...Ű�� ��������..
	if(g_KeyVal[vk_val] == NO_ && g_KeyUpVal[vk_val] == NO_)	
	{
		g_KeyUpVal[vk_val] = YES_;		// ���� �ʱ�ȭ ������ Ű�� ����.
		return TRUE;					//'���ȴ� ��������' �� �����Ѵ�.
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
// BOOL MsgBox(const char* msg)  : �޼��� �ڽ� ����ϱ�.
// 
// ���� : ����� ���ڿ�.
// ���ϰ� : OK ��ư�� ������ TRUE , CANCEL ��ư�� ������ FALSE ����.
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
//	���� : TRUE - �ѱ� ��� FALSE - �������.
//  ���ϰ� : ����.
void ChangeCodePage(BOOL bIsKorean)
{
#ifdef _DEBUG
	char msg[80];
#endif
 	if(bIsKorean) 
#ifdef _DEBUG
	{
		sprintf(msg, "** ConWrapper : Change Code Page. 949 : �ѱ� ���� ��ȯ..\n");
#endif
		system("chcp 949");  //SetConsoleCP(..)
#ifdef _DEBUG
	}
#endif
	else
#ifdef _DEBUG
	{
		sprintf(msg, "** ConWrapper : Change Code Page. 437 : ���� ���� ��ȯ..\n");
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
// �ܼ� ���÷���                                                 //
/////////////////////////////////////////////////////////////////////
// 2�� ����. 2002. 11.05   ��ȫ. 
// �Ʒ��� ���۵��� ���� ȣ���ϴ� ���� �������� �ʴ´�.
 
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
			"CD_Create() : pCD->hCS ������" );



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
	// check - Ŭ����.
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
	// check - Ŭ���� : ���ڿ��ε�?? -,-;
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
// �ܼ� ���÷��� ����                                            //
/////////////////////////////////////////////////////////////////////
// 2�� ����. 2002. 11.05   ��ȫ. 
// �Ʒ��� ���۵��� ���� ȣ���ϴ� ���� �������� �ʴ´�.

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
			"CB_Create() : pCB->pBufArray ��������" );

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
// ȭ�� Ŭ����.(EX: ������)
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
// �ܼ� �Է� - ���콺 / Ű����                                     //
/////////////////////////////////////////////////////////////////////
// 2�� ����. 2002. 11.05   ��ȫ.  
// �Ʒ��� ���۵��� ���� ȣ���ϴ� ���� �������� �ʴ´�.

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
	CI_InitMember( pCI );  //��� �ʱ�ȭ.

	// get input handle
	pCI->hCI = GetStdHandle( STD_INPUT_HANDLE );	

	IS_NOT( pCI->hCI, INVALID_HANDLE_VALUE, 
		    "CI_Create() : pCI->hCI ������" );

	
	// enable mouse input
	DWORD modeOld, modeNew;
	GetConsoleMode( pCI->hCI, &modeOld );
	//modeNew = modeOld & ~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	modeNew = modeOld;// | (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	//modeNew = modeOld & ~(ENABLE_ECHO_INPUT);
	modeNew = modeNew | ENABLE_MOUSE_INPUT;

	IS_OK( SetConsoleMode( pCI->hCI, modeNew ),
		   TRUE, 
		   "CI_Create() : SetConsoleMode() ����" ); 

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
	GetNumberOfConsoleInputEvents( pCI->hCI, &dwUnread );  //���� ���� �ܼ� �Է� �̺�Ʈ ������ �о� �´�.
//	if( res == 0)
//	{
//		OutputDebugString("** GetNumberOfConsoleInputEvents failed...\n");
//	}

	if( dwUnread == 0 ) return;		//���� ���� ���� ���ٸ� ����. 

  	if( rec == REC_ERASE )		//���� Ű�� ����.
		ZeroMemory( &pCI->InputRecord, sizeof(INPUT_RECORD) );
 

	if( read == READ_WAIT )		//�Է� �̺�Ʈ�� ���������� ����Ѵ�.
	{
/*		for(int i=0; i<dwUnRead; i++)
		{
			ReadConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead );
			//Ű���� ���̸�..
			if(

 
		{
			FlushConsoleInputBuffer( pCI->hCI );
		}*/
	}
	else if( read == READ_NOWAIT )	//�Է��� ������ ������� �ʰ� �ٷ� ����. 
	{
		for(DWORD i=0; i<dwUnread; i++)
		{
			//PeekConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead);
			ReadConsoleInput( pCI->hCI, &pCI->InputRecord, 1, &dwRead);
			//Ű���� �޼��� ��?
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
// � Ű�� ���ȴ��� �˻��Ѵ�. 
//
BOOL CIK_IsAnyKey( CONINPUT* pCI )
{
	if( pCI->InputRecord.Event.KeyEvent.bKeyDown )	return TRUE;
	else	return FALSE;
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �Է� �̺�Ʈ�� ����Ű ���� �˻��Ѵ�.
//
// --> ��ũ�θ� ����Ұ�. 
//#define IsKey(key) (g_KeyVal[key]?TRUE:FALSE)		//Ű�� �������¸� TRUE ����. --> CONWRAP.H 
// 
BOOL CIK_IsVKey( CONINPUT* pCI, DWORD dwVKey ) 
{
//	if( pCI->InputRecord.Event.KeyEvent.wVirtualKeyCode	== dwVKey )	return TRUE;
//	else	return FALSE;
	return (g_KeyVal[dwVKey])?TRUE:FALSE;
}
 

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �Է��̺�Ʈ�� �ƽ�Ű �ڵ尪�� �˻��Ѵ�.
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