#pragma once
#include "MapObstacle.h"
#include "IGameProgress.h"
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

	class Block :public MapObject, public IGameProgress
	{
	public:
		Block(const ln::Vector2& position);
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Destroy(const GameManager& game) override;
		bool CanRemove() override;
		virtual MapType Type() = 0;
	};



	class SoftBlock:public Block
	{
	public:
		void Draw(const GameManager& game) override;
	
		SoftBlock(const ln::Vector2& position, int imageHandle);

		MapType Type() override{ return SOFTBLOCK; }

	private:
		static int imageHandle;
	};



	class HardBlock:public Block
	{
	public:
		explicit HardBlock(const ln::Vector2& position, int imageHandle);

		void Draw(const GameManager& game) override;
		MapType Type() override{ return HARDBLOCK; }
	private:
		static int imageHandle;
	};
}

