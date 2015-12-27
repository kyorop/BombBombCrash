#include "MapObject.h"
#include "Rect.h"

using namespace BombBombCrash;

MapObject::MapObject(void):
visible(true),
exists(true),
upperLeftPos(),
lowerRightPos()
{
}

MapObject::MapObject(const ln::Vector2& position, int width, int height):
visible(true),
exists(true),
upperLeftPos(position),
lowerRightPos(position + ln::Vector2(width,height))
{
}

MapObject::~MapObject(void)
{
}

int MapObject::X()const
{
	return upperLeftPos.X;
}

void MapObject::SetX(int x)
{
	SetPosition(ln::Vector2(x, upperLeftPos.Y));
}

int MapObject::RX()const
{
	return lowerRightPos.X;
}

int MapObject::Y()const
{
	return upperLeftPos.Y;
}

void MapObject::SetY(int y)
{
	SetPosition(ln::Vector2(upperLeftPos.X, y));
}

int MapObject::DY()const
{
	return lowerRightPos.Y;
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

Rect MapObject::Rect() const
{
	return ::Rect(upperLeftPos, lowerRightPos);
}

void MapObject::Translate(const ln::Vector2& translation)
{
	upperLeftPos += translation;
	lowerRightPos += translation;
}
