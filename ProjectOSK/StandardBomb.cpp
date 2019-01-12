#include "StandardBomb.h"
#include "GameManager.h"
#include "BombAnimation.h"
#include "Fire.h"

using namespace BombBombCrash;


StandardBomb::StandardBomb(int fire_level):
fire_level_(fire_level)
{
}

void StandardBomb::Initialize()
{
	bomb_animator_ = std::make_unique<BombAnimation>();
}

void StandardBomb::Update()
{
    if (timer_.CountDownFrame(2500))
	{
		Create(std::make_unique<BombBombCrash::Fire>(Position(), fire_level_));
		Delete();
    }
}

void StandardBomb::Draw()
{
	bomb_animator_->Play(X(), Y());
}

void StandardBomb::Finalize(){
	Notify();
}

void StandardBomb::AddObserver(const std::shared_ptr<IObserver>& observer)
{
	observers_.push_back(observer);
}

void StandardBomb::DeleteObserver(const std::shared_ptr<IObserver>& observer)
{
	auto itr = std::find(begin(observers_), end(observers_), observer);
	observers_.erase(itr);
}

void StandardBomb::Notify()
{
	for (auto& observer : observers_)
		observer->Update();
}

void StandardBomb::OnCollide(MapObject& other)
{
	if (other.Type() == Bomb && Exists())
	{
		other.Delete();
	}

	if (other.Type() == Fire)
	{
		Create(std::make_unique<BombBombCrash::Fire>(Position(), fire_level_));
		Delete();
	}
}
