#pragma once
#include "Task.h"

namespace BombBombCrash
{
	class CollisionableObject;
	class CollisionManager :public Task
	{
	public:
		void Update() override;
		void Add(const std::shared_ptr<CollisionableObject>& object);
	private:
		std::vector<std::shared_ptr<CollisionableObject>> objects;
	};
}


