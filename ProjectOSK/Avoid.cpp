#include "Avoid.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"

Avoid::Avoid(void):
	search(new Search),
	dijkstra(new Dijkstra),
	i_safe(),
	j_safe(),
	routeList()
{
}

Avoid::~Avoid(void)
{
	delete search;
	delete dijkstra;
}

void Avoid::DecideGoal(const Enemy &myself)
{
	search->CheckAbleToAvoidFromBomb(myself.GetY()/32, myself.GetX()/32, &i_safe, &j_safe);
}

void Avoid::SetRoute(const Enemy &myself)
{
	//ルートの初期化
	routeList.clear();

	//最短経路のセット
	dijkstra->SearchShortestPath(myself.GetY()/32, myself.GetX()/32, i_safe, j_safe, &routeList);
}

int Avoid::GetRoute(const Enemy &myself)
{
	if(hasCalculated == 0)	//一度計算したら、一マス移動が終わるまで再計算しない
	{
		int x_center, y_center;
		int i_current, j_current;		//呼び出し時にいたマスの成分
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//キャラの中心座標の計算
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//中心座標のある位置を今いるマスとする
		j_current = x_center / 32;
	
		switch( routeList.front() )
		{
			case UP:
				x_next = (j_current + 0) * 32;
				y_next = (i_current - 1) * 32;
				break;
			case DOWN:
				x_next = (j_current + 0) * 32;
				y_next = (i_current + 1) * 32;
				break;
			case LEFT:
				x_next = (j_current - 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
			case RIGHT:
				x_next = (j_current + 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
		}
		hasCalculated  = 1;
	}//end of if block

	if(myself.GetX() == x_next && myself.GetY() == y_next)
	{
		routeList.pop_front();
		hasCalculated = 0;
	}

	if(routeList.empty() == 1)
	{
		return -1;
	}
	else
		return routeList.front();
}