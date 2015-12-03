#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

namespace BombBombCrash
{
	class Character;
	class SoftBlock:public MapObstacle, public IDrawable, public IRegister
	{
		static int imageHandle;

	public:
		SoftBlock(int id, int imageHandle);
		~SoftBlock();

		void Register() override;
		void Draw() override;
	};

	class HardBlock:public MapObstacle, public IDrawable
	{
		static int imageHandle;
	
	public:
		HardBlock(int id, int imageHandle);

		void Draw() override;
	};

	class Floor: public MapObstacle, public IDrawable
	{
		static int imageHandle;
	public:
		Floor(int id, int imageHandle);
		void Draw() override;
	};
}

