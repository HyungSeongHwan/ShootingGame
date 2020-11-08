#include "Include.h"


void GameMgr_Init()
{
	Hero_Init();
	Bullet_Init();
	Monster_Init();
	Effect_Init();
}

void GameMgr_Update()
{
	Hero_Update();
	Bullet_Update();
	Monster_Update();
	Effect_Update();
}

void GameMgr_Draw()
{
	Hero_Draw();
	Bullet_Draw();
	Monster_Draw();
	Effect_Draw();

	GameMgr_DrawUI();
}

void GameMgr_DrawUI()
{
	// Side UI
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (g_GameMgr.nUI[i][j] == 1)
				DrawFillBoxEx3(j, i, 1, 1, YELLOW);
		}
	}

	// Score UI
	sprintf(g_GameMgr.cScore, "Score    : %d", g_GameMgr.nScore);
	DrawStrEx3(1, 1, g_GameMgr.cScore, LIGHTGREEN, BLACK);

	// GamePlayTime UI
	if (g_GameMgr.dwGMPlayTime < GetTickCount())
	{
		g_GameMgr.dwGMPlayTime = GetTickCount() + 1000;

		++g_GameMgr.nPlayTime;

		sprintf(g_GameMgr.cPlayTime, "PlayTime : %d", g_GameMgr.nPlayTime);
	}
	DrawStrEx3(1, 2, g_GameMgr.cPlayTime, LIGHTGREEN, BLACK);
}