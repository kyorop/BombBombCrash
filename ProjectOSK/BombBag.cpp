#include "stdafx.h"
#include "BombBag.h"
#include "StandardBomb.h"


void BombBag::Update()
{
	--living_bomb_num_;
	if (living_bomb_num_ <= 0)
		living_bomb_num_ = 0;
}


std::unique_ptr<BombBombCrash::StandardBomb> BombBag::Request(const std::shared_ptr<BombBag>& bomb_bag, const ln::Vector2& position)
{
	int j = (position.X + position.X + 32) / 2 / 32;
	int i = (position.Y + position.Y + 32) / 2 / 32;

	if (bomb_bag->living_bomb_num_ >= bomb_bag->maximum_possession_num_)
		return nullptr;

	++bomb_bag->living_bomb_num_;
	auto bomb = std::make_unique<BombBombCrash::StandardBomb>(bomb_bag->FireLevel());
	bomb->SetPosition(i, j);
	bomb->AddObserver(bomb_bag);
	return bomb;
}