#include "Include.h"


void Bullet_Init()
{
	for (int i = 0; i < BulletSize; i++) 
	{
		g_ArrBullet[i].speed = 1;

		g_ArrBullet[i].fColor = GREEN;
		g_ArrBullet[i].bColor = BLACK;

		g_ArrBullet[i].body = '^';
	}
}

void Bullet_Update()
{
	Bullet_Move();
	Bullet_LockUp();
}

void Bullet_Draw()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (g_ArrBullet[i].IsActive)
			DrawCharEx3(g_ArrBullet[i].x, g_ArrBullet[i].y, g_ArrBullet[i].body, g_ArrBullet[i].fColor, g_ArrBullet[i].bColor);
	}
}

void Bullet_Move()
{
	for (int i = 0; i < BulletSize; i++)
	{
		g_ArrBullet[i].y -= g_ArrBullet[i].speed;
	}
}

void Bullet_LockUp()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (g_ArrBullet[i].y < 0)
			g_ArrBullet[i].IsActive = false;
	}
}
