#include "Include.h"

// �밡���� ǥ���
// int    n�̸�
// char   c�̸�
// bool   b�̸�	
// DWORD  dw�̸�
// short  s�̸�
// long   l�̸�
// ����ü �ɹ������� 
// int m_n�̸�
// char  m_c�̸�
// �۷ι� g_?�̸�
// int nVlaue = 0;
// void Quit();


stHero g_Hero;

int main()
{
	InitialConsole();//�ʱ�ȭ�Լ�
	Hero_Init();

	SetWindowTitle("Shooting"); // ������ Ÿ��Ʋ �̸� ����
	while (true) // ���۽� ���ѷ���
	{
		CheckInput(); // ���� Ű�� �������� üũ�Ѵ�
		ClearScreenEx3(BLACK); // ����ȭ�� �� ����(���� : ������)

		//  > ������ Update ���� ��� �� Draw
		/// - ���� : ��ǥ�� �̻��ϰų� �̻��ϰ� �׷���
		Hero_Update();
		Hero_Draw();

		Bullet_Update();
		Bullet_Draw();

		Flip(); // �������� �ε巴�� ���� (������۸�)
		EngineSync(30); // ������ ���� (�ܼ��� 30 �������� ���� �ε巯��)
	}

	ReleaseConsole(); // �ܼ� ����
	return 0;
}
