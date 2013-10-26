#pragma once
#include "MapObject.h"
#define KINDITEMNUM 3

class Block;
class Player;
class Charactor;
class Item
	:public MapObject
{
public:
	enum
	{
		FIRE,
		BOMB, 
		SPEED,
	};
protected:
	static int graph[KINDITEMNUM];//アイテムはこれを共用する
private:
	int charactorHit;
	int i_graph;
	const int kind;
public:
	Item();
	~Item(void);

	//void CheckHItCharactor(Charactor *charactor);
	int GetKindGraph();
	int GetCharactorHit();
	void SetItem(const Block &block);
	void Draw();
	int GetKind()const;

	bool operator== (const Item &other);
	bool operator== (const Player &player);
};

