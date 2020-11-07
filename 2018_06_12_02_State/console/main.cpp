#include "Include.h"

// 헝가리안 표기법
// int    n이름
// char   c이름
// bool   b이름	
// DWORD  dw이름
// short  s이름
// long   l이름
// 구조체 맴버변수는 
// int m_n이름
// char  m_c이름
// 글로벌 g_?이름
// int nVlaue = 0;
// void Quit();


stHero g_Hero;

int main()
{
	InitialConsole();//초기화함수
	Hero_Init();

	SetWindowTitle("Shooting"); // 윈도우 타이틀 이름 설정
	while (true) // 시작시 무한루프
	{
		CheckInput(); // 무슨 키를 눌렀는지 체크한다
		ClearScreenEx3(BLACK); // 바탕화면 색 설정(현재 : 검은색)

		//  > 무조껀 Update 먼저 출력 후 Draw
		/// - 이유 : 좌표가 이상하거나 이상하게 그려짐
		Hero_Update();
		Hero_Draw();

		Bullet_Update();
		Bullet_Draw();

		Flip(); // 움직임을 부드럽게 해줌 (더블버퍼링)
		EngineSync(30); // 프레임 설정 (콘솔은 30 프레임이 가장 부드러움)
	}

	ReleaseConsole(); // 콘솔 종료
	return 0;
}
