#pragma once
#include "MapObstacle.h"
#include "IGameProgress.h"
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

	class Block :public CollisionableObject, public IGameProgress
	{
	public:
		Block(const ln::Vector2& position);
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Destroy(const GameManager& game) override;
		bool CanRemove() override;
	};



	class SoftBlock:public Block
	{
	public:
		void OnCollide(CollisionableObject* object) override{}
		GameObjectType Type() const override;
		void Draw(const GameManager& game) override;
	
		SoftBlock(const ln::Vector2& position, int imageHandle);
	private:
		static int imageHandle;
	};



	class HardBlock:public Block
	{
	public:
		GameObjectType Type() const override;
		void OnCollide(CollisionableObject* object) override{}
		explicit HardBlock(const ln::Vector2& position, int imageHandle);

		void Draw(const GameManager& game) override;
	private:
		static int imageHandle;
	};
}

