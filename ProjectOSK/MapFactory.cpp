#include "MapFactory.h"
#include "GameConstant.h"
#include "Block.h"
#include "Image.h"
#include "Drawing.h"
#include "ControlPassingCollision.h"


namespace BombBombCrash
{
	MapFactory::MapFactory()
	{
	}


	MapFactory::~MapFactory()
	{
	}

	std::vector<std::shared_ptr<Block>> MapFactory::Create()
	{
		std::vector<std::shared_ptr<Block>> mapSource;

		int temp[MAP_ROW][MAP_LINE] =
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
			1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
			1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
			1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
			1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
			1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		};


		const int softHandle = Image::GetInstance()->GetImage(Image::SOFTBLOCK);
		const int hardHandle = Image::GetInstance()->GetImage(Image::HARDBLOCK);

		for (size_t i = 0; i < MAP_ROW; ++i)
		{
			for (size_t j = 0; j < MAP_LINE; ++j)
			{
				auto blockPos = ln::Vector2(GameConstant::BlockWidth*j, GameConstant::BlockHeight*i);
				switch (static_cast<MapType>(temp[i][j]))
				{
				case HARDBLOCK:
					mapSource.push_back(std::make_shared<HardBlock>(blockPos, hardHandle));
					break;
				case SOFTBLOCK:
					mapSource.push_back(std::make_shared<SoftBlock>(blockPos, softHandle));
					break;
				default: break;
				}
			}
		}

		return mapSource;
	}
}
