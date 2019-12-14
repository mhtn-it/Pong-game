#include "gameMaster.h"

gameMaster::gameMaster()
{
	return;
}
gameMaster::~gameMaster()
{
	delete[] _ball;
	delete[] _slider;
}
gameMaster::gameMaster(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_score = 0;
	_slider = new slider(x + (width / 2) - width / 8, y + height - 1);
	_slider->setSize(width / 4);
	_ball = new ball(x + (width / 2), y + (height / 2));
	_item = new listItem(x, y, width, height);
	_bonus = new bonusItem(x, y, width, height);
	_quitGame = 0;
	_speed = 0;
}
void gameMaster::reset()
{
	_ball->reset();
	_slider->reset();
	_slider->setSize(_width / 4);
	_item->reset();
	_bonus->reset();
}
void gameMaster::scoreUp()
{
	if (checkItem())
	{
		_score++;
		randomBonus();
	}
}
void gameMaster::display()
{
	////Tô đen vị trí trước đó của trái banh
	gotoxy(_ball->getPreX(), _ball->getPreY());
	cout << " ";
	//Xóa thanh cũ
	for (int i = 0; i < _slider->getSize(); i++)
	{
		gotoxy(_slider->getX() + i, _slider->getY());
		cout << " ";
	}
	//Kiem tra ket thuc game
	if (_ball->getY() >= _y + _height || _quitGame == true)
	{
		return;
	}
	//Vẽ thanh
	for (int i = 0; i < _slider->getSize(); i++)
	{
		gotoxy(_slider->getX() + i, _slider->getY());
		cout << "\xCD";
	}
	//Vẽ điểm
	gotoxy(_x + _width / 2 - 10, _y + _height + 1);
	cout << "Score: " << _score << "   ";
	//Vẽ trái banh
	textcolor(7);
	gotoxy(_ball->getX(), _ball->getY());
	cout << "\x4F";
}
void gameMaster::controlEveryThing()
{
	char a;
	//Nhận biết khi phát hiện có phím được bấm
	if (_kbhit())
	{
		a = _getch();
		if ((a == 75) && _slider->getX() >= _x + 4)
		{
			for (int i = _slider->getSize() - 4; i < _slider->getSize(); i++)
			{
				gotoxy(_slider->getX() + i, _slider->getY());
				cout << " ";
			}
			_slider->moveLeft();
		}
		else if ((a == 77) && _slider->getX() <= _x + _width - 20)
		{
			for (int i = 0; i <= 3; i++)
			{
				gotoxy(_slider->getX() + i, _slider->getY());
				cout << " ";
			}
			_slider->moveRight();
		}
	}
}
void gameMaster::handle()
{
	//Bóng chạm thanh
	if (_slider->getX() <= _ball->getX() && _ball->getX() < _slider->getX() + _slider->getSize() && _ball->getY() == _slider->getY() - 1)
	{
		if (_ball->getX() < _slider->getX() + _slider->getSize() / 4 || _ball->getX() > _slider->getX() + _slider->getSize() / 4 * 3)
			_ball->setVX(2);
		else if (_ball->getX() < _slider->getX() + _slider->getSize() / 2 - 1 || _ball->getX() > _slider->getX() + _slider->getSize() / 2)
			_ball->setVX(1);
		else
			_ball->setVX(0);
		_ball->setY(_slider->getY() - 1);
		if (_ball->getDirection() == DOWNRIGHT)
		{
			_ball->setDirecton(UPRIGHT);
		}
		else if (_ball->getDirection() == DOWNLEFT)
		{
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWN)
		{
			_ball->setDirecton(UP);
		}
		//Tăng tốc cho trái banh
		if (_speed <= 105)
			_speed += 15;
	}
	//Bóng chạm biên trái
	if (((_ball->getVX() == 1 && _ball->getX() <= _x) || (_ball->getVX() == 2 && _ball->getX() <= _x + 1)) && _ball->getY() >= _y && _ball->getY() <= _y + _height)
	{
		gotoxy(_ball->getX(), _ball->getY());
		cout << " ";
		_ball->setX(_x);
		gotoxy(_ball->getX(), _ball->getY()); cout << "O";
		if (_ball->getDirection() == UPLEFT)
		{
			_ball->setDirecton(UPRIGHT);
		}
		else if (_ball->getDirection() == DOWNLEFT)
		{
			_ball->setDirecton(DOWNRIGHT);
		}
	}
	//Bóng chạm biên phải
	else if (((_ball->getVX() == 1 && _ball->getX() >= _x + _width - 1) || (_ball->getVX() == 2 && _ball->getX() >= _x + _width - 2)) && _ball->getY() >= _y && _ball->getY() <= _y + _height)
	{
		gotoxy(_ball->getX(), _ball->getY());
		cout << " ";
		_ball->setX(_x + _width - 1);
		gotoxy(_ball->getX(), _ball->getY()); cout << "O";
		if (_ball->getDirection() == UPRIGHT)
		{
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWNRIGHT)
		{
			_ball->setDirecton(DOWNLEFT);
		}
	}
	//Bong cham bien tren
	if (_ball->getY() <= _y + 1)
	{
		_ball->setY(_y + 1);
		if (_ball->getDirection() == UPRIGHT)
		{
			_ball->setDirecton(DOWNRIGHT);
		}
		else if (_ball->getDirection() == UPLEFT)
		{
			_ball->setDirecton(DOWNLEFT);
		}
		else if (_ball->getDirection() == UP)
		{
			_ball->setDirecton(DOWN);
		}
	}
	//Cong diem
	scoreUp();
	handleBonus();
	_ball->setPreX(_ball->getX());
	_ball->setPreY(_ball->getY());
	_ball->move();
}
void gameMaster::handleWithBot()
{
	if (_ball->getX() < _slider->getX() && _slider->getX() >= _x + 4)
	{
		for (int i = _slider->getSize() - 4; i < _slider->getSize(); i++)
		{
			gotoxy(_slider->getX() + i, _slider->getY());
			cout << " ";
		}
		_slider->moveLeft();
	}
	else if (_ball->getX() > _slider->getX() + _slider->getSize() - 1 && _slider->getX() <= _x + _width + 20)
	{
		for (int i = 0; i <= 3; i++)
		{
			gotoxy(_slider->getX() + i, _slider->getY());
			cout << " ";
		}
		_slider->moveRight();
	}
	//Bóng chạm thanh
	if (_slider->getX() <= _ball->getX() && _ball->getX() < _slider->getX() + _slider->getSize() && _ball->getY() == _slider->getY() - 1)
	{
		if (_ball->getX() < _slider->getX() + _slider->getSize() / 4 || _ball->getX() > _slider->getX() + _slider->getSize() / 4 * 3)
			_ball->setVX(2);
		else if (_ball->getX() < _slider->getX() + _slider->getSize() - 1 || _ball->getX() > _slider->getX() + _slider->getSize())
			_ball->setVX(1);
		else
			_ball->setVX(0);
		_ball->setY(_slider->getY() - 1);
		if (_ball->getDirection() == DOWNRIGHT)
		{
			_ball->setDirecton(UPRIGHT);
		}
		else if (_ball->getDirection() == DOWNLEFT)
		{
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWN)
		{
			_ball->setDirecton(UP);
		}
		//Tăng tốc cho trái banh
		if (_speed <= 105)
			_speed += 15;
	}
	//Bóng chạm biên trái
	if (((_ball->getVX() == 1 && _ball->getX() <= _x) || (_ball->getVX() == 2 && _ball->getX() <= _x + 1)) && _ball->getY() >= _y && _ball->getY() <= _y + _height)
	{
		gotoxy(_ball->getX(), _ball->getY());
		cout << " ";
		_ball->setX(_x);
		gotoxy(_ball->getX(), _ball->getY()); cout << "O";
		if (_ball->getDirection() == UPLEFT)
		{
			_ball->setDirecton(UPRIGHT);
		}
		else if (_ball->getDirection() == DOWNLEFT)
		{
			_ball->setDirecton(DOWNRIGHT);
		}
	}
	//Bóng chạm biên phải
	else if (((_ball->getVX() == 1 && _ball->getX() >= _x + _width - 1) || (_ball->getVX() == 2 && _ball->getX() >= _x + _width - 2)) && _ball->getY() >= _y && _ball->getY() <= _y + _height)
	{
		gotoxy(_ball->getX(), _ball->getY());
		cout << " ";
		_ball->setX(_x + _width - 1);
		gotoxy(_ball->getX(), _ball->getY()); cout << "O";
		if (_ball->getDirection() == UPRIGHT)
		{
			_ball->setDirecton(UPLEFT);
		}
		else if (_ball->getDirection() == DOWNRIGHT)
		{
			_ball->setDirecton(DOWNLEFT);
		}
	}
	//Bong cham bien tren
	if (_ball->getY() <= _y + 1)
	{
		_ball->setY(_y + 1);
		if (_ball->getDirection() == UPRIGHT)
		{
			_ball->setDirecton(DOWNRIGHT);
		}
		else if (_ball->getDirection() == UPLEFT)
		{
			_ball->setDirecton(DOWNLEFT);
		}
		else if (_ball->getDirection() == UP)
		{
			_ball->setDirecton(DOWN);
		}
	}
	//Cong diem
	scoreUp();
	handleBonus();
	_ball->setPreX(_ball->getX());
	_ball->setPreY(_ball->getY());
	_ball->move();
}
void gameMaster::gameOver()
{
	if (_ball->getY() >= _y + _height || _quitGame == true)
	{
		//dung man hinh truoc khi reset game
		//_getch();
		addHallofFame();
		reset();
		_speed = 0;
		_score = 0;
		_quitGame = true;
		display();
	}
	if (_item->getN() == 0)
	{
		gotoxy(40, 18); cout << "YOU WIN!";
		_getch();
		gotoxy(40, 18); cout << "			";
		reset();
		_speed = 0;
		_score = 0;
		_quitGame = true;
		display();
	}
}
bool gameMaster::checkItem()
{
	item temp;
	for (int i = 0; i < _item->getN(); i++)
	{
		temp = _item->getI(i);
		if (!temp.getDelete())
		{
			if (_ball->getNextY() == temp.getY() && _ball->getNextY() == temp.getY() && _ball->getNextX() >= temp.getX() && _ball->getNextX() <= temp.getX() + temp.getSize() - 2)
			{
				_item->deleteItem(i);
				temp.setDelete(true);
				temp.draw();
				return true;
			}
		}
	}
	return false;
}
int gameMaster::checkBonus()
{
	item temp;
	for (int i = 0; i < _bonus->getN(); i++)
	{
		temp = _bonus->getI(i);
		if (!temp.getDelete())
		{
			if (_ball->getNextY() == temp.getY() && _ball->getNextY() == temp.getY() && _ball->getNextX() >= temp.getX() && _ball->getNextX() <= temp.getX() + temp.getSize() - 2)
			{
				_bonus->deleteItem(i);
				temp.setDelete(true);
				temp.draw();
				return int(temp.getSpe());
			}
		}
	}
	return -1;
}
void gameMaster::randomBonus()
{
	if (_score % 5 == 0)
	{
		item newItem;
		newItem.set(_x + 2 + rand() % (_width - 10), _y + 5 + _score / 5);
		newItem.setSpe(rand() % 6 + 1);
		newItem.draw();
		_bonus->pushBack(newItem);
	}
}
void gameMaster::handleBonus()
{
	int check = checkBonus();
	if (check == -1)
		return;
	switch (check)
	{
	case 1:
		_score += 5;
		break;
	case 2:
		if (_score >= 5)
			_score -= 5;
		else
			_score = 0;
		break;
	case 3:
		_score *= 2;
		break;
	case 4:
		_score = int(_score / 2);
		break;
	case 5:
		if (_slider->getSize() == 16)
			_slider->setSize(8);
		break;
	case 6:
		if (_slider->getSize() == 8)
			_slider->setSize(16);
		break;
	default:
		break;
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
	gotoxy(_x - 16, _y + 5);
	cout << "Continue Game";
	gotoxy(_x - 16, _y + 7);
	cout << "Play with BOT";
	gotoxy(_x - 15, _y + 9);
	cout << "How to play";
	gotoxy(_x - 16, _y + 11);
	cout << "Hall of Fame";
	gotoxy(_x - 14, _y + 13);
	cout << "Quit Game";
	option _option = OPTION1;
	char a = 'a';
	do {
		//Nhận biết khi phát hiện có phím được bấm
		if (_kbhit())
		{
			//Lưu giá trị của phím vừa bấm
			a = _getch();
			//Nếu phát hiện có dấu mũi tên xuống
			if (a == 80)
			{
				if (_option == OPTION1) _option = OPTION2;
				else if (_option == OPTION2) _option = OPTION3;
				else if (_option == OPTION3) _option = OPTION4;
				else if (_option == OPTION4) _option = OPTION5;
				else if (_option == OPTION5) _option = OPTION6;
				else if (_option == OPTION6) _option = OPTION1;

				if (_option == OPTION2)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 5);
					cout << "Continue Game";
					textcolor(4);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
				}
				else if (_option == OPTION3)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
					textcolor(4);
					gotoxy(_x - 16, _y + 5);
					cout << "Continue Game";
				}
				else if (_option == OPTION4)
				{
					textcolor(6);
					gotoxy(_x - 15, _y + 9);
					cout << "How to play";
					textcolor(4);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
				}
				else if (_option == OPTION5)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 11);
					cout << "Hall of Fame";
					textcolor(4);
					gotoxy(_x - 15, _y + 9);
					cout << "How to play";
				}
				else if (_option == OPTION6)
				{
					textcolor(6);
					gotoxy(_x - 14, _y + 13);
					cout << "Quit Game";
					textcolor(4);
					gotoxy(_x - 16, _y + 11);
					cout << "Hall of Fame";
				}
				else if (_option == OPTION1)
				{
					textcolor(6);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
					textcolor(4);
					gotoxy(_x - 14, _y + 13);
					cout << "Quit Game";
				}
			}
			//Nếu phát hiện có múi tên lên
			else if (a == 72)
			{
				if (_option == OPTION1) _option = OPTION6;
				else if (_option == OPTION2) _option = OPTION1;
				else if (_option == OPTION3) _option = OPTION2;
				else if (_option == OPTION4) _option = OPTION3;
				else if (_option == OPTION5) _option = OPTION4;
				else if (_option == OPTION6) _option = OPTION5;

				if (_option == OPTION1)
				{
					textcolor(6);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
					textcolor(4);
					gotoxy(_x - 16, _y + 5);
					cout << "Continue Game";
				}
				else if (_option == OPTION2)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 5);
					cout << "Continue Game";
					textcolor(4);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
				}
				else if (_option == OPTION3)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 7);
					cout << "Play with BOT";
					textcolor(4);
					gotoxy(_x - 15, _y + 9);
					cout << "How to play";
				}
				else if (_option == OPTION4)
				{
					textcolor(6);
					gotoxy(_x - 15, _y + 9);
					cout << "How to play";
					textcolor(4);
					gotoxy(_x - 16, _y + 11);
					cout << "Hall of Fame";
				}
				else if (_option == OPTION5)
				{
					textcolor(6);
					gotoxy(_x - 16, _y + 11);
					cout << "Hall of Fame";
					textcolor(4);
					gotoxy(_x - 14, _y + 13);
					cout << "Quit Game";
				}
				else if (_option == OPTION6)
				{
					textcolor(6);
					gotoxy(_x - 14, _y + 13);
					cout << "Quit Game";
					textcolor(4);
					gotoxy(_x - 14, _y + 3);
					cout << "New Game";
				}
			}
			//Nếu phát hiện có bấm phím ENTER
			bool isBot =true;
			if (a == 13)
			{
				switch (_option)
				{
					//New game
				case OPTION1:
				{
					clearScreen();
					textcolor(7);
					_ball->randomV();
					_ball->randomDirection();
					_item->drawItem();
					//Trò chơi kết thúc khi thuộc tính quitGame == true
					while (_quitGame != true)
					{
						//Chế độ chơi thường 
						pauseGame(isBot);
						controlEveryThing();
						handle();
						display();
						gameOver();
						Sleep(170 - _speed);	//Thay doi toc do
					}
					textcolor(7);
					_quitGame = false;
					break;
				}
				case OPTION2:
				{
					clearScreen();
					loadGame(isBot);
					_item->drawItem();
					while (_quitGame != true)
					{
						pauseGame(isBot);
						controlEveryThing();
						if (isBot == false)
							handle();
						else
							handleWithBot();
						display();
						gameOver();
						Sleep(170 - _speed);
					}
					textcolor(7);
					_quitGame = false;
					break;
				}
				case OPTION3:
				{
					clearScreen();
					textcolor(7);
					_ball->randomV();
					_ball->randomDirection();
					_item->drawItem();
					//Trò chơi kết thúc khi thuộc tính quitGame == true
					while (_quitGame != true)
					{
						//Chế độ chơi với máy
						isBot = true;
						pauseGame(isBot);
						controlEveryThing();
						handleWithBot();
						display();
						gameOver();
						Sleep(170 - _speed);
					}
					textcolor(7);
					_quitGame = false;
					break;
				}
				//How to play
				case OPTION4:
				{
					clearScreen();
					textcolor(2);
					gotoxy(_x + (_width / 8), _y + (_height / 8));
					cout << "Use '->' and '<-' to control";
					break;
				}
				case OPTION5:
				{
					clearScreen();
					HallofFame();
					break;
				}
				case OPTION6:
				{
					return;
					break;
				}
				default:
					break;
				}
			}
		}
	} while (true);
}

