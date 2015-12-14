#include "Item.h"
#include "Collision.h"
#include "Image.h"

using namespace BombBombCrash;


Item::Item():
	i_graph(GetRand(itemNum - 1)),
	image_item(Image::GetInstance()->GetItemImage(i_graph))
{
	Collision::Instance()->RegisterWithItem(this);
}

Item::~Item()
{
}


void Item::Draw()
{
	if (this->exists)
		DrawGraph(this->x, this->y, image_item,FALSE);
}


int Item::GetKind() const
{
	return i_graph;
}

