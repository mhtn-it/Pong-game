#pragma once
#include "Header.h"
#include "ball.h"
#include "slider.h"
#include "listItem.h"
#include "bonusItem.h"
enum option { OPTION1, OPTION2, OPTION3, OPTION4 };

//Đối tượng quản lí trò chơi
class gameMaster
{
private:
	int _x, _y;
	int _width, _height;
	int _score;
	ball* _ball;
	slider* _slider;
	bool _quitGame;
	int _speed;
	listItem *_item;
	bonusItem* _bonus;
public:
	gameMaster();
	//Khởi tạo gameMaster
	gameMaster(int x, int y, int width, int height);
	//Xóa gameMaster
	~gameMaster();
	//Đưa trái bóng và thanh về vị trí ban đầu
	void reset();
	//Tăng điểm
	void scoreUp();
	//Vẽ ra màn hình
	void display();
	void controlEveryThing();
	//Hàm xử lí, logic
	void handle();
	//Hàm xử lí chơi với bot
	void handleWithBot();
	//Hàm xử lí thắng thua
	void gameOver();
	//Ham kiem tra xem cham vat pham chua
	bool checkItem();
	int checkBonus();
	//Ngau nhien xuat hien vat pham bonus
	void randomBonus();
	//Xu ly va cham voi bonus
	void handleBonus();
	void launchGame();
	void pauseGame();
	void saveGame();	//chua lam
};