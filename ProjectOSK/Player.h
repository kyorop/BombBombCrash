#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#define PLAYERDEVIDENUMBER 20
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Map;
class Item;
class ItemManager;
class Player:
	public Charactor,virtual public IDrawable 
{
private:
	int graph[PLAYERDEVIDENUMBER];
	int muki;
	int animpat;
public:	
	//void CheckHit(Map &map);
	//virtual void SetCharactorState(int flag);
	virtual void Move(int g_lastTime);
	virtual void Draw();
	int GetStateFire(const Item &item);
	int GetStateBomb(const ItemManager &manageItem);
	Player();//コンストラクタ
	~Player(void);//デストラクタ
};

