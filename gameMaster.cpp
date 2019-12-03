#include "gameMaster.h"



gameMaster::gameMaster()
{
	return;
}


gameMaster::~gameMaster()
{
	delete[] _ball;
	delete[] _slider1;
	delete[] _slider2;
}

gameMaster::gameMaster(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_score1 = _score2 = 0;
	_slider1 = new slider(x + (width / 2), y + 1);
	_slider2 = new slider(x + (width / 2), y + height - 1);
	_ball = new ball(x + (width / 2), y + (height / 2));
	_quitGame = 0;
	_speed = 0;
}

void gameMaster::reset()
{
	_ball->reset();
	_slider1->reset();
	_slider2->reset();
}

void gameMaster::scoreUp(slider * mslider)
{
	//Xóa thanh cũ
	for (int i = 0; i <= 15; i++) {
		gotoxy(_slider1->getX() + i, _slider1->getY());
		cout << " ";
		gotoxy(_slider2->getX() + i, _slider2->getY());
		cout << " ";
	}
	if (mslider == _slider1) {
		_speed = 0;
		_score1++;
	}
	else if (mslider == _slider2) {
		_speed = 0;
		_score2++;
	}
	reset();
	display();
	_getch();
	_ball->randomDirection();
}

void gameMaster::display()
{
	//Tô đen vị trí trước đó của trái banh
	gotoxy(_ball->getPreX(), _ball->getPreY());
	cout << " ";
	//Vẽ 2 thanh
	for (int i = 0; i <= 15; i++) {
		gotoxy(_slider1->getX() + i, _slider1->getY());
		cout << "\xCD";
		gotoxy(_slider2->getX() + i, _slider2->getY());
		cout << "\xCD";
	}
	if (_ball->getY() == _y || _ball->getY() == _y + _height) {
		return;
	}
	//Vẽ điểm
	gotoxy(_x + _width + 2, _y);
	cout << "Player 1: " << _score1;
	gotoxy(_x + _width + 2, _y + _height);
	cout << "Player 2: " << _score2;
	//Vẽ trái banh
	textcolor(rand() % 15 + 1);
	gotoxy(_ball->getX(), _ball->getY());
	cout << "\x4F";
	textcolor(7);
}

void gameMaster::controlEveryThing()
{
	char a;
	if (_kbhit()) {
		a = _getch();
		if ((a == 'a' || a == 'A') && _slider1->getX() >= _x + 4) {
			for (int i = 12; i <= 15; i++) {
				gotoxy(_slider1->getX() + i, _slider1->getY());
				cout << " ";
			}
			_slider1->moveLeft();
		}
		else if ((a == 'd' || a == 'D') && _slider1->getX() <= _x + _width - 20) {
			for (int i = 0; i <= 3; i++) {
				gotoxy(_slider1->getX() + i, _slider1->getY());
				cout << " ";
			}
			_slider1->moveRight();
		}
		else if (a == 75 && _slider2->getX() >= _x + 4) {
			for (int i = 12; i <= 15; i++) {
				gotoxy(_slider2->getX() + i, _slider2->getY());
				cout << " ";
			}
			_slider2->moveLeft();
		}
		else if (a == 77 && _slider2->getX() <= _x + _width - 20) {
			for (int i = 0; i <= 3; i++) {
				gotoxy(_slider2->getX() + i, _slider2->getY());
				cout << " ";
			}
			_slider2->moveRight();
		}
	}
}

