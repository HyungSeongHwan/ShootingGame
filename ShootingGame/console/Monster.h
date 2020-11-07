#pragma once

struct stMonster
{
	float x, y;

	int hp;
	float speed;
	int damage;

	char body;

	DWORD fColor;
	DWORD bColor;

	bool IsActive = false;
};

void Monster_Init(); // 몬스터 초기화 함수
void Monster_Update(); // 몬스터 업데이트 함수
void Monster_Draw(); // 몬스터를 그리는 함수
void Monster_Move(); // 몬스터를 아래로 떨어지게 하는 함수
void Monster_Spawn(); // 몬스터 스폰
void Monster_LockUp(); // 몬스터가 밖으로 못나가게 하는 함수
void Monster_TriggerBullet(); // 몬스터가 총알과 충돌하는지 감지하는 함수