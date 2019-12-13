#include "bonusItem.h"

bonusItem::bonusItem()
{
	_N = _item.size();
}

bonusItem::~bonusItem()
{
}

int bonusItem::getN()
{
	return _N;
}

void bonusItem::setN(int N)
{
	_N = N;
}

item bonusItem::getI(int i)
{
	return _item[i];
}

void bonusItem::setOriN(int N)
{
	oriN = N;
}

int bonusItem::getOriN()
{
	return oriN;
}

void bonusItem::deleteItem(int i)
{
	_item.erase(_item.begin() + i);
	_N = _item.size();
}

bonusItem::bonusItem(vector<item>)
{
}

bonusItem::bonusItem(int x, int y, int width, int height)
{
	oriN=_N = rand() % 5 + 10;
	oriX = x;
	oriY = y;
	oriW = width;
	oriH = height;
	_item.resize(_N);
	int newX = x + 2;
	int newY = y + 5;
	for (int i = 0; i < _N; i++)
	{
		newX =x+ rand() % (width - 10);
		newY++;
		_item[i].set(newX, newY);
	}
}

void bonusItem::reset()
{
	oriN = _N = rand() % 5 + 10;
	_item.resize(_N);
	int newX = oriX + 2;
	int newY = oriY + 5;
	for (int i = 0; i < _N; i++)
	{
		newX = oriX + rand() % (oriW - 10);
		newY++;
		_item[i].set(newX, newY);
		_item[i].setSpe(rand() % 6 + 1);
	}
}

void bonusItem::drawItem()
{
	for (int i = 0; i < _N; i++)
	{
		_item[i].draw();
	}
}
