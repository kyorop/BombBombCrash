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
	if (Exists())
		DrawGraph(Position().X, Position().Y, image_item,FALSE);
}


int Item::GetKind() const
{
	return i_graph;
}

