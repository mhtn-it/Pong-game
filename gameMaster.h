#pragma once
#include "Header.h"
#include "ball.h"
#include "slider.h"
enum option { OPTION1, OPTION2, OPTION3, OPTION4 };

//Đối tượng quản lí trò chơi
class gameMaster
{
private:
	int _x, _y;
	int _width, _height;
	int _score1, _score2;
	ball * _ball;
	slider * _slider1;
	slider * _slider2;
	bool _quitGame;
	int _speed;
public:
	gameMaster();
	//Khởi tạo gameMaster
	gameMaster(int x, int y, int width, int height);
	//Xóa gameMaster
	~gameMaster();
	//Đưa trái bóng và thanh về vị trí ban đầu
	void reset();
	//Tăng điểm
	void scoreUp(slider * mslider);
	//Vẽ ra màn hình
	void display();
	void controlEveryThing();
	//Hàm xử lí, logic
	void handle();
	//Hàm in khi chơi với bot
	void displayWithBot();
	//Hàm điều khiển chơi với máy
	void controlWithBot();
	//Hàm xử lí chơi với bot
	void handleWithBot();
	//Hàm xử lí thắng thua
	void gameOver();
	void launchGame();
};