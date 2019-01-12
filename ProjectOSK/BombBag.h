#pragma once
#include "StandardBomb.h"
#include "IObserver.h"

class BombBag : public IObserver
{
	int living_bomb_num_;
	int maximum_possession_num_;
	int fire_level_;
public:
	BombBag()
		:living_bomb_num_(0),maximum_possession_num_(1),fire_level_(1)
	{
	}
	void IncrementMaxBombNum(){ ++maximum_possession_num_; }
	void IncrementFireLevel(){ ++fire_level_; }
	int MaxBombNum()const{ return maximum_possession_num_; }
	int FireLevel()const { return fire_level_; }
	static std::unique_ptr<BombBombCrash::StandardBomb> Request(const std::shared_ptr<BombBag>& bomb_bag, const ln::Vector2& position);
	void Update() override;
};
