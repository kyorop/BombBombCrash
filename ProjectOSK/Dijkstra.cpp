#include "Dijkstra.h"
#include "MapState.h"
#include "Graph.h"
#include "DxLib.h"
#include <climits>
enum
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BOMBSET,
	BOMBSETOFF,
};

const int Dijkstra::ud[4] = {-1,1,0,0};
const int Dijkstra::lr[4] = {0,0,-1,1};

Dijkstra::Dijkstra():
	i_currentNode(),
	j_currentNode(),
	graph(new Graph),
	vecRoute()
{
}

void Dijkstra::ResetRoute()
{
	vecRoute.clear();
}

void Dijkstra::SearchShortestPath(int i_start, int j_start, int i_goal, int j_goal)
{
	//�S�m�[�h�̏�����
	graph->Initialize();

	//�X�^�[�g�m�[�h�ł̃t�@�[�X�g�X�e�b�v
	graph->SetCost(i_goal, j_goal, 0);
	graph->SettleShortestPath(i_goal, j_goal);
	i_currentNode = i_goal;
	j_currentNode = j_goal;

	while(graph->GetSettled(i_start, j_start) == 0)
	{
		//�ŏ��R�X�g�̍X�V
		int costSum;	//��_�m�[�h��minCost�Ƃ����܂ł̃R�X�g�̘a
		int i_next;
		int j_next;
		for(int n=0; n<4; ++n)
		{
			i_next = i_currentNode + ud[n];
			j_next = j_currentNode + lr[n];
			costSum = graph->GetCost(i_currentNode, j_currentNode) + edgeCost ;

			//�q�����Ă���m�[�h�̌���
			if(MapState::GetInstance()->GetState(i_next, j_next, BLOCK) == 0
				&& MapState::GetInstance()->GetState(i_next, j_next, MAP) == 0)
			{
				//��_�m�[�h�̍ŏ��R�X�g�ƒT���m�[�h�܂ł̃R�X�g�𑫂������̂��T���m�[�h�̍ŏ��R�X�g��菬�����Ȃ�
				if(costSum < graph->GetCost(i_next, j_next) )
				{
					graph->SetCost(i_next, j_next, costSum);
					//graph->SetPreNode(i_currentNode, j_currentNode, i_next, j_next);
					graph->SetPreNode(i_next, j_next, i_currentNode, j_currentNode);
					//graph->SettleShortestPath(i_next, j_next);
				}
			}
		}

		//���̊�_�m�[�h�����߂�
		int min = INT_MAX;
		for (int i = 0; i < MAPSIZE_Y; ++i)
		{
			for (int j = 0; j < MAPSIZE_X; ++j)
			{
				if(MapState::GetInstance()->GetState(i, j, BLOCK) == 0
					&& MapState::GetInstance()->GetState(i, j, MAP) == 0
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
	SetRoute(i_start, j_start, i_goal, j_goal);
}

void Dijkstra::SetRoute(int i_start, int j_start, int i_goal, int j_goal)
{
	int i_now = i_start;
	int j_now = j_start;
	
	while( !(i_now == i_goal && j_now == j_goal) )
	{
		if(i_now > graph->GetPreNode_i(i_now, j_now) && j_now == graph->GetPreNode_j(i_now, j_now))
		{
			vecRoute.push_back(UP);
			i_now = graph->GetPreNode_i(i_now, j_now);
		}
		else if(i_now < graph->GetPreNode_i(i_now, j_now) && j_now == graph->GetPreNode_j(i_now, j_now))
		{
			vecRoute.push_back(DOWN);
			i_now = graph->GetPreNode_i(i_now, j_now);
		}
		else if(i_now == graph->GetPreNode_i(i_now, j_now) && j_now > graph->GetPreNode_j(i_now, j_now))
		{
			vecRoute.push_back(LEFT);
			j_now = graph->GetPreNode_j(i_now, j_now);
		}
		else if(i_now == graph->GetPreNode_i(i_now, j_now) && j_now < graph->GetPreNode_j(i_now, j_now))
		{
			vecRoute.push_back(RIGHT);
			j_now = graph->GetPreNode_j(i_now, j_now);
		}
	}
}

int Dijkstra::GetRoute(int num)const
{
	int size = vecRoute.size();

	//�z����I�[�o�[�����烋�[�g�I����m�点��
	if(num >= size)
		return -1;
	
		return vecRoute[num];
}

void Dijkstra::SetBombAction(int bombState)
{
	vecRoute.push_back(bombState);
}

Dijkstra::~Dijkstra(void)
{
	delete graph;
}