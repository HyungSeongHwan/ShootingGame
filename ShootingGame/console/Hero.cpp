#include "Include.h"


void Hero_Init()
{
	g_GameMgr.Hero.x = WIDTH / 2;
	g_GameMgr.Hero.y = HEIGHT / 2;
	g_GameMgr.Hero.attack = 1;
	g_GameMgr.Hero.hp = 5;
	g_GameMgr.Hero.fColor = WHITE;
	g_GameMgr.Hero.bColor = BLACK;
	g_GameMgr.Hero.body = 'A';
	g_GameMgr.Hero.speed = 1;

	Hero_Cliping();
}

void Hero_Update()
{
	Hero_Move();
	Hero_Cliping();
	Hero_Fire();
}

void Hero_Draw()
{
	DrawCharEx3(g_GameMgr.Hero.x, g_GameMgr.Hero.y, g_GameMgr.Hero.body, g_GameMgr.Hero.fColor, g_GameMgr.Hero.bColor); // ���� ���
}

void Hero_CreateBullet()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (!g_GameMgr.ArrBullet[i].IsActive)
		{
			g_GameMgr.ArrBullet[i].x = g_GameMgr.Hero.x;
			g_GameMgr.ArrBullet[i].y = g_GameMgr.Hero.y;
			g_GameMgr.ArrBullet[i].IsActive = true;

			break; //for��������
		}
	}

}

void Hero_Move()
{
	//  > IsKey : ��ũ ���Լ�
	if (IsKey(VK_LEFT)) // ���� LEFT Ű�� �����ٸ�
	{
		g_GameMgr.Hero.x -= g_GameMgr.Hero.speed; // g_Hero �� x ��ǥ - g_Hero.speed;
	}

	if (IsKey(VK_UP)) // ���� VK_UP Ű�� �����ٸ�
	{
		g_GameMgr.Hero.y -= g_GameMgr.Hero.speed; // g_Hero �� y ��ǥ - g_Hero.speed;
	}

	if (IsKey(VK_RIGHT)) // ���� VK_RIGHT Ű�� �����ٸ�
	{
		g_GameMgr.Hero.x += g_GameMgr.Hero.speed; // g_Hero �� x ��ǥ + g_Hero.speed;
	}

	if (IsKey(VK_DOWN)) // ���� VK_DOWN Ű�� �����ٸ�
	{
		g_GameMgr.Hero.y += g_GameMgr.Hero.speed; // g_Hero �� x ��ǥ + g_Hero.speed;
	}
}

void Hero_Cliping() // �÷��̾ �ʹ����� �������� �ϴ� �Լ�
{
	if (g_GameMgr.Hero.y > HEIGHT - 2)
	{
		g_GameMgr.Hero.y = HEIGHT - 2;
	}

	if (g_GameMgr.Hero.x > WIDTH - 2)
	{
		g_GameMgr.Hero.x = WIDTH - 2;
	}

	if (g_GameMgr.Hero.y < 3)
	{
		g_GameMgr.Hero.y = 3;
	}

	if (g_GameMgr.Hero.x < 1)
	{
		g_GameMgr.Hero.x = 1;
	}
}

void Hero_Fire()
{
	if (IsKey(VK_SPACE) && g_GameMgr.dwBulletFureTime < GetTickCount())
	{
		g_GameMgr.dwBulletFureTime = GetTickCount() + 10; // 0.2�� ���� �����̸� �ش�.
		Hero_CreateBullet();
	}
}