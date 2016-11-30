#pragma once
#include "CollisionableObject.h"

namespace BombBombCrash
{
	class Timer;
	class Fire:public CollisionableObject
	{
	private:
		std::weak_ptr<Fire> pre;
		std::weak_ptr<Fire> next;
		CollisionableObject* deletedObject;
		static int imageHandle;
		std::shared_ptr<Timer> timer;

		void KillForwardFire();
		void RecordDeletedObjectBackward(CollisionableObject* deletedObject);
	public:
		Fire(ln::Vector2 position, int width, int height, const std::weak_ptr<Fire>& pre, const std::weak_ptr<Fire>& next);
		GameObjectType Type() const override;
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;
		void OnCollide(CollisionableObject* object) override;
		void SetPre(const std::weak_ptr<Fire>& pre);
		void SetNext(const std::weak_ptr<Fire>& next);
	};
}



