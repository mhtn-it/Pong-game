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
int ball::getNextX()
{
	int nextX = _x;;
	switch (_dir)
	{
	case STOP:
		break;
	case UP:
		break;
	case DOWN:
		break;
	case UPLEFT:
		nextX -= _vx;
		break;
	case UPRIGHT:
		nextX += _vx;
		break;
	case DOWNLEFT:
		nextX -= _vx;
		break;
	case DOWNRIGHT:
		nextX += _vx;
	default:
		break;
	}
	return nextX;
}
int ball::getNextY()
{
	int nextY = _y;
	switch (_dir)
	{
	case STOP:
		break;
	case UP:
		nextY -= _vy;
		break;
	case DOWN:
		nextY += _vy;
		break;
	case UPLEFT:
		nextY -= _vy;
		break;
	case UPRIGHT:
		nextY -= _vy;
		break;
	case DOWNLEFT:
		nextY += _vy;
		break;
	case DOWNRIGHT:
		nextY += _vy;
	default:
		break;
	}
	return nextY;
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
void ball::setVX(int v)
{
	_vx = v;
}
int ball::getVX()
{
	return _vx;
}
void ball::setVY(int v)
{
	_vy = v;
}
int ball::getVY()
{
	return _vy;
}
void ball::setV(int vx, int vy)
{
	_vx = vx;
	_vy = vy;
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
	_dir = (ballDirection)(rand() % 2 + 5);
}
void ball::randomV()
{
	_vx = rand() % 2 + 1;
	_vy = 1;
}
void ball::move()
{
	switch (_dir)
	{
	case STOP:
		break;
	case UP:
		_y -= _vy;
		break;
	case DOWN:
		_y += _vy;
		break;
	case UPLEFT:
		_y -= _vy; _x -= _vx;
		break;
	case UPRIGHT:
		_y -= _vy; _x += _vx;
		break;
	case DOWNLEFT:
		_y += _vy; _x -= _vx;
		break;
	case DOWNRIGHT:
		_y += _vy; _x += _vx;
	default:
		break;
	}
}