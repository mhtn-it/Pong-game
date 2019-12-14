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
	_item.resize(0);
	_N = oriN = 0;
}

void bonusItem::reset()
{
	for (int i = 0; i < _N; i++)
	{
		_item[i].setDelete(true);
		_item[i].draw();
	}
	_item.resize(0);
	_N = oriN = 0;
}

void bonusItem::drawItem()
{
	for (int i = 0; i < _N; i++)
	{
		_item[i].draw();
	}
}

void bonusItem::pushBack(item i)
{
	_item.push_back(i);
	oriN++;
	_N++;
}
