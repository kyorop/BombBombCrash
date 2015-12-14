#pragma once

namespace BombBombCrash
{
	class IRegister
	{
	public:
		virtual ~IRegister(void){};
		virtual void Register() = 0;
	};
}




