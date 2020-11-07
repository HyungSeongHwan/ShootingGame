/********************************************************************
  SysTimer.h

  Win32 �ý��� Ÿ�̸� / Implementation

********************************************************************/


#include "SysTimer.h"  // ���� �佺 ����. 2002.10.31. ��ȫ.

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

