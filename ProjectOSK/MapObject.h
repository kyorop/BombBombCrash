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

public:
	MapObject(void);
	virtual ~MapObject(void);

	virtual int GetX()const;
	virtual void SetX(int x);
	virtual int GetRX()const;
	virtual int GetY()const;
	virtual void SetY(int y);
	virtual int GetDY()const;
	virtual bool Exists() const;
	virtual bool Visible() const;
	virtual void SetFlag(int flag);
};
}




