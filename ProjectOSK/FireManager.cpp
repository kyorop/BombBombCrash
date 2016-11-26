#include "FireManager.h"
#include "GameConstant.h"
#include "NewFire.h"

BombBombCrash::FireManager::FireManager():
center()
{
	auto nullFire = std::shared_ptr<NewFire>(nullptr);

	center = std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, nullFire, nullFire);
	up.push_back(std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, nullFire, nullFire));
	right.push_back(std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, nullFire, nullFire));
	down.push_back(std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, nullFire, nullFire));
	left.push_back(std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, nullFire, nullFire));
}

std::vector<std::shared_ptr<BombBombCrash::NewFire>> BombBombCrash::FireManager::Create(const ln::Vector2& centerPosition)
{
	const int width = GameConstant::BlockWidth;
	const int height = GameConstant::BlockHeight;

	center->SetPosition(centerPosition);
	center->SetExists(true);
	for (int i = 0; i < up.size();i++)
	{
		up[i]->SetPosition(centerPosition + ln::Vector2(height*(-(i+1)), 0));
		right[i]->SetPosition(centerPosition + ln::Vector2(0, width*(i + 1)));
		down[i]->SetPosition(centerPosition + ln::Vector2(height*(i+1),0));
		left[i]->SetPosition(centerPosition + ln::Vector2(0,width*(-(i+1))));

		up[i]->SetExists(true);
		right[i]->SetExists(true);
		down[i]->SetExists(true);
		left[i]->SetExists(true);
	}
	std::vector<std::shared_ptr<NewFire>> newFire;
	newFire.push_back(center);
	newFire.insert(end(newFire), begin(up), end(up));
	newFire.insert(end(newFire), begin(right), end(right));
	newFire.insert(end(newFire), begin(down), end(down));
	newFire.insert(end(newFire), begin(left), end(left));
	return newFire;
}

void BombBombCrash::FireManager::IncreaseFirePower()
{
	auto nullFire = std::shared_ptr<NewFire>(nullptr);
	auto newUp = std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, up[up.size() - 1], nullFire);
	up[up.size() - 1]->SetNext(newUp);
	up.push_back(newUp);

	auto newRight = std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, right[right.size() - 1], nullFire);
	right[right.size() - 1]->SetNext(newRight);
	right.push_back(newRight);

	auto newDown = std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, down[down.size() - 1], nullFire);
	down[down.size() - 1]->SetNext(newDown);
	down.push_back(newDown);

	auto newLeft = std::make_shared<NewFire>(ln::Vector2(), GameConstant::BlockWidth, GameConstant::BlockHeight, left[left.size() - 1], nullFire);
	left[left.size() - 1]->SetNext(newLeft);
	left.push_back(newLeft);
}
