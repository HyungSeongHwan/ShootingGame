
//  < Include.h 파일 >
//  > Include 파일들을 모두 한곳에 모아준다
/// - 장점 : 관리하기 편하다.

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


#include "Hero.h"; // 자동으로 위의 헤더파일이 속해짐
#include "Bullet.h";
#include "Monster.h";
#include "Effect.h";


extern stHero g_Hero; // 외부에 있는 변수를 직접 쓸 수 있다 (구조체가 정의된 헤더파일 밑에 쓴다.)

extern stBullet g_ArrBullet[BulletSize];
extern DWORD dwBulletFureTime;

extern stMonster g_ArrMonster[MonsterSize];
extern DWORD dwMonsterSpawnDelay;
extern int g_nScore;

extern stEffect g_ArrEffect[EffectSize];
extern char g_Effect[3][3][3];

#endif