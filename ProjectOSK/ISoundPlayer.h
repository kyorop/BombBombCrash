#pragma once
namespace BombBombCrash
{
	class ISoundPlayer
	{
	public:
		virtual ~ISoundPlayer(void){}

		virtual int EnableToPlaySound()const = 0;
	};
}


