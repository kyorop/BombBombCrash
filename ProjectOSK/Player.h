#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"
#define PLAYERDEVIDENUMBER 20
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Map;
class Item;
class ItemManager;
class Player:
	public Charactor
{
private:
	int graph[PLAYERDEVIDENUMBER];
	int muki;
	int animpat;
	
public:	
	Player();
	~Player();

	 void Move()override;
	 void Draw()override;
	int EnableBomb()const override;
	//int GetStateFire(const Item &item);
	//int GetStateBomb(const ItemManager &manageItem);
};

