#include <random>
#include "ItemManager.h"
#include "Item.h"
#include "GameConstant.h"
#include "BombUpItem.h"
#include "FireUpItem.h"
#include "SpeedUpItem.h"
#include "Image.h"
#include "Block.h"

using namespace BombBombCrash;

ItemManager::~ItemManager(void)
{
}

ItemManager::ItemManager()
{
}

std::vector<std::shared_ptr<Item>> ItemManager::Create()
{
	for (size_t i = 0; i < itemNum / 3; i++)
	{
		items.push_back(std::make_shared<FireUpItem>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, Image::GetInstance()->GetItemImage(Image::FIREUP)));
		items.push_back(std::make_shared<BombUpItem>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, Image::GetInstance()->GetItemImage(Image::BOMBUP)));
		items.push_back(std::make_shared<SpeedUpItem>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, Image::GetInstance()->GetItemImage(Image::SPEEDUP)));
	}


//	std::vector<ln::Vector2> softBlockPos;
//	for (auto itr = begin(map); itr != end(map); ++itr)
//	{
//		if ((*itr)->Type() == MapObject::SoftBlock)
//		{
//			softBlockPos.push_back((*itr)->Position());
//		}
//	}
//
//	std::random_device rd;
//	std::mt19937 mt(rd());
//	while (items.size() < softBlockPos.size())
//	{
//		std::uniform_int_distribution<> softBlockNumDistribution(0, softBlockPos.size());
//		int m = softBlockNumDistribution(mt);
//		softBlockPos.erase(begin(softBlockPos) + m);
//	}
//
//	for (size_t i = 0; i < items.size(); i++)
//	{
//		items[i]->SetPosition(softBlockPos[i]);
//	}
//
	return items;
}
