
//  < Include.h 파일 >
//  > Include 파일들을 모두 한곳에 모아준다
/// - 장점 : 관리하기 편하다.

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <crtdbg.h>
#include "../ConsoleEx3/ConWrap.h"
#include "mmsystem.h"


#define BulletCount 50


#include "Hero.h"; // 자동으로 위의 헤더파일이 속해짐
extern stHero g_Hero; // 외부에 있는 변수를 직접 쓸 수 있다 (구조체가 정의된 헤더파일 밑에 쓴다.)

#include "Bullet.h";
extern stBullet g_ArrBullet[BulletCount];

#endif