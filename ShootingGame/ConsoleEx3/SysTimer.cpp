/********************************************************************
  SysTimer.h

  Win32 시스템 타이머 / Implementation

********************************************************************/


#include "SysTimer.h"  // 파일 페스 수정. 2002.10.31. 기홍.

//-------------------------------------------------------------------
void TIMER_Start ( SYSTIMER* pT, DWORD tLimit )
{
	pT->m_nCount	 = 0;
	pT->m_nCurCount  = 0;
	pT->m_tLimit	 = tLimit;
	pT->m_tStart	 = GetTickCount(); 

}
 
//-------------------------------------------------------------------
void TIMER_Restart ( SYSTIMER* pT )
{ 
	pT->m_nCurCount  = 0;
	pT->m_tStart	 = GetTickCount(); 

}
 
//-------------------------------------------------------------------
int TIMER_IsLimit ( SYSTIMER* pT )
{
	if( GetTickCount() - pT->m_tStart > pT->m_tLimit )
	{
		TIMER_Restart( pT );
		return TRUE;
	}
	else 
	{
		pT->m_nCount = ++pT->m_nCurCount;
		return FALSE;
	}

}

