#pragma once
#include "ICollisionable.h"
#include "IGettable.h"

namespace BombBombCrash
{
class MapObject:public ICollisionable,public IGettable
{
protected:
	int x;
	int rx;
	int y;
	int dy;
	bool exists;
	bool visible;
	ln::Vector2 upperLeftPos;
	ln::Vector2 lowerRightPos;

public:
	MapObject(void);
	MapObject(const ln::Vector2& position, int width, int height);

	virtual ~MapObject(void);

	virtual int GetX()const;
	virtual void SetX(int x);
	virtual int GetRX()const;
	virtual int GetY()const;
	virtual void SetY(int y);
	virtual int GetDY()const;
	virtual bool Exists() const;
	virtual bool Visible() const;
	virtual void SetVisible(bool isVisible);
	virtual void SetExists(int isExists);

	ln::Vector2 Position() const;
	ln::Vector2 LowerRightPosition() const;
	void SetPosition(const ln::Vector2& position);
	void Translate(const ln::Vector2& translation);
	int Width() const;
	int Height() const;
};
}




