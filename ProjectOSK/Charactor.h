#pragma once
#include "MapObject.h"

namespace BombBombCrash
{
	class Character:public MapObject
	{
	protected:
		int preX;
		int preY;
		const int id;
		static int idGenerator;

		virtual bool PutBomb() = 0;

	public:

		Character(const ln::Vector2& position, int width, int height);

		Character(void);
		virtual ~Character(void);

		virtual int Speed()=0;
		virtual int BombSize()=0;
		virtual int FireLevel()=0;

		virtual void IncrementSpeed() = 0;
		virtual void IncrementBomb()=0;
		virtual void IncrementFireLevel()=0;

		virtual void Update() = 0;
		virtual void Move() = 0;
	};
}




