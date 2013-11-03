#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "Collision.h"
#include "Image.h"
#include"DxLib.h"
#define FIRE 0
#define BOMB 1
#define SPEED 2
#define DHIT 10
#define KINDITEMNUM 3

Item::Item():
	i_graph( GetRand(KINDITEMNUM-2) ),
	image_item( Image::GetInstance()->GetItemImage(i_graph) )
{
	Collision::GetInstance()->RegisterWithItem(this);
	flag = 1;
}

Item::~Item(void)
{
}

void Item::Draw()
{
	if(this->flag == 1)
	{
		DrawGraph(this->x, this->y, image_item,FALSE);
	}
}


int Item::GetKind()const
{
	return i_graph;
}



