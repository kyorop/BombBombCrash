#pragma once
#include "Object.h"
#define KINDITEMNUM 3

class Block;
class Player;
class Charactor;
class Item:
	public Object  //class Objcetを継承
{
protected:
	static int graph[KINDITEMNUM];//アイテムはこれを共用する
private:
	int charactorHit;
	int i_graph;
public:
	int CheckHItCharactor(const Charactor &charactor);
	int GetKindGraph();
	int GetCharactorHit();
	void SetItem(const Block &block);
	void Draw();
	Item(void);
	~Item(void);
	bool operator== (const Item &other);
	bool operator== (const Player &player);
};

