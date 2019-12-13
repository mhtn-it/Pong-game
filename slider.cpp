#include "slider.h"
slider::slider()
{
	return;
}
slider::~slider()
{
	return;
}
void slider::setX(int x)
{
	_x = x;
}
void slider::setY(int y)
{
	_y = y;
}
void slider::setOriginalX(int oriX)
{
	_originalX = oriX;
}
void slider::setOriginalY(int oriY)
{
	_originalY = oriY;
}
void slider::setSize(int size)
{
	_size = size;
}
int slider::getSize()
{
	return _size;
}
int slider::getX()
{
	return _x;
}
int slider::getY()
{
	return _y;
}
int slider::getOriginalX()
{
	return _originalX;
}
int slider::getOriginalY()
{
	return _originalY;
}
slider::slider(int oriX, int oriY)
{
	this->setOriginalX(oriX);
	this->setOriginalY(oriY);
	this->setX(oriX);
	this->setY(oriY);
	_size = 0;
}
void slider::reset()
{
	this->setX(this->getOriginalX());
	this->setY(this->getOriginalY());
}
void slider::moveLeft()
{
	_x -= 4;
}
void slider::moveRight()
{
	_x += 4;
}