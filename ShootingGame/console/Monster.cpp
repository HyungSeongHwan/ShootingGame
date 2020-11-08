#include "Include.h"


void Monster_Init()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		g_GameMgr.ArrMonster[i].x = -1;
		g_GameMgr.ArrMonster[i].y = 0;

		g_GameMgr.ArrMonster[i].hp = 2;
		g_GameMgr.ArrMonster[i].speed = 0.5;
		g_GameMgr.ArrMonster[i].damage = 1;
		
		g_GameMgr.ArrMonster[i].body = '@';

		g_GameMgr.ArrMonster[i].fColor = RED;
		g_GameMgr.ArrMonster[i].bColor = BLACK;
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
		if (g_GameMgr.ArrMonster[i].IsActive)
			DrawCharEx3(g_GameMgr.ArrMonster[i].x, g_GameMgr.ArrMonster[i].y, g_GameMgr.ArrMonster[i].body, g_GameMgr.ArrMonster[i].fColor, g_GameMgr.ArrMonster[i].bColor);
	}
		
}

void Monster_Move()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		g_GameMgr.ArrMonster[i].y += g_GameMgr.ArrMonster[i].speed;
	}
}

void Monster_Spawn()
{
	if (g_GameMgr.dwMonsterSpawnDelay < GetTickCount())
	{
		g_GameMgr.dwMonsterSpawnDelay = GetTickCount() + 500;

		for (int i = 0; i < MonsterSize; i++)
		{
			if (!g_GameMgr.ArrMonster[i].IsActive)
			{
				int nRandPosX = rand() % WIDTH;

				g_GameMgr.ArrMonster[i].x = nRandPosX;
				g_GameMgr.ArrMonster[i].y = 0;
				
				g_GameMgr.ArrMonster[i].IsActive = true;

				break;
			}
		}
	}
}

void Monster_LockUp()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		if (g_GameMgr.ArrMonster[i].y > HEIGHT)
			g_GameMgr.ArrMonster[i].IsActive = false;
	}
}

void Monster_TriggerBullet()
{
	for (int i = 0; i < MonsterSize; i++)
	{
		if (g_GameMgr.ArrMonster[i].IsActive)
		{
			for (int j = 0; j < BulletSize; j++)
			{
				if (g_GameMgr.ArrBullet[j].IsActive)
				{
					if (g_GameMgr.ArrMonster[i].y >= g_GameMgr.ArrBullet[j].y && g_GameMgr.ArrMonster[i].x == g_GameMgr.ArrBullet[j].x)
					{
						Effect_Create(g_GameMgr.ArrMonster[i].x, g_GameMgr.ArrMonster[i].y);
						g_GameMgr.ArrMonster[i].y = HEIGHT + 1;
						++g_GameMgr.nScore;
					}

				}
			}
		}
	}
}
