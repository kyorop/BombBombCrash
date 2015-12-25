#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
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

	class Character;
	class SoftBlock:public MapObstacle, public IDrawable, public IRegister
	{
		static int imageHandle;
	public:
		explicit SoftBlock(int imageHandle);
		~SoftBlock();

		void Register() override;
		void Draw() override;
		int Type() const override{return SOFTBLOCK;}
	};

	class HardBlock:public MapObstacle, public IDrawable
	{
		static int imageHandle;
	
	public:
		HardBlock(int imageHandle);

		void Draw() override;
		int Type() const override{return HARDBLOCK;}
	};

	class Floor: public MapObstacle, public IDrawable
	{
		static int imageHandle;
	public:
		Floor(int imageHandle);
		void Draw() override;
		int Type() const override{ return FLOOR; }
	};
}

