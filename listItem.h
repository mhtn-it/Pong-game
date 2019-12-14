#pragma once
#include "item.h"
class listItem
{
private:
	vector<item> _item;
	int _N;	//So luong hien tai
	int oriX, oriY, oriW, oriH;
	int oriN;
public:
	listItem();
	~listItem();
	int getN();
	void setN(int);
	void reset();
	item getI(int);
	void setOriN(int);
	int getOriN();
	void deleteItem(int);
	listItem(vector<item>);
	listItem(int, int, int, int);
	void setXi(int, int);
	void drawItem();
};