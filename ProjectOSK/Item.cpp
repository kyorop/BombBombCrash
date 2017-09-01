#include "Item.h"
#include "Collision.h"
#include "Image.h"

using namespace BombBombCrash;


Item::Item(const ln::Vector2& position, int width, int height, int imageHandle): 
CollisionableObject(position, width, height),
imageHandle(imageHandle)
{
}

void Item::OnCollide(CollisionableObject* object)
{
	if (object->Type() != SoftBlock)
		SetExists(false);
}

void Item::Update(GameManager& game)
{

}

void Item::Draw(GameManager& game)
{
	DrawGraph(X(), Y(), imageHandle, false);
}

Item::~Item()
{
}

