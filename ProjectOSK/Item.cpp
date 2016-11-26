#include "Item.h"
#include "Collision.h"
#include "Image.h"

using namespace BombBombCrash;


void Item::Update(GameManager& game)
{
}

void Item::Draw(const GameManager& game)
{
}

Item::Item():
	i_graph(GetRand(itemNum - 1)),
	image_item(Image::GetInstance()->GetItemImage(i_graph))
{
	Collision::Instance()->RegisterWithItem(this);
}

Item::~Item()
{
}



int Item::GetKind() const
{
	return i_graph;
}

