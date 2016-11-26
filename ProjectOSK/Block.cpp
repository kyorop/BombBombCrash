#include "Block.h"
#include "MapState.h"
#include "GameConstant.h"
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

void Block::Destroy(const GameManager& game)
{
}

bool Block::CanRemove()
{
	return !Exists();
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

void HardBlock::Draw(const GameManager& game)
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

void SoftBlock::Draw(const GameManager& game)
{
	if (Exists())
	{
		DrawGraph(X(), Y(), imageHandle, false);
	}
}

SoftBlock::SoftBlock(const ln::Vector2& position, int imageHandle):
Block(position)
{
	if (!this->imageHandle)
		this->imageHandle = imageHandle;
}

MapObject::GameObjectType HardBlock::Type() const
{
	return GameObjectType::HardBlock;
}
