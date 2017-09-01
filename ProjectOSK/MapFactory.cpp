#include <algorithm>
#include <random>
#include "MapFactory.h"
#include "GameConstant.h"
#include "Block.h"
#include "Image.h"
#include "ControlPassingCollision.h"
#include "Item.h"
#include "ItemManager.h"

namespace BombBombCrash
{
	const int MapFactory::map[MAP_ROW][MAP_LINE]=
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	MapFactory::MapFactory()
	{
	}

	void MapFactory::MakeHardblock()
	{
		const int hardHandle = Image::GetInstance()->GetImage(Image::HARDBLOCK);
		for (size_t i = 0; i < MAP_ROW; ++i)
		{
			for (size_t j = 0; j < MAP_LINE; ++j)
			{
				if (map[i][j]==HARDBLOCK)
				{
					mapSource.push_back(std::make_shared<HardBlock>(ConvertToBlockPos(i,j), hardHandle));
				}
			}
		}
	}

	void MapFactory::MakeSoftBlock()
	{
		const int softImg = Image::GetInstance()->GetImage(Image::SOFTBLOCK);
		for (size_t i = 0; i < MAP_ROW; ++i)
		{
			for (size_t j = 0; j < MAP_LINE; ++j)
			{
				if (map[i][j] == SOFTBLOCK)
				{
					mapSource.push_back(std::make_shared<SoftBlock>(ConvertToBlockPos(i, j), softImg));
				}
			}
		}
	}

	void MapFactory::MakeItem()
	{

	}

	ln::Vector2 MapFactory::ConvertToBlockPos(const int i, const int j)
	{
		return ln::Vector2(GameConstant::BlockWidth*j, GameConstant::BlockHeight*i);
	}


	MapFactory::~MapFactory()
	{
	}

	std::vector<std::shared_ptr<Block>> MapFactory::Create()
	{

//		int temp[MAP_ROW][MAP_LINE] =
//		{
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
//			1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
//			1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
//			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
//			1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
//			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
//			1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
//			1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
//			1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
//			1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
//			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//		};

//		std::vector<ln::Vector2> itemPosMaker;
//		for (size_t i = 0; i < MAP_ROW; i++)
//		{
//			for (size_t j = 0; j < MAP_LINE; j++)
//			{
//				if (temp[i][j]==MapType::SOFTBLOCK)
//					itemPosMaker.push_back(ln::Vector2(GameConstant::BlockWidth*j, GameConstant::BlockHeight*i));
//			}
//		}
//		std::shuffle(begin(itemPosMaker), end(itemPosMaker), std::mt19937());
//		auto items = ItemManager().Create();
//		itemPosMaker.erase(begin(itemPosMaker) + items.size(), end(itemPosMaker));
//
//		const int softHandle = Image::GetInstance()->GetImage(Image::SOFTBLOCK);
//		const int hardHandle = Image::GetInstance()->GetImage(Image::HARDBLOCK);

//		for (size_t i = 0; i < MAP_ROW; ++i)
//		{
//			for (size_t j = 0; j < MAP_LINE; ++j)
//			{
//				auto blockPos = ln::Vector2(GameConstant::BlockWidth*j, GameConstant::BlockHeight*i);
//				switch (static_cast<MapType>(temp[i][j]))
//				{
//				case HARDBLOCK:
//					mapSource.push_back(std::make_shared<HardBlock>(blockPos, hardHandle));
//					break;
//				case SOFTBLOCK:
//					std::shared_ptr<Item> item=nullptr;
//					auto itemPosItr = find_if(begin(itemPosMaker), end(itemPosMaker), [&](const ln::Vector2& itemPos)
//					{
//						return itemPos == blockPos;
//					});
//					if (itemPosItr != end(itemPosMaker))
//						item = std::make_shared<Item>(blockPos,32,32,);
//					mapSource.push_back(std::make_shared<SoftBlock>(blockPos, softHandle,));
//					break;
//				default: break;
//				}
//			}
//		}

		MakeHardblock();
		MakeSoftBlock();
		return mapSource;
	}
}
