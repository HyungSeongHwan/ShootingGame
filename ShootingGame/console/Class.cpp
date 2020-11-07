#include "Include.h"
CTimeClass::CTimeClass()
{
	m_dwStandMonster = GetTickCount();
	m_dwLimitMonster = 150;
	m_dwCountLimit = 1000;
	m_dwCountStand = GetTickCount();
	m_dwSubLimit = 150;
	m_dwSubStand = GetTickCount();
	m_dwBulletLimit = 48;
	m_dwBulletStand = GetTickCount();
	m_dwBullet_Reload_Stand = GetTickCount();
	m_dwBullet_Reload_Limit = 1000;
	m_dwBarrier_Limit = 1000;
	m_dwBarrier_Stand = GetTickCount();
	m_dwBossBullet_Limit = 300;
	m_dwBossBullet_Stand = GetTickCount();
	m_dwBossColor_Stand = GetTickCount();
	m_dwBossColor_Limit = 1500;
	m_dwTerret_Limit = 1000;
	m_dwTerret_Stand = GetTickCount();
	m_dwTerretBullet_Stand = GetTickCount();
	m_dwTerretBullet_Limit = 350;
}
CTimeClass::~CTimeClass()
{

}
void CTimeClass::Init()
{
	m_dwStandMonster = GetTickCount();
	m_dwLimitMonster = 150;
	m_dwCountLimit = 1000;
	m_dwCountStand = GetTickCount();
	m_dwSubLimit = 150;
	m_dwSubStand = GetTickCount();
	m_dwBulletLimit = 48;
	m_dwBulletStand = GetTickCount();
	m_dwBullet_Reload_Stand = GetTickCount();
	m_dwBullet_Reload_Limit = 1000;
	m_dwBarrier_Limit = 1000;
	m_dwBarrier_Stand = GetTickCount();
	m_dwBossBullet_Limit = 300;
	m_dwBossBullet_Stand = GetTickCount();
	m_dwBossColor_Stand = GetTickCount();
	m_dwBossColor_Limit = 1500;
	m_dwTerret_Limit = 1000;
	m_dwTerret_Stand = GetTickCount();
	m_dwTerretBullet_Stand = GetTickCount();
	m_dwTerretBullet_Limit = 350;
	m_dwBossSkill_Stand = GetTickCount();
	m_dwBossSkill_Limit = 15000;
	m_dwHeroZBullet_Stand = GetTickCount();
	m_dwHeroZBullet_Limit = 3;
}