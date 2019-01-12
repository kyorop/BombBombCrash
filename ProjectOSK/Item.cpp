#include "Item.h"
#include "Image.h"

using namespace BombBombCrash;



void Item::Draw()
{
	DrawGraph(X(), Y(), image_.get_handle(), false);
}

void Item::OnCollide(MapObject& other)
{
	if (other.Type() == Fire ||
		other.Type() == Player ||
		other.Type() == Enemy)
	{
		Delete();
	}
}
