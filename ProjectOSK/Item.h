#pragma once
#include "Object.h"
#define KINDITEMNUM 3

class Block;
class Item:
	public Object  //class Objcet���p��
{
protected:
	static int graph[KINDITEMNUM];//�A�C�e���͂�������p����
private:
	int i_graph;
public:
	void SetItem(const Block &block);
	void Draw();
	Item(void);
	~Item(void);
	bool operator== (const Item &other);
};

