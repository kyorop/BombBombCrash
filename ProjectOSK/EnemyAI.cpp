#include "EnemyAI.h"
#include "MapState.h"
#include "DxLib.h"
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

#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)

EnemyAI::EnemyAI(void):
	rand(-1),
	success(0),
	hasVisited(),
	visited(),
	checkedOtherRow(0),
	checkedOtherLine(0),
	i_safe(-1),
	j_safe(-1),
	dijkstra(new Dijkstra),
	targetRoute(),
	noDengerRoute(),
	que_i(),
	que_j()
{
	
	for (int i = 0; i < MapState::row; i++)
	{
		for (int j = 0; j < MapState::line; j++)
		{
			this->visited[i][j] = 0;
			hasVisited[i][j] = 0;
		}
	}

}

void EnemyAI::Initialize()
{
	for (int i = 0; i < MapState::row; i++)
	{
		for (int j = 0; j < MapState::line; j++)
		{
			this->visited[i][j] = 0;
			hasVisited[i][j] = 0;
		}
	}
	while(que_i.empty() == 0)
	{
		que_i.pop();
	}

	while(que_j.empty() == 0)
	{
		que_j.pop();
	}

}

void EnemyAI::SetGoal(const int i, const int j)
{
	//��x�ʂ����Ƃ���ɂ܂��ʂ�Ȃ��悤�ɒʉ߃t���O�𗧂Ă�
	visited[i][j] = 1;

	//�ړI�n�ɂȂ邩����
	if(BLOCK(i, 0, j, 0) || BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	{
		i_goal.push_back(i);
		j_goal.push_back(j);
	}

	//�ʂ��Ƃ���ɐi��
	if( visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 ) SetGoal(i-1, j);
	if( visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) SetGoal(i+1, j);
	if( visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 ) SetGoal(i, j-1);
	if( visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) SetGoal(i, j+1);
}


void EnemyAI::CheckAbleToEscapeFromBomb(const int i_start, const int j_start)
{
	//visited[i][j] = 1;
	//
	//if( checkedOtherRow == 1 && checkedOtherLine == 1 )
	//{
	//	i_safe = i;
	//	j_safe = j;
	//	success = 1;
	//}

	////�ʂ��Ƃ���ɐi��
	//if(success == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
	//{
	//	checkedOtherRow = 1;
	//	CheckAbleToEscapeFromBomb(i-1, j);
	//}
	//if( success == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
	//{
	//	checkedOtherRow = 1;
	//	CheckAbleToEscapeFromBomb(i+1, j);
	//}
	//if( success == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
	//{
	//	checkedOtherLine = 1;
	//	CheckAbleToEscapeFromBomb(i, j-1);
	//}
	//if( success == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
	//{
	//	checkedOtherLine = 1;
	//	CheckAbleToEscapeFromBomb(i, j+1);
	//}

	////�ċA�I�ɌĂ΂ꂽ�֐����I��邱�Ƃ͂܂�T���̎����߂����Ƃ��Ӗ�����
	//checkedOtherRow = 0;
	//checkedOtherLine = 0;

	//return success;

	int size;

	int i;
	int j;

	i = i_start;
	j = j_start;

	if(hasVisited[i-1][j] == 0 &&  MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
	{
		hasVisited[i-1][j] = 1;
		que_i.push(i-1);
		que_j.push(j);
	}
	if( hasVisited[i+1][j] == 0 &&  MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
	{
		hasVisited[i+1][j] = 1;
		que_i.push(i+1);
		que_j.push(j);
	}
	if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
	{
		hasVisited[i][j-1] = 1;
		que_i.push(i);
		que_j.push(j-1);
	}
	if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
	{
		hasVisited[i][j+1] = 1;
		que_i.push(i);
		que_j.push(j+1);
	}

	//������邩�`�F�b�N
	/*while(que_i.empty() == 0 && que_j.empty() == 0)
	{
		if(que_i.front() != i_start && que_j.front() != j_start)
		{
			i_safe = que_i.front();
			j_safe = que_j.front();
			break;
		}
		que_i.pop();
		que_j.pop();
	}*/
	
	while(i_safe == -1 || j_safe == -1)
	{
		//�L���[�X�V
		size = que_i.size();
		for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			//������邩�`�F�b�N
			if( i != i_start && j != j_start)
			{
				i_safe = i;
				j_safe = j;
				break;
			}

			//������Ȃ��Ȃ�
			if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
			{
				hasVisited[i-1][j] = 1;
				que_i.push(i-1);
				que_j.push(j);
			}
			if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
			{
				hasVisited[i+1][j] = 1;
				que_i.push(i+1);
				que_j.push(j);
			}
			if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
			{
				hasVisited[i][j-1] = 1;
				que_i.push(i);
				que_j.push(j-1);
			}
			if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
			{
				hasVisited[i][j+1] = 1;
				que_i.push(i);
				que_j.push(j+1);
			}

			que_i.pop();
			que_j.pop();
		}

		//������邩�`�F�b�N
	/*	while(que_i.empty() == 0 && que_j.empty() == 0)
	{
		if(que_i.front() != i_start && que_j.front() != j_start)
		{
			i_safe = que_i.front();
			j_safe = que_j.front();
			break;
		}
		que_i.pop();
		que_j.pop();
	}*/

		/*for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			if( i != i_start && j != j_start)
			{
				i_safe = i;
				j_safe = j;
				break;
			}
			que_i.pop();
			que_j.pop();
		}*/

	}

}


//int EnemyAI::CheckAbleToMove(const int i, const int j)
//{
//	visited[i][j] = 1;
//	
//	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
//	{
//		success = 1;
//	}
//
//	//�ʂ��Ƃ���ɐi��
//	if(success == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
//	{
//		checkedOtherRow = 1;
//		CheckAbleToEscapeFromBomb(i-1, j);
//	}
//	if( success == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
//	{
//		checkedOtherRow = 1;
//		CheckAbleToEscapeFromBomb(i+1, j);
//	}
//	if( success == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
//	{
//		checkedOtherLine = 1;
//		CheckAbleToEscapeFromBomb(i, j-1);
//	}
//	if( success == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
//	{
//		checkedOtherLine = 1;
//		CheckAbleToEscapeFromBomb(i, j+1);
//	}
//
//	checkedOtherRow = 0;
//	checkedOtherLine = 0;
//
//	return success;
//}

void CheckBomb()
{

}

void EnemyAI::Analyse(int i_current, int j_current)
{
	int n = 0;

	//�j�󂷂�ǂ̌���
	i_goal.clear();
	j_goal.clear();
	Initialize();
	SetGoal(i_current, j_current);
	
	//���߂�ꏊ���{����u���Ă����ꏊ�����ׂ�
	n = GetRand(i_goal.size() - 1);
	Initialize();
	//success = 0;
	//checkedOtherRow = 0;
	//checkedOtherLine = 0;
	i_safe = -1;
	j_safe = -1;
	rand = n;
	CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]);
	/*while(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 0)
	{
		rand = GetRand(i_goal.size() - 1);
	}*/
	/*while(1)
	{
		if(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 1)
		{
			
			break;
		}
		n = GetRand(i_goal.size() - 1);

	}*/

	//�j�󂷂�ǂ܂ł̃��[�g�Z�b�g
	route.clear();
	/*success = 0;
	muki = STOP;
	Initialize();
	SetRoute(i_current, j_current, i_goal[n], j_goal[n]);*/
	dijkstra->ResetRoute();
	dijkstra->SearchShortestPath(i_current, j_current, i_goal[n], j_goal[n]);
	
	//�j�󂷂�ǂ���{�������n�܂ł̃��[�g�Z�b�g
	/*route.push_back(BOMBSET);
	route.push_back(BOMBSETOFF);
	Initialize();
	success = 0;
	muki = STOP;
	SetRoute(i_goal[n], j_goal[n], i_safe, j_safe);*/
	dijkstra->SetBombAction(BOMBSET);
	dijkstra->SetBombAction(BOMBSETOFF);
	dijkstra->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe);

	//�A�N�V�������X�g�̍Ō��\��-1
	//route.push_back(-1);
}

int EnemyAI::GetAction(int num)
{
	//if(next == 1)
	//	route.pop_front();
	//if(route.empty() == 1)
	//	return -1;
	//std::list<int>::iterator it = route.begin();
	//return *it;

	//return route[num];

	return dijkstra->GetRoute(num);
}

EnemyAI::~EnemyAI(void)
{
	delete dijkstra;
}
