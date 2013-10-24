#pragma once
#include "MapObject.h"
#define KINDITEMNUM 3

class Block;
class Player;
class Charactor;
class Item
	:public MapObject
{
protected:
	static int graph[KINDITEMNUM];//アイテムはこれを共用する
private:
	int charactorHit;
	int i_graph;
public:
	Item(void);
	~Item(void);

	void CheckHItCharactor(Charactor *charactor);
	int GetKindGraph();
	int GetCharactorHit();
	void SetItem(const Block &block);
	void Draw();

	bool operator== (const Item &other);
	bool operator== (const Player &player);
};

