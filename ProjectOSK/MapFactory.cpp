#include "MapFactory.h"
#include "Map.h"
#include "GameConstant.h"
#include "Block.h"
#include "Image.h"
#include "Drawing.h"


namespace BombBombCrash
{
	MapFactory::MapFactory()
	{
	}


	MapFactory::~MapFactory()
	{
	}

	std::unique_ptr<Map> MapFactory::Craete()
	{
		std::vector<std::vector<std::shared_ptr<MapObstacle>>> mapSource;
		
		int temp[GameConst::MAP_ROW][GameConst::MAP_LINE] =
		{
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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

//		for (size_t i = 0; i < GameConst::MAP_ROW; ++i)
//		{
//			mapSource.push_back(std::vector<std::shared_ptr<MapObstacle>>());
//
//			for (size_t j = 0; i < GameConst::MAP_LINE; ++j)
//			{
//				auto type = static_cast<MapType>(temp[i][j]);
//				auto mapchip = std::make_shared<Floor>(temp[i][j], Image::GetInstance()->GetImage(Image::FLOOR));
//				switch (type)
//				{
//				case FLOOR:
//					mapSource[i].push_back(mapchip);
//					break;
//				case HARDBLOCK:
//					mapSource[i].push_back(std::make_shared<HardBlock>(temp[i][j], Image::GetInstance()->GetImage(Image::HARDBLOCK)));
//					break;
//				case SOFTBLOCK:
//					mapSource[i].push_back(std::make_shared<SoftBlock>(temp[i][j], Image::GetInstance()->GetImage(Image::SOFTBLOCK)));
//					break;
//				default:
//					break;
//				}
//				
//			}
//		}

		const int floorHandle = Image::GetInstance()->GetImage(Image::FLOOR);
		const int softHandle = Image::GetInstance()->GetImage(Image::SOFTBLOCK);
		const int hardHandle = Image::GetInstance()->GetImage(Image::HARDBLOCK);

		for (size_t i = 0; i < GameConst::MAP_ROW; ++i)
		{
			mapSource.push_back(std::vector<std::shared_ptr<MapObstacle>>());

			for (size_t j = 0; j < GameConst::MAP_LINE; ++j)
			{
				auto& mapRow = mapSource[i];

				auto type = static_cast<MapType>(temp[i][j]);
				switch (type)
				{
				case FLOOR:
				{
					auto floor = std::make_shared<Floor>(floorHandle);
					InitBlock(floor, i, j);
					mapRow.push_back(floor);
					Drawing::Add(floor);
				}
					break;
				case HARDBLOCK:
				{
					auto hard = std::make_shared<HardBlock>(hardHandle);
					InitBlock(hard, i, j);
					mapRow.push_back(hard);
					Drawing::Add(hard);
				}
					break;
				case SOFTBLOCK:
				{
					auto softBlock = std::make_shared<SoftBlock>(softHandle);
					mapRow.push_back(softBlock);
					InitBlock(softBlock, i, j);
					Drawing::Add(softBlock);

//					auto floor = std::make_shared<Floor>(floorHandle);
//					mapRow.push_back(floor);
//					InitBlock(floor, i, j);
//					Drawing::Add(floor);
				}
					break;
				}
			}
		}

		auto map = std::make_unique<Map>(mapSource);
		return map;
	}

	void MapFactory::InitBlock(const std::shared_ptr<MapObject>& block, int i, int j)
	{
		block->SetX(j * 32);
		block->SetY(i * 32);
	}
}
