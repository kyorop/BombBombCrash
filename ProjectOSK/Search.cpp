#include "Search.h"
#include "MapState.h"
#include "GameConstant.h"
#include <memory.h>
#include <winbase.h>


#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)

Search::Search(void):
	failed(0),
	hasVisited(),
	count(0),
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

void Search::SetGoalInitialized(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	//初期化。再帰関数なのでその関数中で初期化できないため
	for (int row = 0; row < GameConst::MAP_ROW; ++row)
	{
		for (int line = 0; line < GameConst::MAP_LINE; ++line)
			hasVisited[row][line] = 0;
	}
	count = 0;
	failed = 0;
	SetGoal(i , j, i_goal, j_goal);
}
void Search::SetGoal(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	++count;
	//一度通ったところにまた通らないように通過フラグを立てる
	hasVisited[i][j] = 1;

	//目的地になるか調査
	if(BLOCK(i, 0, j, 0) || BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	//if(BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	{
		i_goal->push_back(i);
		j_goal->push_back(j);
	}
	if(count > GameConst::MAP_ROW * GameConst::MAP_LINE)
	{
		failed = 1;
	}

	//通れるところに進む
	if(failed == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 ) SetGoal(i-1, j, i_goal, j_goal);
	if(failed == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) SetGoal(i+1, j, i_goal,  j_goal);
	if(failed == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 ) SetGoal(i, j-1, i_goal, j_goal);
	if(failed == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) SetGoal(i, j+1, i_goal, j_goal);
}

//void Search::CheckAbleToAvoidFromBomb(const int i_start, const int j_start, int *i_safe, int *j_safe)
//{
//	*i_safe = -1;
//	*j_safe = -1;
//
//	for (int i = 0; i < GameConst::MAP_ROW; i++)
//	{
//		for (int j = 0; j < GameConst::MAP_LINE; j++)
//			hasVisited[i][j] = 0;
//	}
//
//	while(que_i.empty() == 0)
//	{
//		que_i.pop();
//	}
//	while(que_j.empty() == 0)
//	{
//		que_j.pop();
//	}
//
//	//初期位置をキューに追加
//	que_i.push(i_start);
//	que_j.push(j_start);
//	
//	int size;
//	int i;
//	int j;
//	while(*i_safe == -1 || *j_safe == -1)
//	{
//		size = que_i.size();		//すでに入っていたキューの数だけ更新をする
//		for(int n=0; n<size; ++n)
//		{
//			i = que_i.front();
//			j = que_j.front();
//
//			//逃げれるかチェック
//			//if( i != i_start && j != j_start)
//			if(MAP(i, 0, j, 0) == 0 && BLOCK(i, 0, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i, j) == NODENGER && MapState::GetInstance()->GetState(i, j, BOMB) == 0)
//			{
//				*i_safe = i;
//				*j_safe = j;
//				break;
//			}
//
//			//逃げれないならキューの更新
//			if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER && MapState::GetInstance()->GetState(i-1, j, BOMB) == 0)
//			{
//				hasVisited[i-1][j] = 1;
//				que_i.push(i-1);
//				que_j.push(j);
//			}
//			if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER && MapState::GetInstance()->GetState(i+1, j, BOMB) == 0)
//			{
//				hasVisited[i+1][j] = 1;
//				que_i.push(i+1);
//				que_j.push(j);
//			}
//			if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER && MapState::GetInstance()->GetState(i, j-1, BOMB) == 0)
//			{
//				hasVisited[i][j-1] = 1;
//				que_i.push(i);
//				que_j.push(j-1);
//			}
//			if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER && MapState::GetInstance()->GetState(i, j+1, BOMB) == 0)
//			{
//				hasVisited[i][j+1] = 1;
//				que_i.push(i);
//				que_j.push(j+1);
//			}
//
//			//検索し終わった不必要なキューの削除
//			que_i.pop();
//			que_j.pop();
//		}
//	}
//
//}

