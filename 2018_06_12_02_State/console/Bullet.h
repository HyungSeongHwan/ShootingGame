#pragma once

struct stBullet
{
	int x, y;
	int speed;
	char body;

	DWORD fColor;
	DWORD bColor;

	bool IsAlive = false;
};

void Bullet_Init();
void Bullet_Update();
void Bullet_Draw();