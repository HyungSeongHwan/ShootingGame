class CTimeClass
{
public:
	DWORD m_dwStandMonster;		//몬스터 시간 변수
	DWORD m_dwLimitMonster;		//몬스터 시간 변수
	DWORD m_dwCountStand;		//게임 시작 시간 측정 변수
	DWORD m_dwCountLimit;		//게임 시작 시간 측정 변수
	DWORD m_dwSubStand;			//서브 몬스터 스폰 시간 변수
	DWORD m_dwSubLimit;			//서브 몬스터 스폰 시간 변수
	DWORD m_dwBulletStand;		//히어로 총알 딜레이 변수
	DWORD m_dwBulletLimit;		//히어로 총알 딜레이 변수
	DWORD m_dwBullet_Reload_Stand;		//총 재장전 시간
	DWORD m_dwBullet_Reload_Limit;		//총 재장전 시간
	DWORD m_dwBarrier_Stand;		//장애물이 생기는 딜레이 시간
	DWORD m_dwBarrier_Limit;		//장애물이 생기는 딜레이 시간
	DWORD m_dwBossBullet_Stand;		//보스 총알 딜레이 시간
	DWORD m_dwBossBullet_Limit;		//보스 총알 딜레이 시간
	DWORD m_dwBossColor_Stand;		//보스가 총알에 맞았을때 색깔 변화 시간 변수
	DWORD m_dwBossColor_Limit;		//보스가 총알에 맞았을때 색깔 변화 시간 변수
	DWORD m_dwTerret_Stand;		//터렛 설치 딜레이 변수
	DWORD m_dwTerret_Limit;		//터렛 설치 딜레이 변수
	DWORD m_dwTerretBullet_Stand;		//터렛 총알 발사 딜레이 변수
	DWORD m_dwTerretBullet_Limit;		//터렛 총알 발사 딜레이 변수
	DWORD m_dwBossSkill_Stand;		//보스가 스킬을 쓰는 딜레이 변수
	DWORD m_dwBossSkill_Limit;		//보스가 스킬을 쓰는 딜레이 변수
	DWORD m_dwHeroZBullet_Stand;		//히어로 3가 Z키를 눌러 탄창을 모을떄
	DWORD m_dwHeroZBullet_Limit;		//히어로 3가 Z키를 눌러 탄창을 모을떄
public:
	CTimeClass();
	~CTimeClass();
public:
	void Init();
};