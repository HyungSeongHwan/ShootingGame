#include "Include.h"


stBullet g_ArrBullet[BulletCount];

void Hero_Init()
{
	g_Hero.x = 0;
	g_Hero.y = 0;
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

	Hero_Cliping();

	if (IsKey(VK_SPACE))
	{
		Hero_Fire();
	}
}

void Hero_Draw()
{
	DrawCharEx3(g_Hero.x, g_Hero.y, g_Hero.body, g_Hero.fColor, g_Hero.bColor); // ���� ���
}

void Hero_Fire()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (!g_ArrBullet[i].IsAlive)
		{
			g_ArrBullet[i].x = g_Hero.x;
			g_ArrBullet[i].y = g_Hero.y;
			g_ArrBullet[i].speed = 2;

			g_ArrBullet[i].fColor = RED;
			g_ArrBullet[i].bColor = BLACK;
						
			g_ArrBullet[i].body = '^';
			g_ArrBullet[i].IsAlive = true;

			break; //for��������
		}
	}

}

void Hero_Cliping() // �÷��̾ �ʹ����� �������� �ϴ� �Լ�
{
	if (g_Hero.y > 29)
	{
		g_Hero.y = 29;
	}

	if (g_Hero.x > 119)
	{
		g_Hero.x = 119;
	}

	if (g_Hero.y < 0)
	{
		g_Hero.y = 0;
	}

	if (g_Hero.x < 0)
	{
		g_Hero.x = 0;
	}
}