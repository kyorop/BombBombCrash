#include "MapObject.h"
#include "Rect.h"
#include "GameManager.h"

using namespace BombBombCrash;

int MapObject::id_generator_ = 0;

MapObject::MapObject():
	id_(id_generator_++)
{}

MapObject::MapObject(const ln::Vector2& position, int width, int height):
	upperLeftPos(position),
id_(id_generator_++),
width_(width),
height_(height)
{}

MapObject::MapObject(ln::Vector2 initial_position)
	:
	upperLeftPos(initial_position),
	id_(id_generator_++)
{
}

MapObject::MapObject(int i, int j)
	:
	upperLeftPos(ln::Vector2(j*32, i*32)),
	id_(id_generator_++)
{
}

void MapObject::SetX(float x)
{
	SetPosition(ln::Vector2(x, upperLeftPos.Y));
}


void MapObject::SetY(float y)
{
	SetPosition(ln::Vector2(upperLeftPos.X, y));
}

ln::Vector2 MapObject::LowerRightPosition() const
{
	return upperLeftPos + ln::Vector2(width_, height_);
}

void MapObject::SetPosition(const ln::Vector2& position)
{
	upperLeftPos = position;
}

void MapObject::SetPosition(int i, int j)
{
	SetPosition(ln::Vector2(j*Width(), i*Height()));
}

int MapObject::Width() const
{
	return width_;
}

int MapObject::Height() const
{
	return height_;
}

Rect MapObject::Rect() const
{
	return ::Rect(upperLeftPos, upperLeftPos + ln::Vector2(width_, height_));
}

void MapObject::Create(std::unique_ptr<MapObject> new_entity)
{
	GameManager::Instance().AddTask(move(new_entity));
}

void MapObject::Delete()
{
	exists = false;
	GameManager::Instance().DeleteTask(this);
}

void MapObject::Translate(const ln::Vector2& translation)
{
	upperLeftPos += translation;
}
