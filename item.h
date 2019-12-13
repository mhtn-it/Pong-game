#pragma once
#include "Header.h"

enum itemSpecific {NORMAL, PLUS, MINUS, DOU, HALF, HALFSLIDER, ORISLIDER};

class item
{
private:
	int _x, _y;
	int _size;
	bool _deleted;
	itemSpecific _spe;
public:
	item();
	~item();
	item(int, int, int);
	item(int);
	void setDelete(bool);
	bool getDelete();
	int getX();
	int getY();
	void setSpe(int);
	itemSpecific getSpe();
	void setX(int);
	void setY(int);
	void set(int, int);
	int getSize();
	void setSize(int);
	void draw();
};

