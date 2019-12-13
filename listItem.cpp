#include "listItem.h"

listItem::listItem()
{
	_N = _item.size();
}

listItem::~listItem()
{
}

int listItem::getN()
{
	return _N;
}

void listItem::setN(int N)
{
	_N = N;
}

item listItem::getI(int i)
{
	return _item[i];
}

void listItem::setOriN(int _oN)
{
	oriN = _oN;
}

int listItem::getOriN()
{
	return oriN;
}

void listItem::deleteItem(int i)
{
	_item.erase(_item.begin() + i);
	_N = _item.size();
}

listItem::listItem(vector<item> list)
{
	_item = list;
	oriN = _N = list.size();
}

listItem::listItem(int x, int y, int width, int height)
{
	oriX = x;
	oriY = y;
	oriW = width;
	oriH = height;
	oriN = _N = 40;
	_item.resize(_N);
	int newX = x + 2;
	int newY = y + 1;
	for (int i = 0; i < _N; i++)
	{
		if (newX + 5 >= x + width)
		{
			newY++;
			newX = x + 2;
		}
		_item[i].set(newX, newY);
		newX += _item[i].getSize();
		_item[i].setSpe(0);
	}
}
void listItem::reset()
{
	oriN = _N = 40;
	_item.resize(_N);
	int newX = oriX + 2;
	int newY = oriY + 1;
	for (int i = 0; i < _N; i++)
	{
		if (newX + 5 >= oriX + oriW)
		{
			newY++;
			newX = oriX + 2;
		}
		_item[i].set(newX, newY);
		newX += _item[i].getSize();
		_item[i].setSpe(0);
	}
}
void listItem::drawItem()
{
	for (int i = 0; i < _N; i++)
	{
		_item[i].draw();
	}
}

//Chuyen item thanh dang vien gach size = 4