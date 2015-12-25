#include "MapObject.h"

using namespace BombBombCrash;

MapObject::MapObject(void) :
x(),
rx(),
y(),
dy(),
exists(true),
visible(true),
upperLeftPos(),
lowerRightPos()
{
}

MapObject::MapObject(const ln::Vector2& position, int width, int height):
x(),
rx(),
y(),
dy(),
exists(true),
visible(true),
upperLeftPos(position),
lowerRightPos(position + ln::Vector2(width,height))
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

bool MapObject::Exists() const
{
	return exists;
}

bool MapObject::Visible() const
{
	return visible;
}

void MapObject::SetVisible(bool isVisible)
{
	this->visible = isVisible;
}

void MapObject::SetExists(int flag)
{
	this->exists = flag;
}

ln::Vector2 MapObject::Position() const
{
	return upperLeftPos;
}

ln::Vector2 MapObject::LowerRightPosition() const
{
	return lowerRightPos;
}

void MapObject::SetPosition(const ln::Vector2& position)
{
	int currentW = Width();
	int currentH = Height();
	upperLeftPos = position;
	lowerRightPos.X = upperLeftPos.X + currentW;
	lowerRightPos.Y = upperLeftPos.Y + currentH;
}

int MapObject::Width() const
{
	return lowerRightPos.X - upperLeftPos.X;
}

int MapObject::Height() const
{
	return lowerRightPos.Y - upperLeftPos.Y;
}

void MapObject::Translate(const ln::Vector2& translation)
{
	upperLeftPos += translation;
	lowerRightPos += translation;
}
