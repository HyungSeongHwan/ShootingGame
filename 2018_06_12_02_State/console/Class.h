class CTimeClass
{
public:
	DWORD m_dwStandMonster;		//���� �ð� ����
	DWORD m_dwLimitMonster;		//���� �ð� ����
	DWORD m_dwCountStand;		//���� ���� �ð� ���� ����
	DWORD m_dwCountLimit;		//���� ���� �ð� ���� ����
	DWORD m_dwSubStand;			//���� ���� ���� �ð� ����
	DWORD m_dwSubLimit;			//���� ���� ���� �ð� ����
	DWORD m_dwBulletStand;		//����� �Ѿ� ������ ����
	DWORD m_dwBulletLimit;		//����� �Ѿ� ������ ����
	DWORD m_dwBullet_Reload_Stand;		//�� ������ �ð�
	DWORD m_dwBullet_Reload_Limit;		//�� ������ �ð�
	DWORD m_dwBarrier_Stand;		//��ֹ��� ����� ������ �ð�
	DWORD m_dwBarrier_Limit;		//��ֹ��� ����� ������ �ð�
	DWORD m_dwBossBullet_Stand;		//���� �Ѿ� ������ �ð�
	DWORD m_dwBossBullet_Limit;		//���� �Ѿ� ������ �ð�
	DWORD m_dwBossColor_Stand;		//������ �Ѿ˿� �¾����� ���� ��ȭ �ð� ����
	DWORD m_dwBossColor_Limit;		//������ �Ѿ˿� �¾����� ���� ��ȭ �ð� ����
	DWORD m_dwTerret_Stand;		//�ͷ� ��ġ ������ ����
	DWORD m_dwTerret_Limit;		//�ͷ� ��ġ ������ ����
	DWORD m_dwTerretBullet_Stand;		//�ͷ� �Ѿ� �߻� ������ ����
	DWORD m_dwTerretBullet_Limit;		//�ͷ� �Ѿ� �߻� ������ ����
	DWORD m_dwBossSkill_Stand;		//������ ��ų�� ���� ������ ����
	DWORD m_dwBossSkill_Limit;		//������ ��ų�� ���� ������ ����
	DWORD m_dwHeroZBullet_Stand;		//����� 3�� ZŰ�� ���� źâ�� ������
	DWORD m_dwHeroZBullet_Limit;		//����� 3�� ZŰ�� ���� źâ�� ������
public:
	CTimeClass();
	~CTimeClass();
public:
	void Init();
};