#include "Block.h"
#include "MapState.h"
#include "GameConstant.h"
#include "GameManager.h"
#include "Item.h"
#define HABA 0
#define DHIT 5
#define KBHABA 16

using namespace BombBombCrash;

int SoftBlock::imageHandle;
int HardBlock::imageHandle;

void Block::Initialize(GameManager& game)
{
}

void Block::Update(GameManager& game)
{
}

Block::Block(const ln::Vector2& position):
CollisionableObject(position, GameConstant::BlockWidth,GameConstant::BlockHeight)
{
}

HardBlock::HardBlock(const ln::Vector2& position, int imageHandle): 
Block(position)
{
	if (!this->imageHandle)
		this->imageHandle = imageHandle;
}

void HardBlock::Draw(GameManager& game)
{
	if (Exists())
	{
		DrawGraph(X(), Y(), imageHandle, false);
	}
}

MapObject::GameObjectType SoftBlock::Type() const
{
	return GameObjectType::SoftBlock;
}

void SoftBlock::Draw(GameManager& game)
{
	if (Exists())
	{
		DrawGraph(X(), Y(), imageHandle, false);
	}
}

void SoftBlock::Finalize(GameManager& game)
{
	if (item)
		game.AddGameObject(item);
}

SoftBlock::SoftBlock(const ln::Vector2& position, int imageHandle,const std::shared_ptr<BombBombCrash::Item>& item):
Block(position),
item(item)
{
	if (!this->imageHandle)
		this->imageHandle = imageHandle;
}

SoftBlock::SoftBlock(const ln::Vector2& position, int imageHandle):
Block(position),
item(nullptr)
{
	if (!this->imageHandle)
		this->imageHandle = imageHandle;
}

void SoftBlock::SetItem(const std::shared_ptr<BombBombCrash::Item>& item)
{
	this->item = item;
}

MapObject::GameObjectType HardBlock::Type() const
{
	return GameObjectType::HardBlock;
}
