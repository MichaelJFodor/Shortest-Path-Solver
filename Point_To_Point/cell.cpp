#include "cell.h"

cell& cell::operator=(const cell& a)
{
	x_ = a.x_;
	y_ = a.y_;
	coord_ = a.coord_;
	val_ = a.val_;

	return *this;
}

int cell::getX()
{
	return x_;
}

int cell::getY()
{
	return y_;
}

int cell::getVal()
{
	return val_;
}

int cell::getCoord()
{
	return coord_;
}

bool cell::getSource()
{
	return isSource_;
}

int cell::extractX(int width)
{
	int x = coord_ % width;
	return x;
}

int cell::extractY(int width)
{
	int y = (int)(coord_ / width);
	return y;
}

void cell::setX(const int x)
{
	x_ = x;
}

void cell::setY(const int y)
{
	y_ = y;
}

void cell::setCoord(int coord)
{
	coord_ = coord;
}

void cell::calculateCoord(const int width)
{
	coord_ = y_ * width + x_;
}

void cell::setSource(bool isSource)
{
	isSource_ = isSource;
}

void cell::setVal(const int val)
{
	val_ = val;
}
