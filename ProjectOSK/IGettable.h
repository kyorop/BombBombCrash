#pragma once


namespace BombBombCrash
{
	class IGettable
	{
	public:
		virtual ~IGettable(void){};

		virtual int X()const = 0;
		virtual int RX()const = 0;
		virtual int Y()const = 0;
		virtual int DY()const = 0;
		virtual bool Exists() const = 0;
	};
}




