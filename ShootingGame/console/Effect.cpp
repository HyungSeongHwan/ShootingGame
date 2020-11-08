#include "Include.h"

void Effect_Init()
 {
	for (int i = 0; i < EffectSize; i++)
	{
		g_GameMgr.ArrEffect[i].x = -1000;
		g_GameMgr.ArrEffect[i].y = -1000;

		g_GameMgr.ArrEffect[i].nIdx = 0;

		g_GameMgr.ArrEffect[i].fColor = WHITE;
		g_GameMgr.ArrEffect[i].bColor = BLACK;

		g_GameMgr.ArrEffect[i].IsActive = false;
	}
}

void Effect_Update()
{
	Effect_Animation();
}

void Effect_Draw()
{
	for (int i = 0; i < EffectSize; i++)
	{
		if (g_GameMgr.ArrEffect[i].IsActive)
		{
			for (int j = 0; j < FXImgSize; j++)
			{
				for (int k = 0; k < FXImgSize; k++)
				{
					DrawCharEx3(g_GameMgr.ArrEffect[i].x + k - 1, g_GameMgr.ArrEffect[i].y + j - 1,
						g_GameMgr.MonPopEffect[g_GameMgr.ArrEffect[i].nIdx][j][k], g_GameMgr.ArrEffect[i].fColor, g_GameMgr.ArrEffect[i].bColor);
				}
			}
		}
	}
}

void Effect_Animation()
{
	for (int i = 0; i < EffectSize; i++)
	{
		for (int j = 0; j < FXImgSize; j++)
		{
			if (g_GameMgr.ArrEffect[i].IsActive && g_GameMgr.ArrEffect[i].animDelayTime < GetTickCount())
			{
				g_GameMgr.ArrEffect[i].animDelayTime = GetTickCount() + 300;
				g_GameMgr.ArrEffect[i].nIdx++;

				if (g_GameMgr.ArrEffect[i].nIdx > FXImgSize - 1)
					g_GameMgr.ArrEffect[i].IsActive = false;
					
			}
		}
	}
}

void Effect_Create(int MonPosX, int MonPosY)
{
	for (int i = 0; i < EffectSize; i++)
	{
		if (!g_GameMgr.ArrEffect[i].IsActive)
		{
			g_GameMgr.ArrEffect[i].x = MonPosX;
			g_GameMgr.ArrEffect[i].y = MonPosY;

			g_GameMgr.ArrEffect[i].nIdx = 0;
			g_GameMgr.ArrEffect[i].animDelayTime = GetTickCount() + 300;

			g_GameMgr.ArrEffect[i].IsActive = true;

			break;
		}
	}
}
