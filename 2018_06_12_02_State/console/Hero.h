#pragma once

struct stHero
{
	int x, y;
	char body;
	int speed;
	int attack;
	int hp;

	DWORD fColor; // front Color
	DWORD bColor; // background Color
};

void Hero_Init(); // Hero �� �ʱ�ȭ�ϴ� �Լ�

void Hero_Update(); // Hero �� ������Ʈ �Ѵ�.
void Hero_Draw(); // Hero �� �׸���.
void Hero_Fire();
void Hero_Cliping();