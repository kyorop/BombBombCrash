#pragma once
#include "MapObject.h"
#include "AnimationClip.h"
#include "Timer.h"
#include "ISubject.h"

namespace BombBombCrash
{
	class Fire :public MapObject
	{
		static AnimationClip image_;
		Timer timer_;
		int remaining_fire_num_;
		ln::Vector2 fire_spreading_direction_;
		static std::unique_ptr<Fire> CreateSpreadingFire(const ln::Vector2& position, const ln::Vector2& fire_spreading_direction, int remaining_fire_num);
	public:
		Fire(ln::Vector2 position, int fire_level);

		ObjectType Type() const override{ return ObjectType::Fire; }
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Draw() override;
		void Finalize() override{}
		void OnCollide(MapObject& other) override;
	};
}



