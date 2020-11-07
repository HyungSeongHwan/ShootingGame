
//  < Include.h ���� >
//  > Include ���ϵ��� ��� �Ѱ��� ����ش�
/// - ���� : �����ϱ� ���ϴ�.

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <crtdbg.h>
#include <time.h>
#include "../ConsoleEx3/ConWrap.h"
#include "mmsystem.h"


#define WIDTH 120
#define HEIGHT 30

#define BulletSize 5
#define MonsterSize 50
#define EffectSize 5


#include "Hero.h"; // �ڵ����� ���� ��������� ������
#include "Bullet.h";
#include "Monster.h";
#include "Effect.h";


extern stHero g_Hero; // �ܺο� �ִ� ������ ���� �� �� �ִ� (����ü�� ���ǵ� ������� �ؿ� ����.)

extern stBullet g_ArrBullet[BulletSize];
extern DWORD dwBulletFureTime;

extern stMonster g_ArrMonster[MonsterSize];
extern DWORD dwMonsterSpawnDelay;
extern int g_nScore;

extern stEffect g_ArrEffect[EffectSize];
extern char g_Effect[3][3][3];

#endif