#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "Collision.h"
#include"DxLib.h"
#define FIRE 0
#define BOMB 1
#define SPEED 2
#define DHIT 10

int Item::graph[KINDITEMNUM];

Item::Item():
	i_graph(GetRand(KINDITEMNUM-2)),
	charactorHit(0)//何のアイテムを出すか決める
{
	Collision::GetInstance()->RegisterWithItem(this);
	LoadDivGraph("itemup.bmp", 3, 3, 1, 32, 32, Item::graph, FALSE);
	this->flag = 1;
}

Item::~Item(void)
{
}

void Item::Draw()
{
	if(this->flag == 1)
	{
		DrawGraph(this->x, this->y, this->graph[i_graph],FALSE);
	}
}


int Item::GetKind()const
{
	return i_graph;
}



