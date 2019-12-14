#pragma once
#include "Header.h"
#include "item.h"
class bonusItem
{
private:
	vector<item> _item;
	int _N;	//So luong hien tai
	int oriX, oriY, oriW, oriH;
	int oriN;
public:
	bonusItem();
	~bonusItem();
	int getN();
	void setN(int);
	void reset();
	item getI(int);
	int getOriX();
	int getOriY();
	int getOriW();
	int getOriH();
	void setOriX(int);
	void setOriY(int);
	void setOriW(int);
	void setOriH(int);
	void setOriN(int);
	int getOriN();
	void deleteItem(int);
	bonusItem(vector<item>);
	bonusItem(int, int, int, int);
	void drawItem();
	void pushBack(item);
	void set(bonusItem);
};

