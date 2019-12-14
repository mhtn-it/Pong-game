#include "item.h"

item::item()
{
	_x = 0;
	_y = 0;
	_size = 5;
	_deleted = false;
}

item::~item()
{
}

item::item(int x, int y, int size)
{
	_x = x;
	_y = y;
	_size = size;
}

item::item(int size)
{
	_size = size;
}

void item::setDelete(bool del)
{
	_deleted = del;
}

bool item::getDelete()
{
	return _deleted;
}

int item::getX()
{
	return _x;
}

int item::getY()
{
	return _y;
}

void item::setSpe(int spe)
{
	_spe = (itemSpecific)(spe);
}

itemSpecific item::getSpe()
{
	return _spe;
}

void item::setX(int x)
{
	_x = x;
}

void item::setY(int y)
{
	_y = y;
}

void item::set(int x, int y)
{
	_x = x;
	_y = y;
}
void item::setI(item x)
{
	_x = x._x;
	_y = x._y;
	_size = x._size;
	_deleted = x._deleted;
}
int item::getSize()
{
	return _size;
}

void item::setSize(int size)
{
	_size = size;
}

void item::draw()
{
	switch (_spe)
	{
	case NORMAL:
		textcolor(11);
		break;
	case PLUS:
		textcolor(10);
		break;
	case MINUS:
		textcolor(12);
		break;
	case DOU:
		textcolor(9);
		break;
	case HALF:
		textcolor(4);
		break;
	case HALFSLIDER:
		textcolor(13);
		break;
	case ORISLIDER:
		textcolor(1);
		break;
	default:
		break;
	}
	gotoxy(_x, _y);
	if (!_deleted)
	{
		for (int i = 0; i < _size - 1; i++)
			cout << static_cast<char>(220);
	}
	else
	{
		//for (int i = 0; i < _size - 1; i++)
			cout << "    ";
	}
	cout << " ";
	textcolor(7);
}
