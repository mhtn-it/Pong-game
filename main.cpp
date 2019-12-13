#include "gameMaster.h"

int main()
{
	resizeConsole(800, 700);
	gameMaster gm(25, 4, 64, 30);	//width chia het cho 8
	gm.launchGame();
	return 0;
	/*cout << "o";
	Sleep(50);
	gotoxy(0, 1); cout << "o";*/
}