#pragma once

namespace BombBombCrash
{
	class ICollisionable
	{
	public:
		virtual int X()const = 0;
		virtual int RX()const = 0;
		virtual int Y()const = 0;
		virtual int DY()const = 0;
		virtual void SetX(int x) = 0;
		virtual void SetY(int y) = 0;
		virtual bool Exists() const = 0;
		virtual void SetExists(int flag) = 0;

		virtual ~ICollisionable(void){};
	};
}