void gameMaster::pauseGame(bool isBot)
{
	char a;
	//Nhận biết khi phát hiện có phím được bấm
	if (_kbhit())
	{
		a = _getch();
		if (a == 'p')
		{
			textcolor(7); gotoxy(_x - 16, _y + 19); cout << "PAUSE GAME!!!";
			textcolor(4); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
			textcolor(7); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
			textcolor(7); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
			option _op = OPTION1;
			while (a != 80 || a != 72 || a != 13)
			{
				if (_kbhit())
				{
					//Lưu giá trị của phím vừa bấm
					a = _getch();
					//Nếu phát hiện có dấu mũi tên xuống
					if (a == 80)
					{
						if (_op == OPTION1) _op = OPTION2;
						else if (_op == OPTION2) _op = OPTION3;
						else if (_op == OPTION3) _op = OPTION1;
						if (_op == OPTION2)
						{
							textcolor(7); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(4); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(7); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
						else if (_op == OPTION1)
						{
							textcolor(4); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(7); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(7); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
						else if (_op == OPTION3)
						{
							textcolor(7); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(7); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(4); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
					}
					//Nếu phát hiện có múi tên lên
					else if (a == 72)
					{
						if (_op == OPTION1) _op = OPTION3;
						else if (_op == OPTION2) _op = OPTION1;
						else if (_op == OPTION3) _op = OPTION2;
						if (_op == OPTION2)
						{
							textcolor(7); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(4); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(7); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
						else if (_op == OPTION1)
						{
							textcolor(4); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(7); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(7); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
						else if (_op == OPTION3)
						{
							textcolor(7); gotoxy(_x - 16, _y + 21); cout << "1. Continue";
							textcolor(7); gotoxy(_x - 16, _y + 22); cout << "2. Save & Exit";
							textcolor(4); gotoxy(_x - 16, _y + 23); cout << "3. Exit";
						}
					}
					//Nếu phát hiện có bấm phím ENTER
					if (a == 13)
					{
						switch (_op)
						{
							//Continue
						case OPTION1:
						{
							textcolor(7);
							gotoxy(_x - 16, _y + 19); cout << "              ";
							gotoxy(_x - 25, _y + 21); cout << "	                ";
							gotoxy(_x - 25, _y + 22); cout << "	                ";
							gotoxy(_x - 25, _y + 23); cout << "	                ";
							return;
							break;
						}
						//SaveGame
						case OPTION2:
						{
							textcolor(7);
							gotoxy(_x - 16, _y + 19); cout << "              ";
							gotoxy(_x - 25, _y + 21); cout << "	                ";
							gotoxy(_x - 25, _y + 22); cout << "	                ";
							gotoxy(_x - 25, _y + 23); cout << "	                ";
							saveGame(isBot);
							_quitGame = true;
							return;
							break;
						}
						case OPTION3:
						{
							textcolor(7);
							gotoxy(_x - 16, _y + 19); cout << "              ";
							gotoxy(_x - 25, _y + 21); cout << "	                ";
							gotoxy(_x - 25, _y + 22); cout << "	                ";
							gotoxy(_x - 25, _y + 23); cout << "	                ";
							_quitGame = true;
							return;
							break;
						}
						default:
							break;
						}
					}
				}
			}
		}
	}
}
void gameMaster::addHallofFame()
{
	vector<int> point;
	int _point;
	fstream f;
	f.open("HallofFame.txt", ios::in);
	while (!f.eof())
	{
		f >> _point;
		point.push_back(_point);
		f << "\n";
	}
	for (int i = 0; i < point.size(); i++)
	{
		if (_score > point[i])
		{
			int j = i;
			int temp[10]; int m = 0;
			temp[m] = point[i];
			for (j; j < point.size() - 1; j++)
			{
				m++;
				temp[m] = point[j + 1];
				point[j + 1] = temp[m - 1];
			}
			point[i] = _score;
			break;
		}
	}
	f.close();
	f.open("HallofFame.txt", ios::out | ios::trunc);
	for (int i = 0; i < 10; i++)
	{
		f << point[i] << endl;
	}
	f.close();
}
void gameMaster::clearScreen()
{
	for (int i = 0; i < _height-1; i++)
		for (int j = 0; j < _width-1; j++)
		{
			gotoxy(_x + j + 1, _y + i + 1); cout << " ";
		}
}
void gameMaster::HallofFame()
{
	ifstream f;
	f.open("HallofFame.txt");
	int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
	f >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8 >> t9 >> t10;
	textcolor(9);
	gotoxy(_x + 25, _y + 3);
	cout << "HALL OF FAME";
	textcolor(14);
	gotoxy(_x + 26, _y + 7);
	cout << "Top 1: " << t1;
	gotoxy(_x + 26, _y + 9);
	cout << "Top 2: " << t2;
	gotoxy(_x + 26, _y + 11);
	cout << "Top 3: " << t3;
	gotoxy(_x + 26, _y + 13);
	cout << "Top 4: " << t4;
	gotoxy(_x + 26, _y + 15);
	cout << "Top 5: " << t5;
	gotoxy(_x + 26, _y + 17);
	cout << "Top 6: " << t6;
	gotoxy(_x + 26, _y + 19);
	cout << "Top 7: " << t7;
	gotoxy(_x + 26, _y + 21);
	cout << "Top 8: " << t8;
	gotoxy(_x + 26, _y + 23);
	cout << "Top 9: " << t9;
	gotoxy(_x + 26, _y + 25);
	cout << "Top 10: " << t10;
}
void gameMaster::saveGame(bool isBot)
{
	ofstream f;
	f.open("Save.txt", ios::trunc);
	f << isBot << endl;
	f << _x << endl << _y << endl;
	f << _width << endl << _height << endl;
	f << _score << endl;
	f << _ball->getOriginalX() << endl << _ball->getOriginalY() << endl << _ball->getX() << endl << _ball->getY() << endl << _ball->getPreX() << endl << _ball->getPreY() << endl << _ball->getVX() << endl << _ball->getVY() << endl << (int)_ball->getDirection() << endl;
	f << _slider->getX() << endl << _slider->getY() << endl << _slider->getOriginalX() << endl << _slider->getOriginalY() << endl << _slider->getSize() << endl;
	f << _speed << endl;
	f << _item->getN() << endl << _item->getOriX() << endl << _item->getOriY() << endl << _item->getOriW() << endl << _item->getOriH() << endl << _item->getOriN() << endl;
	//vector<item>::iterator it;
	for (int i = 0; i < _item->getN(); i++)
	{
		f << _item->getI(i).getX() << " " << _item->getI(i).getY() << " " << _item->getI(i).getSize() << " " << _item->getI(i).getDelete() << " " << _item->getI(i).getSpe() << ",";
	}
	f << _bonus->getN() << endl << _bonus->getOriX() << endl << _bonus->getOriY() << endl << _bonus->getOriW() << endl << _bonus->getOriH() << endl << _bonus->getOriN() << endl;
	for (int i = 0; i < _bonus->getN(); i++)
	{
		f << _bonus->getI(i).getX() << " " << _bonus->getI(i).getY() << " " << _bonus->getI(i).getSize() << " " << _bonus->getI(i).getDelete() << " " << _bonus->getI(i).getSpe() << ",";
	}
	f.close();
}
void gameMaster::loadGame(bool& isBot)
{
	ifstream f;
	f.open("Save.txt");
	listItem _list;
	f >> isBot;
	f >> _x >> _y;
	f >> _width >> _height;
	f >> _score;
	int bOx, bOy, bx, by, bPx, bPy, bvx, bvy, bD, sx, sy, sOx, sOy, ss, ln, lOx, lOy, lOw, lOh, lOn;
	f >> bOx >> bOy >> bx >> by >> bPx >> bPy >> bvx >> bvy >> bD;
	f >> sx >> sy >> sOx >> sOy >> ss;
	f >> _speed;
	f >> ln >> lOx >> lOy >> lOw >> lOh >> lOn;
	for (int i = 0; i < ln; i++)
	{
		int ix, iy, is, id, ispe; char phay;
		f >> ix >> iy >> is >> id >> ispe;
		f.get(phay);
		item x;
		x.setX(ix);
		x.setY(iy);
		x.setSize(is);
		x.setDelete(id);
		x.setSpe(ispe);
		_list.pushI(x); //cout << _item->getI(i).getDelete();
	}
	int bonusN, bonusX, bonusY, bonusW, bonusH, bonusOriN;
	f >> bonusN >> bonusX >> bonusY >> bonusW >> bonusH >> bonusOriN;
	bonusItem _listB;
	for (int i = 0; i < bonusN; i++)
	{
		int ix, iy, is, id, ispe; char phay;
		f >> ix >> iy >> is >> id >> ispe;
		f.get(phay);
		item x;
		x.setX(ix);
		x.setY(iy);
		x.setSize(is);
		x.setDelete(id);
		x.setSpe(ispe);
		_listB.pushBack(x); //cout << _item->getI(i).getDelete();
	}
	f.close();

	_ball->setOriginalX(bOx);
	_ball->setOriginalY(bOy);
	_ball->setX(bx);
	_ball->setY(by);
	_ball->setPreX(bPx); //cout << bPx;
	_ball->setPreY(bPy);
	_ball->setVX(bvx);
	_ball->setVY(bvy);
	_ball->setDirecton((ballDirection)bD);
	_slider->setX(sx);
	_slider->setY(sy);
	_slider->setOriginalX(sOx);
	_slider->setOriginalY(sOy);
	_slider->setSize(ss);
	_list.setN(ln);
	_list.setOriX(lOx);
	_list.setOriY(lOy);
	_list.setOriW(lOw);
	_list.setOriH(lOh);
	_list.setOriN(lOn);
	_item->set(_list);
	_listB.setN(bonusN);
	_listB.setOriX(bonusX);
	_listB.setOriY(bonusY);
	_listB.setOriW(bonusW);
	_listB.setOriH(bonusH);
	_listB.setOriN(bonusOriN);
	_bonus->set(_listB);
}

