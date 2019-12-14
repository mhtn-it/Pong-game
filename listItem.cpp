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

void listItem::setOriX(int x)
{
	oriX = x;
}
void listItem::setOriY(int y)
{
	oriY = y;
}
void listItem::setOriW(int w)
{
	oriW = w;
}
void listItem::setOriH(int h)
{
	oriH = h;
}

int listItem::getOriX()
{
	return oriX;
}
int listItem::getOriY()
{
	return oriY;
}
int listItem::getOriW()
{
	return oriW;
}
int listItem::getOriH()
{
	return oriH;
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

void listItem::set(listItem list)
{
	_item = list._item;
	oriN = _N = list._item.size();
	oriX = list.oriX;
	oriY = list.oriY;
	oriW = list.oriW;
	oriH = list.oriH;
	oriN = list.oriN;
}

listItem::listItem(int x, int y, int width, int height)
{
	oriX = x;
	oriY = y;
	oriW = width;
	oriH = height;
	oriN = _N = 48;
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
vector<item> listItem::getVectorI()
{
	return _item;
}
void listItem::reset()
{
	oriN = _N = 48;
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
	item temp;
	for (int i = 0; i < _N; i++)
	{
		temp = _item[i];
		temp.setDelete(true);
		temp.draw();
	}
	for (int i = 0; i < _N; i++)
	{
		_item[i].draw();
	}
}
//Chuyen item thanh dang vien gach size = 4

void listItem::setXi(int i, int x)
{
	_item[i].setX(x);
}
void listItem::setYi(int i, int x)
{
	_item[i].setY(x);
}
void listItem::setSi(int i, int x)
{
	_item[i].setSize(x);
}
void listItem::setDi(int i, int x)
{
	_item[i].setDelete(x);
}
void listItem::pushI(item x)
{
	_item.push_back(x);
	_N++;
	oriN++;
}
