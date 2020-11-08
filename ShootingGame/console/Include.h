
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

#define BulletSize 50
#define MonsterSize 50
#define EffectSize 10
#define FXImgSize 3


#include "Hero.h" // �ڵ����� ���� ��������� ������
#include "Bullet.h"
#include "Monster.h"
#include "Effect.h"
#include "GameMgr.h"


extern stGameMgr g_GameMgr;

#endif