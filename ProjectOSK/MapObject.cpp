#include "MapObject.h"


MapObject::MapObject(void):
	x(),
	rx(),
	y(),
	dy(),
	exists()
{
}

MapObject::~MapObject(void)
{
}

int MapObject::GetX()const
{
	return x;
}

void MapObject::SetX(int x)
{
	this->x = x;
	this->rx = x+32;

}

int MapObject::GetRX()const
{
	return rx;
}

int MapObject::GetY()const
{
	return y;
}

void MapObject::SetY(int y)
{
	this->y = y;
	this->dy = y+32;
}

int MapObject::GetDY()const
{
	return dy;
}

int MapObject::Exists()const
{
	return exists;
}

void MapObject::SetFlag(int flag)
{
	this->exists = flag;
}
