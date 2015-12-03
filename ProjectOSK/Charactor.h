#pragma once
#include "MapObject.h"

class BombController;
class Map;
class Character:public MapObject
{
protected:
	int preX;
	int preY;
	const int id;
	static int idGenerator;

	virtual bool PutBomb() = 0;

public:
	Character(void);
	virtual ~Character(void);

	virtual int Speed()=0;
	virtual int BombSize()=0;
	virtual int Firepower()=0;

	virtual void IncrementSpeed() = 0;
	virtual void IncrementBomb()=0;
	virtual void IncrementFirepower()=0;

	virtual void Update() = 0;
	virtual void Move() = 0;
};

