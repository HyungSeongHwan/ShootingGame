#include "Include.h"

void Effect_Init(int MonPosX, int MonPosY)
 {
	for (int i = 0; i < EffectSize; i++)
	{
		g_ArrEffect[i].x = MonPosX;
		g_ArrEffect[i].y = MonPosY;

		g_ArrEffect[i].time = GetTickCount() + 300;
		g_ArrEffect[i].idx = 0;

		g_ArrEffect[i].fColor = WHITE;
		g_ArrEffect[i].bColor = BLACK;
		g_ArrEffect[i].IsActive = true;
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
		if (g_ArrEffect[i].IsActive)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					DrawCharEx3(g_ArrEffect[i].x + k, g_ArrEffect[i].y + j,
						g_Effect[g_ArrEffect[i].idx][j][k], g_ArrEffect[i].fColor, g_ArrEffect[i].bColor);
				}
			}
		}
	}
}

void Effect_Animation()
{
	for (int i = 0; i < EffectSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (g_ArrEffect[i].IsActive && g_ArrEffect[i].time < GetTickCount())
			{
				g_ArrEffect[i].time = GetTickCount() + 300;
				g_ArrEffect[i].idx++;

				if (g_ArrEffect[i].idx > 2)
					g_ArrEffect[i].IsActive = false;
			}
		}
	}
}
