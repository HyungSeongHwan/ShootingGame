#include "Include.h"
#include "Define.h"

//���� Ȱ��

int main(void)
{
	bool					nLoop = true;

	/*short					HeroX = 39;
	int						HeroX = 39;
	long					HeroX = 39;

	float					HeroX = 39;
	double					HeroX = 39;*/

	int						heor[25] = {65,67,68,69,80};
	char					HeroX = 39;
	char					HeroY = 22;
	char					HeroC = 'A'

	//	Memory ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//	Console �ʱ�ȭ ����
	//		ȭ�� ũ��	����: 0~79
	//					����: 0~24
	//		��ũ�� ����
	//		������Ʈ Ŀ�� ����
	//		���콺 Ŀ�� ����
	InitialConsole();
	//	Console â�� ������ ����
	SetWindowTitle("A ���� Hero - Part 01");
	//	Console ��� ����
	//		0 = ����
	//		1 = �ѱ�
	ChangeCodePage(FALSE);

	while(nLoop)
	{
		/*	Console Ű���� �Է��� �ǽð����� �˻��ϱ� ����
			���� �ݺ��ϸ鼭 �˻��Ѵ�								*/
		CheckInput();
		/*	Console ���� �ִ� ������ ������ ������ ������
			������													*/
		ClearScreenEx3(BLUE);

//	����� ���� ���α׷� ����� ����
#if defined(DEBUG) | defined(_DEBUG)
		//	Esc Ű�� ���ȴٸ�
		if(IsKey(VK_ESCAPE))
		{
			//	�ݺ������� ���´�
			break;
		}
#endif




		//	����� ���� ����
		/*	Console ���� �ִ� ������ �� ���ڸ� �׸���			*/
		if(IsKey(VK_UP))
			DrawCharEx3(39, 21, 'A', BLUE, WHITE);
		else if(IsKey(VK_DOWN))
			DrawCharEx3(39, 23, 'A', BLUE, WHITE);
		else
			DrawCharEx3(39, 22, 'a'-' ', WHITE, BLUE);

		//DrawStrEx3(0, 0, (char*)heor, WHITE, BLUE);
		/*if(IsKey(VK_UP))
			HeroY--;
		if(IsKey(VK_DOWN))
			HeroY++;

		DrawCharEx3(HeroX, HeroY, HeroC, WHITE, BLUE);*/




		/*	Console ���� ������ �׷��� ������ �������� ������
			��ü�Ͽ��ش�											*/
		Flip();
		/*	Console �� ���� �ݺ��� �ǽ��ϴ� �ð��� �����Ѵ�	*/
		EngineSync(32);
	}

	/*	Console ������ �����Ѵ�.									*/
	ReleaseConsole();
	//	��ȯ type int
	return 0;
}