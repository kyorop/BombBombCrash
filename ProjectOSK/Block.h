#pragma once
#include "MapObstacle.h"

#include "CollisionableObject.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

namespace BombBombCrash
{
	enum MapType
	{
		FLOOR,
		HARDBLOCK,
		SOFTBLOCK,
	};

	class Block :public CollisionableObject
	{
	public:
		Block(const ln::Vector2& position);
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
	};


	class Item;
	class SoftBlock:public Block
	{
	public:

		void OnCollide(CollisionableObject* object) override{}
		GameObjectType Type() const override;
		void Draw(GameManager& game) override;
		void Finalize(GameManager& game) override;
	
		SoftBlock(const ln::Vector2& position, int imageHandle,const std::shared_ptr<BombBombCrash::Item>& item);
		SoftBlock(const ln::Vector2& position, int imageHandle);
		void SetItem(const std::shared_ptr<BombBombCrash::Item>& item);
	private:
		static int imageHandle;
		std::shared_ptr<BombBombCrash::Item> item;
	};



	class HardBlock:public Block
	{
	public:
		GameObjectType Type() const override;
		void OnCollide(CollisionableObject* object) override{}
		explicit HardBlock(const ln::Vector2& position, int imageHandle);

		void Draw(GameManager& game) override;
	private:
		static int imageHandle;
	};
}

