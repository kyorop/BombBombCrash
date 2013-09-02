#pragma once
#include "Charactor.h"
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
public:	
	void CheckHit(Map &map);
	virtual void SetCharactorState(int flag);
	virtual void Move();
	virtual void Draw(Map &map, int g_lasttime);
	int GetStateFire(const Item &item);
	int GetStateBomb(const ItemManager &manageItem);
	Player();//コンストラクタ
	~Player(void);//デストラクタ
};

