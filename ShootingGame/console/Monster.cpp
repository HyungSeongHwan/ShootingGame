#include "Include.h"


void Monster_Init()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		g_ArrMonster[i].x = -1;
		g_ArrMonster[i].y = 0;

		g_ArrMonster[i].hp = 2;
		g_ArrMonster[i].speed = 0.5;
		g_ArrMonster[i].damage = 1;
		
		g_ArrMonster[i].body = '@';

		g_ArrMonster[i].fColor = RED;
		g_ArrMonster[i].bColor = BLACK;
	}
}

void Monster_Update()
{
	Monster_Spawn();
	Monster_Move();
	Monster_LockUp();
	Monster_TriggerBullet();
}

void Monster_Draw()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		if (g_ArrMonster[i].IsActive)
			DrawCharEx3(g_ArrMonster[i].x, g_ArrMonster[i].y, g_ArrMonster[i].body, g_ArrMonster[i].fColor, g_ArrMonster[i].bColor);
	}
		
}

void Monster_Move()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		g_ArrMonster[i].y += g_ArrMonster[i].speed;
	}
}

void Monster_Spawn()
{
	if (dwMonsterSpawnDelay < GetTickCount()) 
	{
		dwMonsterSpawnDelay = GetTickCount() + 1000;

		for (int i = 0; i < MonsterSize; i++)
		{
			if (!g_ArrMonster[i].IsActive)
			{
				int nRandPosX = rand() % WIDTH;

				g_ArrMonster[i].x = nRandPosX;
				g_ArrMonster[i].y = 0;

				g_ArrMonster[i].IsActive = true;

				break;
			}
		}
	}
}

void Monster_LockUp()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		if (g_ArrMonster[i].y > HEIGHT)
			g_ArrMonster[i].IsActive = false;
	}
}

void Monster_TriggerBullet()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		if (g_ArrMonster[i].IsActive)
		{
			for (int j = 0; j < BulletSize; j++)
			{
				if (g_ArrBullet[j].IsActive)
				{
					if (g_ArrMonster[i].y >= g_ArrBullet[j].y && g_ArrMonster[i].x == g_ArrBullet[j].x)
					{
						Effect_Init(g_ArrMonster[i].x, g_ArrMonster[i].y);
						g_ArrMonster[i].y = 31;
						++g_nScore;
					}

				}
			}
		}
	}
}
