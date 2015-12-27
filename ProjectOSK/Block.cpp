#include "Block.h"
#include "MapState.h"
#include "GameConstant.h"
#define HABA 0
#define DHIT 5
#define KBHABA 16

using namespace BombBombCrash;

int SoftBlock::imageHandle;

SoftBlock::SoftBlock(int imageHandle)
{
	this->imageHandle = imageHandle;
}

SoftBlock::~SoftBlock(void)
{
}

void SoftBlock::Draw()
{
	if (Exists())
	{
		DrawGraph(X(), Y(), imageHandle, false);
	}
}



int HardBlock::imageHandle;

HardBlock::HardBlock(int imageHandle)
{
	this->imageHandle = imageHandle;
}

void HardBlock::Draw()
{
	if (Exists())
		DrawGraph(X(), Y(), imageHandle, false);
}



int Floor::imageHandle;

Floor::Floor(int imageHandle)
{
	this->imageHandle = imageHandle;
}

void Floor::Draw()
{
	if (Exists())
	{
		DrawGraph(X(), Y(), imageHandle, false);
	}
}

void Block::Initialize(GameManager& game)
{
}

void Block::Update(GameManager& game)
{
}

void Block::Draw(const GameManager& game)
{
	if (Exists())
		DrawGraph(X(), Y(), imageHandle, false);
}

void Block::Destroy(const GameManager& game)
{
}

bool Block::CanRemove()
{
	return !Exists();
}

Block::Block(const ln::Vector2& position, int imageHandle):
MapObject(position, GameConstant::BlockWidth,GameConstant::BlockHeight),
imageHandle(imageHandle)
{
}

void SoftBlock::Register()
{
	if (Exists())
		MapState::GetInstance()->SetBlockState(X(), Y(), 1);
	else
		MapState::GetInstance()->SetBlockState(X(), Y(), 0);
}
