#pragma once
#include "CollisionableObject.h"


namespace BombBombCrash
{
	class Item:public CollisionableObject
	{
	public:
		Item(const ln::Vector2& position, int width, int height, int imageHandle);

	public:
		void OnCollide(CollisionableObject* object) override;
		void Update(GameManager& game) override;
		void Draw(GameManager& game) override;

	private:
		const int imageHandle;

	public:
		~Item();
	};
}




