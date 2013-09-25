#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#define MV 1
#define HABA 10
#define ROW 13
#define LINE 17
enum object
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};
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
#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)



Enemy::Enemy(int x, int y)
{
	this->mv = MV;
	this->flag = TRUE;
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = x;
	this->y = y;
	this->resetRoutine = 1;
	this->muki = STOP;
	this->bombSet = 0;
	this->actionloop = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < LINE; j++)
		{
			this->visited[i][j] = 0;
		}
	}
}


Enemy::~Enemy(void)
{
}

void Enemy::SetGoal(const int i, const int j)
{
	//一度通ったところにまた通らないように通過フラグを立てる
	visited[i][j] = 1;

	//目的地になるか調査
	if(BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
		vecGoal.push_back(new Component(i,  j));

	//通れるところに進む
	if( visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 ) SetGoal(i-1, j);
	if( visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) SetGoal(i+1, j);
	if( visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 ) SetGoal(i, j-1);
	if( visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) SetGoal(i, j+1);

}

void Enemy::DeleteComponent()
{
	std::vector<Component*>::iterator itBranch = vecBranch.begin();
	for(itBranch ; itBranch != vecBranch.end(); ++itBranch)
		delete *itBranch;

	std::vector<Component*>::iterator itGoal = vecGoal.begin();
	for(itGoal; itGoal != vecGoal.end(); ++itGoal)
		delete *itGoal;
}

void Enemy::Analyse()
{
	if(this->resetRoutine == 1)
	{
	//	int charaX, charaY;
	//	for(int i=0; i<ROW; ++i)
	//	{
	//		for(int j=0; j<LINE; ++j)
	//		{
	//			MapState::GetInstance()->GetState(i, j, CHARACTOR) == 1;
	//			charaX = 32 * j;
	//			charaY = 32 * i;
	//		}
	//	}
		
		//if(MapState::GetInstance()->GetState(this->y/32-1,this->x/32, BLOCK) == 0 && MapState::GetInstance()->GetState(this->y/32,this->x/32-1, BLOCK) == 0 )
		//{
		//	action[0] = LEFT;
		//	action[1] = BOMBSET;
		//	action[2] = RIGHT;
		//	action[3] = UP;
		//	action[4] = STOP;
		//}


			if(BLOCK(this->y,0,this->x,0) == 0)
			{
				if(BLOCK(this->y,-1,this->x,0) == 1 || BLOCK(this->y,1,this->x,0) == 1 || BLOCK(this->y,0,this->x,-1) == 1 || BLOCK(this->y,0,this->x,1) == 1)
				{
					this->bombSet = 1;
				}
			}
		
		//マスの上下左右を調べる
		if(BLOCK(this->y,0,this->x,0) == 0)
		{
			for(int i=-1; i<=1; i+=2)//-1と1をチェック
			{
				for(int j=-1; j<=1; j+=2)//-1と1をチェック
				{
					if(BLOCK(y,i,x,j) == 0)
					{
						
					}
				}
			}
		}
		//for(int k=-1; k<2; ++k)
		//{
		//		if( MapState::GetInstance()->GetState(this->y/32,this->x/32+k, BLOCK) == 0 && MapState::GetInstance()->GetState(this->x/32+k,this->y/32, MAP) == 0)
		//		{
		//			if(k == 1)
		//			{
		//				this->muki = RIGHT;
		//				break;
		//			}
		//			else if(k == -1)
		//			{
		//				this->muki = LEFT;
		//				break;
		//			}
		//		}
		//		else
		//		{
		//			this->muki = STOP;
		//		}
		//}
		//for(int k=-1; k<2; ++k)
		//{
		//	if( MapState::GetInstance()->GetState(this->y/32+k, this->x/32, BLOCK) == 0 && MapState::GetInstance()->GetState(this->y/32+k, this->x/32, MAP) == 0)
		//	{
		//		if(k == 1)
		//		{
		//			this->muki = DOWN;
		//			break;
		//		}
		//		else if(k == -1)
		//		{
		//			this->muki = UP;
		//			break;
		//		}
		//	}
		//	else
		//		this->muki = STOP;
		//	}
		this->resetRoutine = 0;


		if(MAP(y,-1,x,0) == 0)
		{
			if(BLOCK(y,-1,x,0) == 0)
			{
				if(BLOCK(y,0,x,-2) == 0)
				{
					
				}
			}
			else
			{

			}
		}
	}
}

int Enemy::CheckAbleBombSet()
{
	return 0;
}

void Enemy::Move(int g_lastTime)
{
	if(this->resetRoutine == 0)
	{
		switch(this->action[this->actionloop])
		{
		case STOP:break;
		case UP:		this->muki=UP;		this->y -= this->mv;break;
		case DOWN:this->muki=DOWN;this->y += this->mv;break;
		case LEFT:	this->muki=LEFT;	this->x -= this->mv;break;
		case RIGHT:this->muki=RIGHT;	this->x += this->mv;break;
		case BOMBSET:this->bombSet = 1;
		case BOMBSETOFF:this->bombSet = 0;
		}
		
		if(this->x % 32 == 0 && this->y % 32 == 0)
		{
			this->muki = STOP;
			//this->resetRoutine = 1;
			++this->actionloop;
			if(this->actionloop == 5)
				this->resetRoutine = 1;
		}
	}
		
	if(this->x < 64)this->x = 64;
	if(this->x > 32*14)this->x = 32*14;
	if(this->y < 32)this->y = 32;
	if(this->y > 32*11)this->y = 32*11;

	this->animpat = (g_lastTime / (1000 / 12)) % 4;
}

void Enemy::Draw(void)
{
	switch(this->muki)
	{
	case STOP:
		DrawGraph(this->x, this->y, this->graph[4], TRUE);break;
	case LEFT:
		DrawGraph(this->x, this->y, this->graph[animpat+8], TRUE);break;
	case RIGHT:
		DrawGraph(this->x, this->y, this->graph[animpat+12], TRUE);break;
	case UP:
		DrawGraph(this->x, this->y, this->graph[animpat+0], TRUE);break;
	case DOWN:
		DrawGraph(this->x, this->y, this->graph[animpat+4], TRUE);	break;
	}
}


int Enemy::GetBombSet(void)const
{
	return this->bombSet;
}

