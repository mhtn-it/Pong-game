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
	vector<item> getVectorI();
	item getI(int);
	void setOriX(int);
	void setOriY(int);
	void setOriW(int);
	void setOriH(int);
	int getOriX();
	int getOriY();
	int getOriW();
	int getOriH();
	void setOriN(int);
	int getOriN();
	void deleteItem(int);
	listItem(vector<item>);
	void set(listItem);
	listItem(int, int, int, int);
	void drawItem();
	void setXi(int, int);
	void setYi(int, int);
	void setSi(int, int);
	void setDi(int, int);
	void pushI(item);
};