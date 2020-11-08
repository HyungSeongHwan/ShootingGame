
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

#define BulletSize 50
#define MonsterSize 50
#define EffectSize 10
#define FXImgSize 3


#include "Hero.h" // 자동으로 위의 헤더파일이 속해짐
#include "Bullet.h"
#include "Monster.h"
#include "Effect.h"
#include "GameMgr.h"


extern stGameMgr g_GameMgr;

#endif