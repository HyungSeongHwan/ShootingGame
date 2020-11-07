#pragma once

struct stEffect 
{
	int x, y;

	int idx;
	int time;

	DWORD fColor;
	DWORD bColor;

	bool IsActive;
};

void Effect_Init(int x, int y);
void Effect_Update();
void Effect_Draw();
void Effect_Animation();