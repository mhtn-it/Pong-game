#include "ball.h"

ball::ball()
{
	return;
}


ball::~ball()
{
	return;
}

void ball::setX(int x)
{
	_x = x;
}

void ball::setY(int y)
{
	_y = y;
}

void ball::setOriginalX(int oriX)
{
	_originalX = oriX;
}

void ball::setOriginalY(int oriY)
{
	_originalY = oriY;
}

void ball::setDirecton(ballDirection dir)
{
	_dir = dir;
}

void ball::setPreX(int preX)
{
	_preX = preX;
}

void ball::setPreY(int preY)
{
	_preY = preY;
}

int ball::getX()
{
	return _x;
}

int ball::getY()
{
	return _y;
}

int ball::getOriginalX()
{
	return _originalX;
}

int ball::getOriginalY()
{
	return _originalY;
}

int ball::getPreX()
{
	return _preX;
}

int ball::getPreY()
{
	return _preY;
}

ballDirection ball::getDirection()
{
	return _dir;
}

ball::ball(int oriX, int oriY)
{
	this->setOriginalX(oriX);
	this->setOriginalY(oriY);
	this->setX(oriX);
	this->setY(oriY);
	this->setPreX(oriX);
	this->setPreY(oriY);
	this->setDirecton(STOP);
}

void ball::reset()
{
	this->setX(this->getOriginalX());
	this->setY(this->getOriginalY());
	this->setDirecton(STOP);
}

void ball::randomDirection()
{
	_dir = (ballDirection)(rand() % 6 + 1);
}

void ball::move()
{
	switch (_dir) {
	case STOP:
		break;
	case UP:
		_y--;
		break;
	case DOWN:
		_y++;
		break;
	case UPLEFT:
		_y--; _x--;
		break;
	case UPRIGHT:
		_y--; _x++;
		break;
	case DOWNLEFT:
		_y++; _x--;
		break;
	case DOWNRIGHT:
		_y++; _x++;
	default:
		break;
	}
}
