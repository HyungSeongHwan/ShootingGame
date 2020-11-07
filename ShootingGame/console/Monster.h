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

void Monster_Init(); // ���� �ʱ�ȭ �Լ�
void Monster_Update(); // ���� ������Ʈ �Լ�
void Monster_Draw(); // ���͸� �׸��� �Լ�
void Monster_Move(); // ���͸� �Ʒ��� �������� �ϴ� �Լ�
void Monster_Spawn(); // ���� ����
void Monster_LockUp(); // ���Ͱ� ������ �������� �ϴ� �Լ�
void Monster_TriggerBullet(); // ���Ͱ� �Ѿ˰� �浹�ϴ��� �����ϴ� �Լ