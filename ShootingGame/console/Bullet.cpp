#include "Include.h"


void Bullet_Init()
{
	for (int i = 0; i < BulletSize; i++) 
	{
		g_GameMgr.ArrBullet[i].speed = 1;

		g_GameMgr.ArrBullet[i].fColor = GREEN;
		g_GameMgr.ArrBullet[i].bColor = BLACK;

		g_GameMgr.ArrBullet[i].body = '^';
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
		if (g_GameMgr.ArrBullet[i].IsActive)
			DrawCharEx3(g_GameMgr.ArrBullet[i].x, g_GameMgr.ArrBullet[i].y, g_GameMgr.ArrBullet[i].body, g_GameMgr.ArrBullet[i].fColor, g_GameMgr.ArrBullet[i].bColor);
	}
}

void Bullet_Move()
{
	for (int i = 0; i < BulletSize; i++)
	{
		g_GameMgr.ArrBullet[i].y -= g_GameMgr.ArrBullet[i].speed;
	}
}

void Bullet_LockUp()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (g_GameMgr.ArrBullet[i].y < 0)
			g_GameMgr.ArrBullet[i].IsActive = false;
	}
}
