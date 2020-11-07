#include "Include.h"


void Hero_Init()
{
	g_Hero.x = WIDTH / 2;
	g_Hero.y = HEIGHT / 2;
	g_Hero.attack = 1;
	g_Hero.hp = 5;
	g_Hero.fColor = WHITE;
	g_Hero.bColor = BLACK;
	g_Hero.body = 'A';
	g_Hero.speed = 1;

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
	DrawCharEx3(g_Hero.x, g_Hero.y, g_Hero.body, g_Hero.fColor, g_Hero.bColor); // ���� ���
}

void Hero_CreateBullet()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (!g_ArrBullet[i].IsActive)
		{
			g_ArrBullet[i].x = g_Hero.x;
			g_ArrBullet[i].y = g_Hero.y;
			g_ArrBullet[i].IsActive = true;

			break; //for��������
		}
	}

}

void Hero_Move()
{
	//  > IsKey : ��ũ ���Լ�
	if (IsKey(VK_LEFT)) // ���� LEFT Ű�� �����ٸ�
	{
		g_Hero.x -= g_Hero.speed; // g_Hero �� x ��ǥ - g_Hero.speed;
	}

	if (IsKey(VK_UP)) // ���� VK_UP Ű�� �����ٸ�
	{
		g_Hero.y -= g_Hero.speed; // g_Hero �� y ��ǥ - g_Hero.speed;
	}

	if (IsKey(VK_RIGHT)) // ���� VK_RIGHT Ű�� �����ٸ�
	{
		g_Hero.x += g_Hero.speed; // g_Hero �� x ��ǥ + g_Hero.speed;
	}

	if (IsKey(VK_DOWN)) // ���� VK_DOWN Ű�� �����ٸ�
	{
		g_Hero.y += g_Hero.speed; // g_Hero �� x ��ǥ + g_Hero.speed;
	}
}

void Hero_Cliping() // �÷��̾ �ʹ����� �������� �ϴ� �Լ�
{
	if (g_Hero.y > HEIGHT - 2)
	{
		g_Hero.y = HEIGHT - 2;
	}

	if (g_Hero.x > WIDTH - 2)
	{
		g_Hero.x = WIDTH - 2;
	}

	if (g_Hero.y < 3)
	{
		g_Hero.y = 3;
	}

	if (g_Hero.x < 1)
	{
		g_Hero.x = 1;
	}
}

void Hero_Fire()
{
	if (IsKey(VK_SPACE) && dwBulletFureTime < GetTickCount())
	{
		dwBulletFureTime = GetTickCount() + 200; // 0.2�� ���� �����̸� �ش�.
		Hero_CreateBullet();
	}
}