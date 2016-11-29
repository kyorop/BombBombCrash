#pragma once
#include "CollisionableObject.h"

namespace BombBombCrash
{
	class Timer;
	class NewFire:public CollisionableObject
	{
	private:
		std::weak_ptr<NewFire> pre;
		std::weak_ptr<NewFire> next;
		CollisionableObject* deletedObject;
		static int imageHandle;
		std::shared_ptr<Timer> timer;

		void KillForwardFire();
		void RecordDeletedObjectBackward(CollisionableObject* deletedObject);
	public:
		NewFire(ln::Vector2 position, int width, int height, const std::weak_ptr<NewFire>& pre, const std::weak_ptr<NewFire>& next);
		GameObjectType Type() const override;
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;
		void OnCollide(CollisionableObject* object) override;
		void SetPre(const std::weak_ptr<NewFire>& pre);
		void SetNext(const std::weak_ptr<NewFire>& next);
	};
}



