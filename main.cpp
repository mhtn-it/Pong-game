#include "gameMaster.h"

int main()
{
	resizeConsole(800, 700);
	gameMaster gm(25, 4, 64, 30);	//width chia het cho 8
	gm.launchGame();
	return 0;
	//gameMaster gm(25, 4, 64, 30);
	//gm.loadGame();
	//listItem _item; item x; x.setX(3);
	//_item.pushI(x); cout << _item.getI(0).getX();
}