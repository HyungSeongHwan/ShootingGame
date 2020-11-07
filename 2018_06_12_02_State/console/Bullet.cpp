#include "Include.h"


void Bullet_Init()
{
	//g_ArrBullet[0].x;
	//g_ArrBullet[0].y;
	//g_ArrBullet[0].speed = 2;
	//
	//g_ArrBullet[0].fColor = RED;
	//g_ArrBullet[0].bColor = BLACK;
	//
	//g_ArrBullet[0].body = '^';
}

void Bullet_Update()
{
	for (int i = 0; i < BulletCount; i++)
	{
		g_ArrBullet[i].y -= g_ArrBullet[i].speed;
		if (g_ArrBullet[i].y < 0)
			g_ArrBullet[i].IsAlive = false;
	}
}

void Bullet_Draw()
{
	for (int i = 0; i < BulletCount; i++)
		DrawCharEx3(g_ArrBullet[i].x, g_ArrBullet[i].y, g_ArrBullet[i].body, g_ArrBullet[i].fColor, g_ArrBullet[i].bColor);
}
