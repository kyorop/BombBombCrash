#include "Search.h"
#include "MapState.h"
#include "GameConstant.h"
#include "DangerState.h"
#include <stack>
#include <cstring>

using namespace BombBombCrash;

#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MapState::BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MapState::MAP)

Search::Search(void):
	failed(0),
	hasVisited(),
	count(0),
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

int Search::SetGoal(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	success = 0;

	memset(hasVisited[0], 0, sizeof(int)*GameConst::MAP_ROW*GameConst::MAP_LINE);

	//ブロックがあるかチェック
	int blockNum = 0;
	for (int row = 0; row < GameConst::MAP_ROW; ++row)
	{
		for (int line = 0; line < GameConst::MAP_LINE; ++line)
		{
			if(MapState::GetInstance()->GetState(row, line, MapState::BLOCK) == 1)
				++blockNum;
		}
	}
	if(blockNum == 0)
		return 0;

	return SetGoal_base(i , j, i_goal, j_goal);
}

int Search::SetGoal_base(const int i, const int j, std::vector<int> *i_goal, std::vector<int> *j_goal)
{
	//一度通ったところにまた通らないように通過フラグを立てる
	hasVisited[i][j] = 1;

	//目的地になるか調査
	if(MapState::GetInstance()->GetState(i-1, j, MapState::BLOCK) == 1
		|| MapState::GetInstance()->GetState(i+1, j, MapState::BLOCK) == 1
		|| MapState::GetInstance()->GetState(i, j-1, MapState::BLOCK) == 1
		|| MapState::GetInstance()->GetState(i, j+1, MapState::BLOCK) == 1)
	{
		i_goal->push_back(i);
		j_goal->push_back(j);
		success = 1;
	}

	//通れるところに進む
	if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetState(i-1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i-1, j) == 0 && DangerState::GetInstance()->GetFireState(i-1, j) == 0) SetGoal_base(i-1, j, i_goal, j_goal);
	if(hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetState(i+1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i+1, j) == 0 && DangerState::GetInstance()->GetFireState(i+1, j) == 0) SetGoal_base(i+1, j, i_goal,  j_goal);
	if(hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetState(i, j-1,MapState:: BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i, j-1) == 0 && DangerState::GetInstance()->GetFireState(i, j-1) == 0) SetGoal_base(i, j-1, i_goal, j_goal);
	if(hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetState(i, j+1, MapState::BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i, j+1) == 0 && DangerState::GetInstance()->GetFireState(i, j+1) == 0) SetGoal_base(i, j+1, i_goal, j_goal);

	return success;
}

//int Search::CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe)
//{
//	//初期化。再帰関数なのでその関数中で初期化できないため
//	//for (int i = 0; i < GameConst::MAP_ROW; i++)
//	//{
//	//	for (int j = 0; j < GameConst::MAP_LINE; j++)
//	//		hasVisited[i][j] = 0;
//	//}
//	memset(hasVisited[0], 0, sizeof(int)*GameConst::MAP_LINE);
//	success = 0;
//
//	return CheckAbleToMove(i_start, j_start, i_safe, j_safe);
//}

//int Search::CheckAbleToMove(const int i, const int j, int *const i_safe, int *const j_safe)
//{
//	//移動しても爆風に巻き込まれないなら
//	if(MAP(i, 0, j, 0) == 0 && BLOCK(i, 0, j, 0) == 0 && MapState::GetInstance()->GetState(i, j, BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i, j) == 0)
//	{
//		*i_safe = i;
//		*j_safe = j;
//		success = 1;
//	}
//
//	//通れるところに進む
//	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
//	{
//		CheckAbleToMove(i-1, j, i_safe, j_safe);
//	}
//	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
//	{
//		CheckAbleToMove(i+1, j, i_safe, j_safe);
//	}
//	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
//	{
//		CheckAbleToMove(i, j-1, i_safe, j_safe);
//	}
//	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
//	{
//		CheckAbleToMove(i, j+1, i_safe, j_safe);
//	}
//
//	return success;
//}