void gameMaster::handle()
{
	//Cộng điểm
	if (_ball->getY() == _y) {
		scoreUp(_slider2);
	}
	else if (_ball->getY() == _y + _height) {
		scoreUp(_slider1);
	}
	//Bóng chạm thanh 1
	if (_slider1->getX() <= _ball->getX() && _ball->getX() <= _slider1->getX() + 15 && _ball->getY() == _y + 2) {
		_ball->setDirecton((ballDirection)(rand() % 3 + 4));
		//Tăng tốc cho trái banh
		if (_speed <= 105) _speed += 15;
	}
	//Bóng chạm thanh 2
	else if (_slider2->getX() <= _ball->getX() && _ball->getX() <= _slider2->getX() + 15 && _ball->getY() == _y + _height - 2) {
		_ball->setDirecton((ballDirection)(rand() % 3 + 1));
		//Tăng tốc cho trái banh
		if (_speed <= 105) _speed += 15;
	}
	//Bóng chạm biên trái
	if (_ball->getX() == _x + 1 && _ball->getY() != _y && _ball->getY() != _y + _height) {
		if (_ball->getDirection() == UPLEFT) {
			_ball->setDirecton(UPRIGHT);
			//Tăng tốc cho trái banh
			if (_speed <= 105) _speed += 15;
		}
		else if (_ball->getDirection() == DOWNLEFT) {
			_ball->setDirecton(DOWNRIGHT);
			//Tăng tốc cho trái banh
			if (_speed <= 105) _speed += 15;
		}
	}
	//Bóng chạm biên phải
	else if (_ball->getX() == _x + _width - 1 && _ball->getY() != _y && _ball->getY() != _y + _height) {
		if (_ball->getDirection() == UPRIGHT) {
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWNRIGHT) {
			_ball->setDirecton(DOWNLEFT);
		}
	}
	_ball->setPreX(_ball->getX());
	_ball->setPreY(_ball->getY());
	_ball->move();
}

void gameMaster::displayWithBot()
{
	//Tô đen vị trí trước đó của trái banh
	gotoxy(_ball->getPreX(), _ball->getPreY());
	cout << " ";
	//Vẽ 2 thanh
	textcolor(3);
	for (int i = 0; i <= 15; i++) {
		gotoxy(_slider1->getX() + i, _slider1->getY());
		cout << "\xCD";
		gotoxy(_slider2->getX() + i, _slider2->getY());
		cout << "\xCD";
	}
	textcolor(7);
	for (int i = 0; i <= 15; i++) {
		gotoxy(_slider2->getX() + i, _slider2->getY());
		cout << "\xCD";
	}
	if (_ball->getY() == _y || _ball->getY() == _y + _height) {
		return;
	}
	//Vẽ điểm
	gotoxy(_x + _width + 2, _y);
	cout << "Player 1: " << _score1;
	gotoxy(_x + _width + 2, _y + _height);
	cout << "Player 2: " << _score2;
	//Vẽ trái banh
	textcolor(rand() % 15 + 1);
	gotoxy(_ball->getX(), _ball->getY());
	cout << "\x4F";
	textcolor(7);
}

void gameMaster::controlWithBot()
{
	char a;
	if (_kbhit()) {
		a = _getch();
		if (a == 75 && _slider2->getX() >= _x + 4) {
			for (int i = 12; i <= 15; i++) {
				gotoxy(_slider2->getX() + i, _slider2->getY());
				cout << " ";
			}
			_slider2->moveLeft();
		}
		else if (a == 77 && _slider2->getX() <= _x + _width - 20) {
			for (int i = 0; i <= 3; i++) {
				gotoxy(_slider2->getX() + i, _slider2->getY());
				cout << " ";
			}
			_slider2->moveRight();
		}
	}
}

void gameMaster::handleWithBot()
{
	if (_ball->getX() < _slider1->getX() && _slider1->getX() >= _x + 4) {
		for (int i = 12; i <= 15; i++) {
			gotoxy(_slider1->getX() + i, _slider1->getY());
			cout << " ";
		}
		_slider1->moveLeft();
	}
	else if (_ball->getX() > _slider1->getX() + 15 && _slider1->getX() <= _x + _width + 20) {
		for (int i = 0; i <= 3; i++) {
			gotoxy(_slider1->getX() + i, _slider1->getY());
			cout << " ";
		}
		_slider1->moveRight();
	}
	//Cộng điểm
	if (_ball->getY() == _y) {
		scoreUp(_slider2);
	}
	else if (_ball->getY() == _y + _height) {
		scoreUp(_slider1);
	}
	//Bóng chạm thanh 1
	if (_slider1->getX() <= _ball->getX() && _ball->getX() <= _slider1->getX() + 15 && _ball->getY() == _y + 2) {
		_ball->setDirecton((ballDirection)(rand() % 3 + 4));
		//Tăng tốc cho trái banh
		if (_speed <= 105) _speed += 15;
	}
	//Bóng chạm thanh 2
	else if (_slider2->getX() <= _ball->getX() && _ball->getX() <= _slider2->getX() + 15 && _ball->getY() == _y + _height - 2) {
		_ball->setDirecton((ballDirection)(rand() % 3 + 1));
		//Tăng tốc cho trái banh
		if (_speed <= 105) _speed += 15;
	}
	//Bóng chạm biên trái
	if (_ball->getX() == _x + 1 && _ball->getY() != _y && _ball->getY() != _y + _height) {
		if (_ball->getDirection() == UPLEFT) {
			_ball->setDirecton(UPRIGHT);
			//Tăng tốc cho trái banh
			if (_speed <= 105) _speed += 15;
		}
		else if (_ball->getDirection() == DOWNLEFT) {
			_ball->setDirecton(DOWNRIGHT);
			//Tăng tốc cho trái banh
			if (_speed <= 105) _speed += 15;
		}
	}
	//Bóng chạm biên phải
	else if (_ball->getX() == _x + _width - 1 && _ball->getY() != _y && _ball->getY() != _y + _height) {
		if (_ball->getDirection() == UPRIGHT) {
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWNRIGHT) {
			_ball->setDirecton(DOWNLEFT);
		}
	}
	_ball->setPreX(_ball->getX());
	_ball->setPreY(_ball->getY());
	_ball->move();
}