int Search::CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe)
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
	count = 0;

	return CheckAbleToMove(i_start, j_start, i_safe, j_safe);
}
int Search::CheckAbleToMove(const int i, const int j, int *const i_safe, int *const j_safe)
{
	++count;
	hasVisited[i][j] = 1;
		
	//if( checkedOtherRow == 1 && checkedOtherLine == 1 )		//移動しても爆風に巻き込まれないなら
	if(MAP(i, 0, j, 0) == 0 && BLOCK(i, 0, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i, j) == NODENGER && MapState::GetInstance()->GetState(i, j, BOMB) == 0)
	{
		*i_safe = i;
		*j_safe = j;
		success = 1;
	}
	if(count > GameConst::MAP_ROW * GameConst::MAP_LINE)
	{
		success = 1;
	}

	//通れるところに進む
	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
	{
		//checkedOtherRow = 1;
		CheckAbleToMove(i-1, j, i_safe, j_safe);
	}
	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
	{
		//checkedOtherRow = 1;
		CheckAbleToMove(i+1, j, i_safe, j_safe);
	}
	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
	{
		//checkedOtherLine = 1;
		CheckAbleToMove(i, j-1, i_safe, j_safe);
	}
	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
	{
		//checkedOtherLine = 1;
		CheckAbleToMove(i, j+1, i_safe, j_safe);
	}

	//checkedOtherRow = 0;
	//checkedOtherLine = 0;

	return success;
}

void Search::SetEscapeRouteWhenInDanger(int i_start, int j_start, std::list<int> escapeRoute)
{
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
	int goal = 0;

	while(goal == 0)
	{
		size = que_i.size();		//すでに入っていたキューの数だけ更新をする
		for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			if(MAP(i, 0, j, 0) == 0 && BLOCK(i, 0, j, 0) == 0 && MapState::GetInstance()->GetState(i, j, BOMB) == 0 && MapState::GetInstance()->GetDangerState(i, j) == NODENGER)
			{
				goal = 1;
				break;
			}

			//逃げれないならキューの更新
			if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetState(i-1, j, BOMB) == 0)
			{
				escapeRoute.push_back(GameConst::UP);
				hasVisited[i-1][j] = 1;
				que_i.push(i-1);
				que_j.push(j);
			}
			if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetState(i+1, j, BOMB) == 0)
			{
				escapeRoute.push_back(GameConst::DOWN);
				hasVisited[i+1][j] = 1;
				que_i.push(i+1);
				que_j.push(j);
			}
			if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetState(i, j-1, BOMB) == 0)
			{
				escapeRoute.push_back(GameConst::LEFT);
				hasVisited[i][j-1] = 1;
				que_i.push(i);
				que_j.push(j-1);
			}
			if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetState(i, j+1, BOMB) == 0)
			{
				escapeRoute.push_back(GameConst::RIGHT);
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

int Search::OnlyCheckAbleToMove(int i, int j, int i_end, int j_end)
{

	++count;
	hasVisited[i][j] = 1;
	
	if(i == i_end && j == j_end)
	{
		success = 1;
	}
	if(count > GameConst::MAP_ROW * GameConst::MAP_LINE)
	{
		success = 1;
	}

	//通れるところに進む
	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
	{
		OnlyCheckAbleToMove(i-1, j, i_end, j_end);
	}
	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
	{
		OnlyCheckAbleToMove(i+1, j, i_end, j_end);
	}
	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
	{
		OnlyCheckAbleToMove(i, j-1, i_end, j_end);
	}
	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
	{
		OnlyCheckAbleToMove(i, j+1, i_end, j_end);
	}

	return success;
}

void Search::SetEscapeRouteToStop(int i_now, int j_now, std::list<int> escapeRoute)
{

}

int Search::CheckInClosedInterval(int i_now, int j_now)
{
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
	que_i.push(i_now);
	que_j.push(j_now);
	
	int size;
	int i;
	int j;

	//行けるところがなければキューの更新がなくなるので、その時に終了
	while(que_i.empty() == 0)
	{
		size = que_i.size();		//すでに入っていたキューの数だけ更新をする
		for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			//逃げれないならキューの更新
			if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetState(i-1, j, BOMB) == 0)
			{
				hasVisited[i-1][j] = 1;
				que_i.push(i-1);
				que_j.push(j);
			}
			if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetState(i+1, j, BOMB) == 0)
			{
				hasVisited[i+1][j] = 1;
				que_i.push(i+1);
				que_j.push(j);
			}
			if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetState(i, j-1, BOMB) == 0)
			{
				hasVisited[i][j-1] = 1;
				que_i.push(i);
				que_j.push(j-1);
			}
			if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetState(i, j+1, BOMB) == 0)
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

	const int i_start = i_now;
	const int j_start = j_now;
	int i_change = 0;
	int j_change = 0;
	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
		{
			if(hasVisited[i][j] == 2)
			{
				if(i != i_start)
					i_change = 1;
				if(j != j_start)
					j_change = 1;
			}
		}
	}

	if(i_change == 1 && j_change == 1)
		return 0;
	else
		return 1;

}

Search::~Search(void)
{
}
