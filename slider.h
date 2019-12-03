#pragma once
#include "Header.h"

class slider
{
private:
	int _x, _y;
	int _originalX, _originalY;
public:

	void setX(int x);
	void setY(int y);
	void setOriginalX(int oriX);
	void setOriginalY(int oriY);
	int getX();
	int getY();
	int getOriginalX();
	int getOriginalY();
	slider();
	~slider();
	//Khởi tạo thanh
	slider(int oriX, int oriY);
	//Đưa thanh về vị trí ban đầu
	void reset();
	//Sang trái
	void moveLeft();
	//Sang phải
	void moveRight();
};
