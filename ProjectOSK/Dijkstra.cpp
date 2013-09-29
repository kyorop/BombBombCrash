#include "Dijkstra.h"
#include "Node.h"
#include "MapState.h"
#include "Graph.h"
#include <climits>

const int Dijkstra::ud[4] = {-1,1,0,0};
const int Dijkstra::lr[4] = {0,0,-1,1};

Dijkstra::Dijkstra(int nodeNum):
	i_currentNode(),
	j_currentNode(),
	graph(new Graph),
	vecRoute()
{
}

void Dijkstra::SearchShortestPath(int i_goal, int j_goal, int i_start, int j_start)
{
	//全ノードの初期化
	graph->Initialize();

	//スタートノードの初期化
	graph->GetNode(i_goal, j_goal)->SetCost(0);
	graph->GetNode(i_goal, j_goal)->SettleShortestPath();
	i_currentNode = i_goal;
	j_currentNode = j_goal;

	while(graph->GetNode(i_start, j_start)->GetSettled() == 0)
	{
		//最小コストの更新
		int costSum;	//基点ノードのminCostとそこまでのコストの和
		for(int n=0; n<4; ++n)
		{
			costSum = graph->GetNode(i_currentNode+ud[n], j_currentNode+lr[n])->GetCost() + cost ;

			if(MapState::GetInstance()->GetState(i_currentNode+ud[n], j_currentNode+lr[n], BLOCK) == 0
				&& MapState::GetInstance()->GetState(i_currentNode+ud[n], j_currentNode+lr[n], MAP) == 0
				&& costSum < graph->GetNode(i_currentNode+ud[n], j_currentNode+lr[n])->GetCost())
			{
				graph->GetNode(i_currentNode+ud[n], j_currentNode+lr[n])->SetCost(costSum);
				graph->GetNode(i_currentNode+ud[n], j_currentNode+lr[n])->SetPreNode(i_currentNode, j_currentNode);
				graph->GetNode(i_currentNode+ud[n], j_currentNode+lr[n])->SettleShortestPath();
			}
		}

		//次の基点ノードを決める
		int min = INT_MAX;
		for (int i = 0; i < MAPSIZE_Y; i++)
		{
			for (int j = 0; j < MAPSIZE_X; j++)
			{
				if(graph->GetNode(i,j)->GetSettled() == 0 && min > graph->GetNode(i,j)->GetCost())
				{
					min = graph->GetNode(i,j)->GetCost();
					i_currentNode = i;
					j_currentNode = j;
				}
			}
		}
	}//end of while loop

}

void Dijkstra::SetRoute()
{
	vecRoute.clear();

	
}

Dijkstra::~Dijkstra(void)
{
	delete graph;
}
