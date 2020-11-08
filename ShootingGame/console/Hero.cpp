#include "Include.h"


void Hero_Init()
{
	g_GameMgr.Hero.x = WIDTH / 2;
	g_GameMgr.Hero.y = HEIGHT / 2;
	g_GameMgr.Hero.attack = 1;
	g_GameMgr.Hero.hp = 5;
	g_GameMgr.Hero.fColor = WHITE;
	g_GameMgr.Hero.bColor = BLACK;
	g_GameMgr.Hero.body = 'A';
	g_GameMgr.Hero.speed = 1;

	Hero_Cliping();
}

void Hero_Update()
{
	Hero_Move();
	Hero_Cliping();
	Hero_Fire();
}

void Hero_Draw()
{
	DrawCharEx3(g_GameMgr.Hero.x, g_GameMgr.Hero.y, g_GameMgr.Hero.body, g_GameMgr.Hero.fColor, g_GameMgr.Hero.bColor); // 문자 출력
}

void Hero_CreateBullet()
{
	for (int i = 0; i < BulletSize; i++)
	{
		if (!g_GameMgr.ArrBullet[i].IsActive)
		{
			g_GameMgr.ArrBullet[i].x = g_GameMgr.Hero.x;
			g_GameMgr.ArrBullet[i].y = g_GameMgr.Hero.y;
			g_GameMgr.ArrBullet[i].IsActive = true;

			break; //for문끝내기
		}
	}

}

void Hero_Move()
{
	//  > IsKey : 매크 로함수
	if (IsKey(VK_LEFT)) // 만약 LEFT 키를 누른다면
	{
		g_GameMgr.Hero.x -= g_GameMgr.Hero.speed; // g_Hero 의 x 좌표 - g_Hero.speed;
	}

	if (IsKey(VK_UP)) // 만약 VK_UP 키를 누른다면
	{
		g_GameMgr.Hero.y -= g_GameMgr.Hero.speed; // g_Hero 의 y 좌표 - g_Hero.speed;
	}

	if (IsKey(VK_RIGHT)) // 만약 VK_RIGHT 키를 누른다면
	{
		g_GameMgr.Hero.x += g_GameMgr.Hero.speed; // g_Hero 의 x 좌표 + g_Hero.speed;
	}

	if (IsKey(VK_DOWN)) // 만약 VK_DOWN 키를 누른다면
	{
		g_GameMgr.Hero.y += g_GameMgr.Hero.speed; // g_Hero 의 x 좌표 + g_Hero.speed;
	}
}

void Hero_Cliping() // 플레이어가 맵밖으로 못나가게 하는 함수
{
	if (g_GameMgr.Hero.y > HEIGHT - 2)
	{
		g_GameMgr.Hero.y = HEIGHT - 2;
	}

	if (g_GameMgr.Hero.x > WIDTH - 2)
	{
		g_GameMgr.Hero.x = WIDTH - 2;
	}

	if (g_GameMgr.Hero.y < 3)
	{
		g_GameMgr.Hero.y = 3;
	}

	if (g_GameMgr.Hero.x < 1)
	{
		g_GameMgr.Hero.x = 1;
	}
}

void Hero_Fire()
{
	if (IsKey(VK_SPACE) && g_GameMgr.dwBulletFureTime < GetTickCount())
	{
		g_GameMgr.dwBulletFureTime = GetTickCount() + 10; // 0.2초 동안 딜레이를 준다.
		Hero_CreateBullet();
	}
}