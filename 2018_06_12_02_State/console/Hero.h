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

void Hero_Init(); // Hero 를 초기화하는 함수

void Hero_Update(); // Hero 를 업데이트 한다.
void Hero_Draw(); // Hero 를 그린다.
void Hero_Fire();
void Hero_Cliping();