int Search::SetEscapeRouteWhenInDanger(int i_start, int j_start, std::list<int> *escapeRoute)
{
	std::queue<int> que_i;
	std::queue<int> que_j;
	int visited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	//どうやってそこに着いたか
	int pred[GameConst::MAP_ROW][GameConst::MAP_LINE];

	memset(visited[0], 0, sizeof(int)*GameConst::MAP_ROW*GameConst::MAP_LINE);
	memset(pred[0], 0, sizeof(int)*GameConst::MAP_ROW*GameConst::MAP_LINE);

	//スタートノードの初期化
	visited[i_start][j_start] = 1;
	pred[i_start][j_start] = -1;

	//初期位置をキューに追加
	que_i.push(i_start);
	que_j.push(j_start);
	
	int i;
	int j;
	int i_goal = -1;
	int j_goal = -1;
	success = 0;

	while(que_i.empty() == 0)
	{
			i = que_i.front();
			j = que_j.front();

			if( !(i == i_start && j == j_start) )
			{
				if(MAP(i, 0, j, 0) == 0 && BLOCK(i, 0, j, 0) == 0 && MapState::GetInstance()->GetState(i, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetDangerState(i, j) == 0)
				{
					visited[i][j] = 1;
					i_goal = i;
					j_goal = j;
					success = 1;
					break;
				}
			}

			//逃げれないならキューの更新
			if(visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetState(i-1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i-1, j) == 0/* && MapState::GetInstance()->GetState(i-1, j, FIRE) == 0*/)
			{
				visited[i-1][j] = 1;
				pred[i-1][j] = GameConst::EnemyAction::UP;//ここまでUPして来た
				que_i.push(i-1);
				que_j.push(j);
			}
			if(visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetState(i+1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i+1, j) == 0/* && MapState::GetInstance()->GetState(i+1, j, FIRE) == 0*/)
			{
				visited[i+1][j] = 1;
				pred[i+1][j] = GameConst::EnemyAction::DOWN;//ここまでDOWNしてきた
				que_i.push(i+1);
				que_j.push(j);
			}
			if(visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetState(i, j-1, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i, j-1) == 0/* && MapState::GetInstance()->GetState(i, j-1, FIRE) == 0*/)
			{
				visited[i][j-1] = 1;
				pred[i][j-1] = GameConst::EnemyAction::LEFT;//ここまでLEFTして来た
				que_i.push(i);
				que_j.push(j-1);
			}
			if(visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetState(i, j+1, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i, j+1) == 0/* && MapState::GetInstance()->GetState(i, j+1, FIRE) == 0*/)
			{
				visited[i][j+1] = 1;
				pred[i][j+1] = GameConst::EnemyAction::RIGHT;//ここまでRIGHTして来た
				que_i.push(i);
				que_j.push(j+1);
			}

			//検索し終わった不必要なキューの削除
			que_i.pop();
			que_j.pop();
	}

	if(i_goal != -1 && j_goal != -1)
	{
		int i_current = i_goal;
		int j_current = j_goal;
		
		while(pred[i_current][j_current] != -1)		//-1は自分のいるところ
		{
			switch(pred[i_current][j_current])
			{
			case GameConst::EnemyAction::UP:
				escapeRoute->push_front(GameConst::EnemyAction::UP);
				i_current += 1;
				break;
			case GameConst::EnemyAction::DOWN:
				escapeRoute->push_front(GameConst::EnemyAction::DOWN);
				i_current -= 1;
				break;
			case GameConst::EnemyAction::LEFT:
				escapeRoute->push_front(GameConst::EnemyAction::LEFT);
				j_current += 1;
				break;
			case GameConst::EnemyAction::RIGHT:
				escapeRoute->push_front(GameConst::EnemyAction::RIGHT);
				j_current -= 1;
				break;
			}
		}
	}

	return success;
}

//int Search::OnlyCheckAbleToMove(int i, int j, int i_end, int j_end)
//{
//
//	++count;
//	hasVisited[i][j] = 1;
//	
//	if(i == i_end && j == j_end)
//	{
//		success = 1;
//	}
//	if(count > GameConst::MAP_ROW * GameConst::MAP_LINE)
//	{
//		success = 1;
//	}
//
//	//通れるところに進む
//	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
//	{
//		OnlyCheckAbleToMove(i-1, j, i_end, j_end);
//	}
//	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
//	{
//		OnlyCheckAbleToMove(i+1, j, i_end, j_end);
//	}
//	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
//	{
//		OnlyCheckAbleToMove(i, j-1, i_end, j_end);
//	}
//	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
//	{
//		OnlyCheckAbleToMove(i, j+1, i_end, j_end);
//	}
//
//	return success;
//}

void Search::SetEscapeRouteToStop(int i_now, int j_now, std::list<int> escapeRoute)
{
}

int Search::CheckInClosedInterval(int i_now, int j_now)
{
	std::queue<int> que_i;
	std::queue<int> que_j;
	int visited[GameConst::MAP_ROW][GameConst::MAP_LINE];

	memset(visited[0], 0, sizeof(int)*GameConst::MAP_ROW*GameConst::MAP_LINE);

	//初期位置をキューに追加
	que_i.push(i_now);
	que_j.push(j_now);
	
	int i;
	int j;

	//行けるところがなければキューの更新がなくなるので、その時に終了
	while(que_i.empty() == 0)
	{
		//size = que_i.size();		//すでに入っていたキューの数だけ更新をする
		//for(int n=0; n<size; ++n)

		i = que_i.front();
		j = que_j.front();

		//逃げれないならキューの更新
		if(visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetState(i-1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i-1, j) == 0 && DangerState::GetInstance()->GetDangerState(i-1, j) == 0)
		{
			visited[i-1][j] = 1;
			que_i.push(i-1);
			que_j.push(j);
		}
		if(visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetState(i+1, j, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i+1, j) == 0 && DangerState::GetInstance()->GetDangerState(i+1, j) == 0)
		{
			visited[i+1][j] = 1;
			que_i.push(i+1);
			que_j.push(j);
		}
		if(visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetState(i, j-1, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i, j-1) == 0 && DangerState::GetInstance()->GetDangerState(i, j-1) == 0)
		{
			visited[i][j-1] = 1;
			que_i.push(i);
			que_j.push(j-1);
		}
		if(visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetState(i, j+1, MapState::BOMB) == 0 && DangerState::GetInstance()->GetFireState(i, j+1) == 0 && DangerState::GetInstance()->GetDangerState(i, j+1) == 0)
		{
			visited[i][j+1] = 1;
			que_i.push(i);
			que_j.push(j+1);
		}

		//検索し終わった不必要なキューの削除
		que_i.pop();
		que_j.pop();
	}

	const int i_start = i_now;
	const int j_start = j_now;
	int i_change = 0;
	int j_change = 0;
	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
		{
			if(visited[i][j] == 1)
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

int Search::CheckAbleToGoTo(int i_start, int j_start, int i_goal, int j_goal)
{
	//初期化
	success = 0;
	memset(hasVisited[0], 0, sizeof(int)*GameConst::MAP_ROW*GameConst::MAP_LINE);

	return CheckAbleToGoTo_base(i_start, j_start, i_goal, j_goal);
}

int Search::CheckAbleToGoTo_base(const int i, const int j, const int i_goal, const int j_goal)
{
	//一度通ったところにまた通らないように通過フラグを立てる
	hasVisited[i][j] = 1;

	//目的地についたら
	if(i == i_goal && j == j_goal)
		success = 1;

	//通れるところに進む
	if(success == 0 && hasVisited[i-1][j] == 0 && CheckAbleToPass(i-1, j) == 1) CheckAbleToGoTo_base(i-1, j, i_goal, j_goal);
	if(success == 0 && hasVisited[i+1][j] == 0 && CheckAbleToPass(i+1, j) == 1) CheckAbleToGoTo_base(i+1, j, i_goal, j_goal);
	if(success == 0 && hasVisited[i][j-1] == 0 && CheckAbleToPass(i, j-1) == 1) CheckAbleToGoTo_base(i, j-1, i_goal, j_goal);
	if(success == 0 && hasVisited[i][j+1] == 0 && CheckAbleToPass(i, j+1) == 1)CheckAbleToGoTo_base(i, j+1, i_goal, j_goal);

	return success;
}

int Search::CheckAbleToPass(int i, int j)
{
	//ダイクストラが考慮する障害物と同じにしなければならない
	if(MapState::GetInstance()->GetState(i, j, MapState::MAP) == 0
		&& MapState::GetInstance()->GetState(i, j, MapState::BLOCK) == 0
		&& MapState::GetInstance()->GetState(i, j, MapState::BOMB) == 0 
		&& DangerState::GetInstance()->GetDangerState(i, j) == 0 
		&& DangerState::GetInstance()->GetFireState(i, j) == 0 
		)
	{
		return 1;
	}
	else
		return 0;
}