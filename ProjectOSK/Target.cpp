#include "Target.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "DxLib.h"

Target::Target(void):
	i_to(),
	j_to(),
	rand(),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	hasCalculated(0)
{
}

Target::~Target(void)
{
	delete search;
	delete dijkstra;
}

void Target::DecideGoal(const Enemy &myself)
{
	//初期化
	i_to.clear();
	j_to.clear();

	//目的地の決定
	search->SetGoalInitialized(myself.GetY()/32, myself.GetX()/32, &i_to, &j_to);
	
	//目的地は候補の内から乱数で決める
	rand = GetRand(i_to.size() - 1);
}

void Target::SetRoute(const Enemy &myself)
{
	//初期化
	routeList.clear();

	//最短経路のセット
	dijkstra->SearchShortestPath(myself.GetY()/32, myself.GetX()/32, i_to[rand], j_to[rand], &routeList);
}

int Target::GetRoute(const Enemy &myself)
{
	//if(hasCalculated == 0)	//一度計算したら、一マス移動が終わるまで再計算しない
	//{
	//	int x_center, y_center;
	//	int i_current, j_current;		//呼び出し時にいたマスの成分
	//	
	//	x_center = (myself.GetX() + myself.GetX()+32) / 2;	//キャラの中心座標の計算
	//	y_center = (myself.GetY() + myself.GetY()+32) / 2;
	//	
	//	i_current = y_center / 32;		//中心座標のある位置を今いるマスとする
	//	j_current = x_center / 32;
	//
	//	switch( routeList.empty() ? -1 : routeList.front()  )
	//	{
	//		case UP:
	//			x_next = (j_current + 0) * 32;
	//			y_next = (i_current - 1) * 32;
	//			break;
	//		case DOWN:
	//			x_next = (j_current + 0) * 32;
	//			y_next = (i_current + 1) * 32;
	//			break;
	//		case LEFT:
	//			x_next = (j_current - 1) * 32;
	//			y_next = (i_current + 0) * 32;
	//			break;
	//		case RIGHT:
	//			x_next = (j_current + 1) * 32;
	//			y_next = (i_current + 0) * 32;
	//			break;
	//		default:
	//			break;
	//	}
	//	hasCalculated  = 1;
	//}//end of if block

	////自身が一マス分の移動を終えたら
	//if(myself.GetX() == x_next && myself.GetY() == y_next)
	//{
	//	if(routeList.empty() != 1)
	//	{
	//		routeList.pop_front();
	//	}
	//	hasCalculated = 0;		//次の移動先の座標を再計算
	//}

	//if(routeList.empty() == 1)
	//{
	//	return -1;
	//}
	//else
	//{
	//	return routeList.front();
	//}

	if(hasCalculated == 0)
	{
		//次に進む場所の座標の計算
		int x_center, y_center;
		int i_current, j_current;		//呼び出し時にいたマスの成分
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//キャラの中心座標の計算
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//中心座標のある位置を今いるマスとする
		j_current = x_center / 32;
	
		switch(routeList.empty() ? -1 : routeList.front())
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
			case -1:
				//nowExploring = 0;
				break;
			default:
				break;
		}
		hasCalculated = 1;
	}

	if(myself.GetX() == x_next && myself.GetY() == y_next /*&& nowExploring == 1*/)
	//if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
	{
		//次の目標マスを再計算する
		hasCalculated = 0;

		if(routeList.empty() == 0)
			routeList.pop_front();
	}
	
	
		if(routeList.empty() == 1)
		{
			return -1;		//リストが空なら終了として－１を返す
		}
		else
		{
			return routeList.front();
		}

}