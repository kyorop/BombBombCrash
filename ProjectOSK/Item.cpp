#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "Collision.h"
#include "Image.h"
#include"DxLib.h"


Item::Item():
	i_graph( GetRand(itemNum-1) ),
	image_item( Image::GetInstance()->GetItemImage(i_graph) )
{
	Collision::GetInstance()->RegisterWithItem(this);
}

Item::~Item()
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



