#pragma once
#include <list>
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "IStateChanger.h"


namespace BombBombCrash
{
	class Enemy;
	class State
	{
	protected:
		enum
		{
			END = -1,
			STOP,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			BOMBSET,
			BOMBSETOFF,
		};
		static const int scoutingRadius_character = 8;
		static const int scoutingRadius_item = 8;
		static const int scoutingRadius_block = 5;
	protected:
		IStateChanger*const stateMrg;
		std::list<int> routeList;
		Search *const search;
		Dijkstra *const dijkstra;
		const Enemy& myself;
		int x_center;
		int y_center;
		int i_center;
		int j_center;
		int x_next;
		int y_next;
		int resetRoute;
		int currentAction;
		int resetCalc;
	protected:
		//指定した対象が指定した半径にあり、かつそこへ行けるなら１を返す
		int CheckAroundMyself(int i_now, int j_now, int TRAGET, int radius);
		int CheckObjectAroundAndAbleToGoThere(int i_now, int j_now, int* i_to, int* j_to, int OBJECT, int radius);
		virtual void ChangeState() = 0;
		void ChangeStateBase();
		void UpdateCoordinate();
	public:
		State(IStateChanger *stateMrg, const Enemy &myself);
		virtual ~State(void);
		virtual void Analyse() = 0;
		virtual int GetRoute();
	};
}




