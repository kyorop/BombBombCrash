#pragma once
#include <list>

namespace BombBombCrash
{
	class Enemy;
	class Route
	{
	public:
		int myclass;
		//virtual void Analyse() = 0;
		virtual void DecideGoal(const Enemy &myself) = 0;
		virtual void SetRoute(const Enemy &myself) = 0;
		//virtual void Enter() = 0;
		//virtual void Execute() = 0;
		virtual int GetRoute(const Enemy &myself) = 0;
		virtual ~Route(void){}
	};
}




