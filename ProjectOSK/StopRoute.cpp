#include "StopRoute.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"

StopRoute::StopRoute(void):
	routeList(),
	hasCalculated(0),
	x_next(0),
	y_next(0),
	search(new Search),
	dijkstra(new Dijkstra),
	i_safe(0),
	j_safe(0)
{
}


StopRoute::~StopRoute(void)
{
	delete search;
	delete dijkstra;
}

void StopRoute::DecideGoal(const Enemy &myself)
{
}

void  StopRoute::SetRoute(const Enemy &myself)
{
	//ルートの初期化
	routeList.clear();

	//ストップ
	routeList.push_back(STOP);
}

int StopRoute::GetRoute(const Enemy &myself)
{
	if(routeList.empty() == 0)
		return routeList.front();
	else
		return -1;
}