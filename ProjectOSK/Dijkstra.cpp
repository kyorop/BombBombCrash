#include "Dijkstra.h"
#include "MapState.h"
#include "DangerState.h"
#include "Graph.h"
#include "GameConstant.h"
#include <climits>
//enum
//{
//	STOP,
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN,
//	BOMBSET,
//	BOMBSETOFF,
//};

using namespace BombBombCrash;

const int Dijkstra::ud[4] = {-1,1,0,0};
const int Dijkstra::lr[4] = {0,0,-1,1};

Dijkstra::Dijkstra()
	:i_currentNode(),
	j_currentNode(),
	graph(new Graph)
{
}

void Dijkstra::SearchShortestPath(int i_start, int j_start, int i_goal, int j_goal, std::list<int> *shortestRoute)
{
	//全ノードの初期化
	graph->Initialize();

	//スタートノードでのファーストステップ
	graph->SetCost(i_goal, j_goal, 0);
	graph->SettleShortestPath(i_goal, j_goal);
	i_currentNode = i_goal;
	j_currentNode = j_goal;

	while(graph->GetSettled(i_start, j_start) == 0)
	{
		//最小コストの更新
		int costSum;	//基点ノードのminCostとそこまでのコストの和
		int i_next;
		int j_next;
		for(int n=0; n<4; ++n)
		{
			i_next = i_currentNode + ud[n];
			j_next = j_currentNode + lr[n];
			costSum = graph->GetCost(i_currentNode, j_currentNode) + edgeCost ;

			//繋がっているノードの検索
			if(MapState::GetInstance()->GetState(i_next, j_next, MapState::BLOCK) == 0
				&& MapState::GetInstance()->GetState(i_next, j_next, MapState::MAP) == 0
				&& MapState::GetInstance()->GetState(i_next, j_next, MapState::BOMB) == 0
				&& DangerState::GetInstance()->GetDangerState(i_next, j_next) == 0
				&& DangerState::GetInstance()->GetFireState(i_next, j_next) == 0)
			{
				//基点ノードの最小コストと探索ノードまでのコストを足したものが探索ノードの最小コストより小さいなら
				if(costSum < graph->GetCost(i_next, j_next) )
				{
					graph->SetCost(i_next, j_next, costSum);
					//graph->SetPreNode(i_currentNode, j_currentNode, i_next, j_next);
					graph->SetPreNode(i_next, j_next, i_currentNode, j_currentNode);
					//graph->SettleShortestPath(i_next, j_next);
				}
			}
		}

		//次の基点ノードを決める
		int min = INT_MAX;
		for (int i = 0; i < MAPSIZE_Y; ++i)
		{
			for (int j = 0; j < MAPSIZE_X; ++j)
			{
				if(MapState::GetInstance()->GetState(i, j, MapState::BLOCK) == 0
					&& MapState::GetInstance()->GetState(i, j, MapState::MAP) == 0
					&& MapState::GetInstance()->GetState(i, j, MapState::BOMB) == 0
					&& DangerState::GetInstance()->GetDangerState(i, j) == 0
					&& DangerState::GetInstance()->GetFireState(i, j) == 0
					&& graph->GetSettled(i, j) == 0 
					&& min > graph->GetCost(i, j) )
				{
					min = graph->GetCost(i, j);
					i_currentNode = i;
					j_currentNode = j;
				}
			}
		}
		graph->SettleShortestPath(i_currentNode, j_currentNode);
	}//end of while loop

	//SetRoute( i_goal, j_goal, i_start, j_start);
	SetRoute(i_start, j_start, i_goal, j_goal, shortestRoute);
}

void Dijkstra::SetRoute(int i_start, int j_start, int i_goal, int j_goal, std::list<int> *shortestRoute)
{
	int i_now = i_start;
	int j_now = j_start;
	
	while( !(i_now == i_goal && j_now == j_goal) )
	{
		if(i_now > graph->GetPreNode_i(i_now, j_now) && j_now == graph->GetPreNode_j(i_now, j_now))
		{
			shortestRoute->push_back(GameConst::EnemyAction::UP);
			i_now = graph->GetPreNode_i(i_now, j_now);
		}
		else if(i_now < graph->GetPreNode_i(i_now, j_now) && j_now == graph->GetPreNode_j(i_now, j_now))
		{
			shortestRoute->push_back(GameConst::EnemyAction::DOWN);
			i_now = graph->GetPreNode_i(i_now, j_now);
		}
		else if(i_now == graph->GetPreNode_i(i_now, j_now) && j_now > graph->GetPreNode_j(i_now, j_now))
		{
			shortestRoute->push_back(GameConst::EnemyAction::LEFT);
			j_now = graph->GetPreNode_j(i_now, j_now);
		}
		else if(i_now == graph->GetPreNode_i(i_now, j_now) && j_now < graph->GetPreNode_j(i_now, j_now))
		{
			shortestRoute->push_back(GameConst::EnemyAction::RIGHT);
			j_now = graph->GetPreNode_j(i_now, j_now);
		}
	}
}

Dijkstra::~Dijkstra(void)
{
	delete graph;
}
