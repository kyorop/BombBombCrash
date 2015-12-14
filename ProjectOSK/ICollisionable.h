#pragma once

namespace BombBombCrash
{
	class ICollisionable
	{
	public:
		virtual int GetX()const = 0;
		virtual int GetRX()const = 0;
		virtual int GetY()const = 0;
		virtual int GetDY()const = 0;
		virtual void SetX(int x) = 0;
		virtual void SetY(int y) = 0;
		virtual bool Exists() const = 0;
		virtual void SetFlag(int flag) = 0;

		virtual ~ICollisionable(void){};
	};
}




