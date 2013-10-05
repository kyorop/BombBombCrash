#include "Search.h"
#include "MapState.h"

#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)

Search::Search(void):
	hasVisited(),
	//i_goal(),
	//j_goal(),
	que_i(),
	que_j(),
	//i_safe(-1),
	//j_safe(-1),
	checkedOtherRow(0),
	checkedOtherLine(0),
	success(0)
{
	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
			hasVisited[i][j] = 0;
	}
}

//void Search::Initialize()
//{
//}

void Search::SetGoalInitialized(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	//初期化。再帰関数なのでその関数中で初期化できないため
	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
			hasVisited[i][j] = 0;
	}

	SetGoal(i , j, i_goal, j_goal);
}

void Search::SetGoal(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	//一度通ったところにまた通らないように通過フラグを立てる
	hasVisited[i][j] = 1;

	//目的地になるか調査
	if(BLOCK(i, 0, j, 0) || BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	{
		i_goal->push_back(i);
		j_goal->push_back(j);
	}

	//通れるところに進む
	if( hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 ) SetGoal(i-1, j, i_goal, j_goal);
	if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) SetGoal(i+1, j, i_goal,  j_goal);
	if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 ) SetGoal(i, j-1, i_goal, j_goal);
	if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) SetGoal(i, j+1, i_goal, j_goal);
}

void Search::CheckAbleToEscapeFromBomb(const int i_start, const int j_start, int *i_safe, int *j_safe)
{
	*i_safe = -1;
	*j_safe = -1;

	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
			hasVisited[i][j] = 0;
	}

	while(que_i.empty() == 0)
	{
		que_i.pop();
	}
	while(que_j.empty() == 0)
	{
		que_j.pop();
	}

	//初期位置をキューに追加
	que_i.push(i_start);
	que_j.push(j_start);
	
	int size;
	int i;
	int j;
	while(*i_safe == -1 || *j_safe == -1)
	{
		size = que_i.size();		//すでに入っていたキューの数だけ更新をする
		for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			//逃げれるかチェック
			if( i != i_start && j != j_start)
			{
				*i_safe = i;
				*j_safe = j;
				break;
			}

			//逃げれないならキューの更新
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

			//検索し終わった不必要なキューの削除
			que_i.pop();
			que_j.pop();
		}
	}

}

int Search::CheckAbleToMoveInitialized(const int i_start, const int j_start)
{
	//初期化。再帰関数なのでその関数中で初期化できないため
	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
			hasVisited[i][j] = 0;
	}
	checkedOtherLine = 0;
	checkedOtherRow = 0;
	success = 0;

	return CheckAbleToMove(i_start, j_start);
}

int Search::CheckAbleToMove(const int i, const int j)
{
	hasVisited[i][j] = 1;
	
	
	if( checkedOtherRow == 1 && checkedOtherLine == 1 )		//移動しても爆風に巻き込まれないなら
	{
		success = 1;
	}

	//通れるところに進む
	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
	{
		checkedOtherRow = 1;
		CheckAbleToMove(i-1, j);
	}
	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
	{
		checkedOtherRow = 1;
		CheckAbleToMove(i+1, j);
	}
	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
	{
		checkedOtherLine = 1;
		CheckAbleToMove(i, j-1);
	}
	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
	{
		checkedOtherLine = 1;
		CheckAbleToMove(i, j+1);
	}

	checkedOtherRow = 0;
	checkedOtherLine = 0;

	return success;
}

Search::~Search(void)
{
}