void gameMaster::gameOver()
{
	if (_score1 == 3 || _score2 == 3) {
		if (_score1 == 3) {
			textcolor(9);  gotoxy(_x + 2, _y + 4); cout << "        .__                                    ____            .__          ";
			textcolor(10); gotoxy(_x + 2, _y + 5); cout << "______  |  |  _____    ___.__.  ____  _______ /_   |  __  _  __|__|  ____   ";
			textcolor(11); gotoxy(_x + 2, _y + 6); cout << "\\____ \\ |  |  \\__  \\  <   |  |_/ __ \\ \\_  __ \\ |   |  \\ \\/ \\/ /|  | /    \\  ";
			textcolor(12); gotoxy(_x + 2, _y + 7); cout << "|  |_> >|  |__ / __ \\_ \\___  |\\  ___/  |  | \\/ |   |   \\     / |  ||   |  \\ ";
			textcolor(13); gotoxy(_x + 2, _y + 8); cout << "|   __/ |____/(____  / / ____| \\___  > |__|    |___|    \\/\\_/  |__||___|  / ";
			textcolor(14); gotoxy(_x + 2, _y + 9); cout << "|__|               \\/  \\/          \\/                                   \\/  ";
			_getch();
			gotoxy(_x + 2, _y + 4); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 5); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 6); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 7); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 8); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 9); cout << "                                                                             ";
		}
		else if (_score2 == 3) {
			textcolor(14);  gotoxy(_x + 2, _y + 4); cout << "        .__                                   ________           .__          ";
			textcolor(13); gotoxy(_x + 2, _y + 5); cout << "______  |  |  _____    ___.__.  ____  _______ \\_____  \\ __  _  __|__|  ____   ";
			textcolor(12); gotoxy(_x + 2, _y + 6); cout << "\\____ \\ |  |  \\__  \\  <   |  |_/ __ \\ \\_  __ \\ /  ____/ \\ \\/ \\/ /|  | /    \\  ";
			textcolor(11); gotoxy(_x + 2, _y + 7); cout << "|  |_> >|  |__ / __ \\_ \\___  |\\  ___/  |  | \\//       \\  \\     / |  ||   |  \\ ";
			textcolor(10); gotoxy(_x + 2, _y + 8); cout << "|   __/ |____/(____  / / ____| \\___  > |__|   \\_______ \\  \\/\\_/  |__||___|  / ";
			textcolor(9); gotoxy(_x + 2, _y + 9); cout << "|__|               \\/  \\/          \\/                 \\/                  \\/  ";
			_getch();
			gotoxy(_x + 2, _y + 4); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 5); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 6); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 7); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 8); cout << "                                                                             ";
			gotoxy(_x + 2, _y + 9); cout << "                                                                             ";
		}
		gotoxy(_ball->getX(), _ball->getY()); cout << " ";
		reset();
		_speed = 0;
		_score1 = 0;
		_score2 = 0;

		_quitGame = true;
	}
}

