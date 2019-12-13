#pragma once
#include "Header.h"
enum ballDirection { STOP = 0, UP = 1, UPLEFT = 2, UPRIGHT = 3, DOWN = 4, DOWNLEFT = 5, DOWNRIGHT = 6 };

class ball
{
private:
	int _originalX, _originalY;
	int _x, _y;
	int _preX, _preY;
	int _vx,_vy;
	ballDirection _dir;
public:
	void setX(int x);
	void setY(int y);
	void setOriginalX(int oriX);
	void setOriginalY(int oriY);
	void setDirecton(ballDirection dir);
	void setPreX(int preX);
	void setPreY(int preY);
	void setVX(int);
	void setVY(int);
	void setV(int, int);
	int getX();
	int getY();
	int getNextX();
	int getNextY();
	int getOriginalX();
	int getOriginalY();
	int getPreX();
	int getPreY();
	int getVX();
	int getVY();
	ball();
	~ball();
	ballDirection getDirection();
	//Khởi tạo trái bóng
	ball(int oriX, int oriY);
	//Đưa trái bóng về trạng thái ban đầu
	void reset();
	//Chọn 1 hướng bất kì cho trái bóng
	void randomDirection();
	//Thay đổi tọa độ của bóng khi di chuyển
	void move();
	void randomV();
};