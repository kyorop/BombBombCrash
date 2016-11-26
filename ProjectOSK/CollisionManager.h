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
		std::list<std::shared_ptr<CollisionableObject>> objects;

		void CheckCollide();
		void CheckRemove();
	};
}