void gameMaster::launchGame()
{
	//Xóa biểu tượng con trỏ
	Nocursortype();
	//Tạo ra một biến ngẫu nhiên
	srand(time(NULL));
	//Vẽ khung trò chơi
	drawRectangle1(_x - 20, _y, _height, _width + 20, 7);
	drawRectangle1(_x - 1, _y, _height, _width + 1, 7);
	textcolor(6);
	gotoxy(_x - 14, _y + 3);
	cout << "New Game";
	textcolor(4);
	gotoxy(_x - 16, _y + 7);
	cout << "Play with BOT";
	gotoxy(_x - 15, _y + 11);
	cout << "How to play";
	gotoxy(_x - 14, _y + 15);
	cout << "Quit Game";
	option _option = OPTION1;
	char a = 'a';
	do {
		//Nhận biết khi phát hiện có phím được bấm
		if (_kbhit()) {
			//Lưu giá trị của phím vừa bấm
			a = _getch();
			//Nếu phát hiện có dấu mũi tên xuống
			if (a == 80) {
				if (_option == OPTION1) _option = OPTION2;
				else if (_option == OPTION2) _option = OPTION3;
				else if (_option == OPTION3) _option = OPTION4;
				else if (_option == OPTION4) _option = OPTION1;

				if (_option == OPTION2) {
					textcolor(6);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
					textcolor(4);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
				}
				else if (_option == OPTION3) {
					textcolor(6);
					gotoxy(_x - 15, _y + 11);
					cout << "How to play";
					textcolor(4);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
				}
				else if (_option == OPTION4) {
					textcolor(6);
					gotoxy(_x - 14, _y + 15);
					cout << "Quit Game";
					textcolor(4);
					gotoxy(_x - 15, _y + 11);
					cout << "How to play";
				}
				else if (_option == OPTION1) {
					textcolor(6);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
					textcolor(4);
					gotoxy(_x - 14, _y + 15);
					cout << "Quit Game";
				}
			}
			//Nếu phát hiện có múi tên lên
			else if (a == 72) {
				if (_option == OPTION1) _option = OPTION4;
				else if (_option == OPTION2) _option = OPTION1;
				else if (_option == OPTION3) _option = OPTION2;
				else if (_option == OPTION4) _option = OPTION3;

				if (_option == OPTION1) {
					textcolor(6);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
					textcolor(4);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
				}
				else if (_option == OPTION2) {
					textcolor(6);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
					textcolor(4);
					gotoxy(_x - 15, _y + 11);
					cout << "How to play";
				}
				else if (_option == OPTION3) {
					textcolor(6);
					gotoxy(_x - 15, _y + 11);
					cout << "How to play";
					textcolor(4);
					gotoxy(_x - 14, _y + 15);
					cout << "Quit Game";
				}
				else if (_option == OPTION4) {
					textcolor(6);
					gotoxy(_x - 14, _y + 15);
					cout << "Quit Game";
					textcolor(4);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
				}
			}
			//Nếu phát hiện có bấm phím ENTER
			if (a == 13) {
				switch (_option) {
					//New game
				case OPTION1: {
					textcolor(7);
					_ball->randomDirection();
					//Trò chơi kết thúc khi thuộc tính quitGame == true
					while (_quitGame != true) {
						//Chế độ chơi thường 
						controlEveryThing();
						handle();
						display();
						gameOver();
						Sleep(170 - _speed);
					}
					textcolor(7);
					_quitGame = false;
					break;
				}
				case OPTION2: {
					textcolor(7);
					_ball->randomDirection();
					//Trò chơi kết thúc khi thuộc tính quitGame == true
					while (_quitGame != true) {
						//Chế độ chơi với máy
						controlWithBot();
						handleWithBot();
						displayWithBot();
						gameOver();
						Sleep(170 - _speed);
					}
					textcolor(7);
					_quitGame = false;
					break;
				}
							  //How to play
				case OPTION3: {
					textcolor(2);
					gotoxy(_x + (_width / 8), _y + (_height / 8));
					cout << "There is two player. Player1 will use press";
					gotoxy(_x + (_width / 8), _y + (_height / 8) + 1);
					cout << "'A' to move left and 'D' to move Right the";
					gotoxy(_x + (_width / 8), _y + (_height / 8) + 2);
					cout << "same to Player2 who use '<-' and '->' instead";
					_getch();
					gotoxy(_x + (_width / 8), _y + (_height / 8));
					cout << "                                           ";
					gotoxy(_x + (_width / 8), _y + (_height / 8) + 1);
					cout << "                                          ";
					gotoxy(_x + (_width / 8), _y + (_height / 8) + 2);
					cout << "                                             ";
				}
							  break;
				case OPTION4: {
					break;
				}
				}
				if (_option == OPTION4) break;
			}
		}
	} while (true);
}
