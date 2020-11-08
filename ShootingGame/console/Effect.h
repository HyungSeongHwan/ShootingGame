#pragma once

struct stEffect 
{
	int x, y;

	int nIdx;
	int animDelayTime;

	DWORD fColor;
	DWORD bColor;

	bool IsActive;
};

void Effect_Init();
void Effect_Update();
void Effect_Draw();
void Effect_Animation();
void Effect_Create(int MonPosX, int MonPosY);