#include "Include.h"


stBullet g_ArrBullet[BulletCount];

void Hero_Init()
{
	g_Hero.x = 0;
	g_Hero.y = 0;
	g_Hero.attack = 1;
	g_Hero.hp = 5;
	g_Hero.fColor = WHITE;
	g_Hero.bColor = BLACK;
	g_Hero.body = 'A';
	g_Hero.speed = 1;

	Hero_Cliping();
}

void Hero_Update()
{
	//  > IsKey : 매크 로함수
	if (IsKey(VK_LEFT)) // 만약 LEFT 키를 누른다면
	{
		g_Hero.x -= g_Hero.speed; // g_Hero 의 x 좌표 - g_Hero.speed;
	}

	if (IsKey(VK_UP)) // 만약 VK_UP 키를 누른다면
	{
		g_Hero.y -= g_Hero.speed; // g_Hero 의 y 좌표 - g_Hero.speed;
	}

	if (IsKey(VK_RIGHT)) // 만약 VK_RIGHT 키를 누른다면
	{
		g_Hero.x += g_Hero.speed; // g_Hero 의 x 좌표 + g_Hero.speed;
	}

	if (IsKey(VK_DOWN)) // 만약 VK_DOWN 키를 누른다면
	{
		g_Hero.y += g_Hero.speed; // g_Hero 의 x 좌표 + g_Hero.speed;
	}

	Hero_Cliping();

	if (IsKey(VK_SPACE))
	{
		Hero_Fire();
	}
}

void Hero_Draw()
{
	DrawCharEx3(g_Hero.x, g_Hero.y, g_Hero.body, g_Hero.fColor, g_Hero.bColor); // 문자 출력
}

void Hero_Fire()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (!g_ArrBullet[i].IsAlive)
		{
			g_ArrBullet[i].x = g_Hero.x;
			g_ArrBullet[i].y = g_Hero.y;
			g_ArrBullet[i].speed = 2;

			g_ArrBullet[i].fColor = RED;
			g_ArrBullet[i].bColor = BLACK;
						
			g_ArrBullet[i].body = '^';
			g_ArrBullet[i].IsAlive = true;

			break; //for문끝내기
		}
	}

}

void Hero_Cliping() // 플레이어가 맵밖으로 못나가게 하는 함수
{
	if (g_Hero.y > 29)
	{
		g_Hero.y = 29;
	}

	if (g_Hero.x > 119)
	{
		g_Hero.x = 119;
	}

	if (g_Hero.y < 0)
	{
		g_Hero.y = 0;
	}

	if (g_Hero.x < 0)
	{
		g_Hero.x = 0;
	}
}