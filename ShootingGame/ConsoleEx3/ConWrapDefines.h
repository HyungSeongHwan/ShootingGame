/********************************************************************
  ConWrapDefines.h

  Win32 콘솔 입출력 사용자 설정 인터페이스 / Header

  - 기타 필요한 것들 

********************************************************************/


#ifndef __CON_WRAPPER_DEFINES__
#define __CON_WRAPPER_DEFINES__



/////////////////////////////////////////////////
//

//#define CON_W		80
//#define CON_H		25
//
//#define SCROLL_POS	24

#define CON_W		120
#define CON_H		30

#define SCROLL_POS	29

#define SAFE_FREE(p) { if(p) { free(p); (p)=NULL; } }

#define YES_		1		//2002. 11.05.  
#define NO_			0

#define DOWN_		1		//2002.11.5
#define UP_			0



/////////////////////////////////////////////////
//

#define IS_OK(Res, OK, str) \
			if( Res != OK ) {		\
				MessageBox( NULL, str, "ConsoleWrapper", MB_ICONSTOP ); \
				exit(1);\
			}

#define IS_NOT(Res, NOT, str) \
			if( Res == NOT ) {		\
				MessageBox( NULL, str, "ConsoleWrapper", MB_ICONSTOP ); \
				exit(1);\
			}



/////////////////////////////////////////////////
//

typedef enum {
	KOR, ENG
} CODEPAGE;


typedef enum {
	READ_WAIT, READ_NOWAIT
} READMODE;


typedef enum {
	REC_ERASE, REC_NOERASE
} RECMODE;




#endif //__CON_WRAPPER_DEFINES__