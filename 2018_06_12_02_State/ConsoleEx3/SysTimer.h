/********************************************************************
  SysTimer.h

  Win32 시스템 타이머 / Header

 ********************************************************************
  [] Update	
    * 2002.03.15 - 최초 작업
													   by klayman@gs
********************************************************************/


#ifndef __SYS_TIMER__
#define __SYS_TIMER__


#include <windows.h>


/////////////////////////////////////////////////////////////////////
// 
#define SECOND 1000



/////////////////////////////////////////////////////////////////////
// 
typedef struct 
{
	int			m_nCount;
	int			m_nCurCount;
	DWORD		m_tStart;
	DWORD		m_tLimit;

} SYSTIMER;



/////////////////////////////////////////////////////////////////////
// 
#define TIMER_GetLimit(pT)			( (pT)->m_tLimit )
#define TIMER_SetLimit(pT,tLimit)	( (pT)->m_tLimit = tLimit )

#define TIMER_GetCurCount(pT)		( (pT)->m_nCurCount )
#define TIMER_SetCurCount(pT,num)	( (pT)->m_nCurCount = num )

#define TIMER_GetCount(pT)			( (pT)->m_nCount )
#define TIMER_SetCount(pT,num)		( (pT)->m_nCount = num )



/////////////////////////////////////////////////////////////////////
// 
void  TIMER_Start		( SYSTIMER* pT, DWORD tLimit );
void  TIMER_Restart		( SYSTIMER* pT );
int	  TIMER_IsLimit	( SYSTIMER* pT );




#define TEST_TIMER_BEGIN(t)	{

#define TIMER_BEGIN(t)	if( TIMER_IsLimit(&t) ) {
#define TIMER_END(t)	}




#endif//__TIME_COUNTER__