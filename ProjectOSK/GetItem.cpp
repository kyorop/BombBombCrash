#include "GetItem.h"


GetItem::GetItem(IStateChanger *stateMrg, const Enemy& myself)
	:State(stateMrg, myself)
{
}


GetItem::~GetItem(void)
{
}


void GetItem::ChangeState()
{

}


void GetItem::Analyse()
{
	x_center = (myself.GetX()+myself.GetX()+32)/2;
	y_center = (myself.GetY()+myself.GetY()+32)/2;
	i_center = y_center/32;
	j_center = x_center/32;
	
	if(routeList.empty())
		resetRoute = 1;
	
	ChangeState();
	
	if(resetRoute == 1)
	{
		std::vector<int> i_to, j_to;
		routeList.clear();
		//ルートセット
		if(search->SetGoal(i_center, j_center, &i_to, &j_to) == 1)
		{
			//int rand = GetRand(i_to.size()-1);
			//dijkstra->SearchShortestPath(i_center, j_center, i_to[rand], j_to[rand], &routeList);
			routeList.push_back(GameConst::EnemyAction::BOMBREADY);
			routeList.push_back(GameConst::EnemyAction::BOMBSET);
			resetRoute = 0;
		}
	}
}