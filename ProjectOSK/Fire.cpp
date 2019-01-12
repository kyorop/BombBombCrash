#include "Fire.h"
#include "Image.h"
#include "Timer.h"

using namespace BombBombCrash;

AnimationClip Fire::image_;

std::unique_ptr<Fire> Fire::CreateSpreadingFire(const ln::Vector2& position,
	const ln::Vector2& fire_spreading_direction, int remaining_fire_num)
{
	auto spreading_fire = std::make_unique<Fire>(position, remaining_fire_num - 1);
	spreading_fire->fire_spreading_direction_ = fire_spreading_direction;
	return spreading_fire;
}

Fire::Fire(ln::Vector2 position, int fire_level):
MapObject(position),
remaining_fire_num_(fire_level),
fire_spreading_direction_(ln::Vector2(0,0))
{
}


void Fire::Initialize()
{
	if (image_.Length() == 0)
		image_ = Image::GetInstance()->Load("Images\\fire.bmp");
}

void Fire::Update()
{
	if (timer_.CountDownFrame(1 * 1000))
		Delete();
}

void Fire::LateUpdate()
{
	if (remaining_fire_num_ > 0)
	{
		if (fire_spreading_direction_ == ln::Vector2(0,0))
		{
			Create(CreateSpreadingFire(Position() + ln::Vector2(0, -Width()), ln::Vector2(0, -Width()), remaining_fire_num_ - 1));
			Create(CreateSpreadingFire(Position() + ln::Vector2(-Width(), 0), ln::Vector2(-Width(), 0), remaining_fire_num_ - 1));
			Create(CreateSpreadingFire(Position() + ln::Vector2(Width(), 0), ln::Vector2(Width(), 0), remaining_fire_num_ - 1));
			Create(CreateSpreadingFire(Position() + ln::Vector2(0, Width()), ln::Vector2(0, Width()), remaining_fire_num_ - 1));
		}
		else
		{
			Create(CreateSpreadingFire(Position() + fire_spreading_direction_, fire_spreading_direction_, remaining_fire_num_ - 1));
		}
		remaining_fire_num_ = 0;
	}
}

void Fire::Draw()
{
	DrawGraph(X(), Y(), image_.get_handle(), true);
}

void Fire::OnCollide(MapObject& other)
{
	if (other.Type() == HardBlock ||
		other.Type() == BREAKABLE_BLOCK||
		other.Type() == Bomb)
	{
		Delete();
	}
}