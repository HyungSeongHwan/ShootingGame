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


stGameMgr g_GameMgr;

int main()
{
	InitialConsole();//�ܼ� �ʱ�ȭ �Լ�

	srand(time(NULL));

	GameMgr_Init();

	SetWindowTitle("Shooting"); // ������ Ÿ��Ʋ �̸� ����
	while (true) // ���۽� ���ѷ���
	{
		CheckInput(); // ���� Ű�� �������� üũ�Ѵ�
		ClearScreenEx3(BLACK); // ����ȭ�� �� ����(���� : ������)

		//  > ������ Update ���� ��� �� Draw
		/// - ���� : ��ǥ�� �̻��ϰų� �̻��ϰ� �׷���
		GameMgr_Update();
		GameMgr_Draw();

		Flip(); // �������� �ε巴�� ���� (������۸�)
		EngineSync(30); // ������ ���� (�ܼ��� 30 �������� ���� �ε巯��)
	}

	ReleaseConsole(); // �ܼ� ����
	return 0;
}
