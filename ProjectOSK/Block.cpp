#include "Block.h"
#include "MapState.h"
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
		DrawGraph(GetX(), GetY(), imageHandle, false);
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
		DrawGraph(GetX(), GetY(), imageHandle, false);
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
		DrawGraph(GetX(), GetY(), imageHandle, false);
	}
}

void SoftBlock::Register()
{
	if (Exists())
		MapState::GetInstance()->SetBlockState(GetX(), GetY(), 1);
	else
		MapState::GetInstance()->SetBlockState(GetX(), GetY(), 0);
}