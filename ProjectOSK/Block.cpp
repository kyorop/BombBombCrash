#include "Block.h"
#include "MapState.h"
#define HABA 0
#define DHIT 5
#define KBHABA 16

namespace BombBombCrash
{
	int SoftBlock::imageHandle;

	SoftBlock::SoftBlock(int id, int imageHandle)
		:MapObstacle(id)
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

	HardBlock::HardBlock(int id, int imageHandle)
		:MapObstacle(id)
	{
		this->imageHandle = imageHandle;
	}

	void HardBlock::Draw()
	{
		if (Exists())
			DrawGraph(GetX(), GetY(), imageHandle, false);
	}



	int Floor::imageHandle;

	Floor::Floor(int id, int imageHandle):
		MapObstacle(id)
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
	
}
