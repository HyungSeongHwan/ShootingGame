
//  < Include.h ���� >
//  > Include ���ϵ��� ��� �Ѱ��� ����ش�
/// - ���� : �����ϱ� ���ϴ�.

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <crtdbg.h>
#include "../ConsoleEx3/ConWrap.h"
#include "mmsystem.h"


#define BulletCount 50


#include "Hero.h"; // �ڵ����� ���� ��������� ������
extern stHero g_Hero; // �ܺο� �ִ� ������ ���� �� �� �ִ� (����ü�� ���ǵ� ������� �ؿ� ����.)

#include "Bullet.h";
extern stBullet g_ArrBullet[BulletCount];

#endif