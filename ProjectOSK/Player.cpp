#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "DxLib.h"
#define MV 1
#define HABA 0
#define DHIT 5
enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOHIT,
};

Player::Player()
{
	LoadDivGraph("bombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = 32*2;
	this->rx = this->x+32;
	this->y = 32*1;
	this->dy = this->y+32;
	this->muki = DOWN;
	this->flag =1;
}

void Player::Draw(Map &map, int g_lasttime)
{
	if(CheckHitKey(KEY_INPUT_Q) == 1)
	{
		this->x = 32*2;
		this->y = 32*1;
		this->muki = DOWN;
		this->flag = 1;
	}
	if(CheckHitKey(KEY_INPUT_W) == 1)
	{
		this->x = 32*14;
		this->y = 32*1;
		this->muki = DOWN;
	}
	if(CheckHitKey(KEY_INPUT_E) == 1)
	{
		this->x = 32*2;
		this->y = 32*11;
		this->muki = DOWN;
	}
	if(CheckHitKey(KEY_INPUT_R) == 1)
	{
		this->x = 32*14;
		this->y = 32*11;
		this->muki = DOWN;
	}
	if(CheckHitKey(KEY_INPUT_X) == 1)
	{
		this->x = 32*10;
		this->y = 32*10;
		this->muki = DOWN;
	}

	if(this->x < 64)this->x = 64;
	if(this->x > 32*14)this->x = 32*14;
	if(this->y < 32)this->y = 32;
	if(this->y > 32*11)this->y = 32*11;

	int animpat = (g_lasttime / (1000 / 12)) % 4;
	if(this->flag == 1)
	{
		if(CheckHitKey(KEY_INPUT_LEFT) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+8], TRUE);//動いているときはアニメーション
		else if(CheckHitKey(KEY_INPUT_RIGHT) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+12], TRUE);
		else if(CheckHitKey(KEY_INPUT_UP) == 1)		DrawGraph(this->x, this->y, this->graph[animpat+0], TRUE);
		else if(CheckHitKey(KEY_INPUT_DOWN) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+4], TRUE);	
		else if(this->muki == LEFT)DrawGraph(this->x, this->y, this->graph[8], TRUE);//止まっているときは最後の向きを表示
		else if(this->muki == RIGHT)DrawGraph(this->x, this->y, this->graph[12], TRUE);
		else if(this->muki == UP)DrawGraph(this->x, this->y, this->graph[0], TRUE);
		else if(this->muki == DOWN)DrawGraph(this->x, this->y, this->graph[4], TRUE);
	}
}

void Player::Move()
{
	if(CheckHitKey(KEY_INPUT_LEFT) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 0)
	{
		this->x -=	MV;
		this->muki = LEFT;
		if(CheckHitKey(KEY_INPUT_UP) == 1)this->y -= MV;			
		if(CheckHitKey(KEY_INPUT_DOWN) == 1)this->y += MV;
		
	}	
	else if(CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_UP) == 0)	
	{
		this->x += MV;
		this->muki = RIGHT;
		if(CheckHitKey(KEY_INPUT_UP) == 1)this->y -= MV;			
		if(CheckHitKey(KEY_INPUT_DOWN) == 1)this->y += MV;
		
	}			
	else if(CheckHitKey(KEY_INPUT_UP) == 1  && CheckHitKey(KEY_INPUT_DOWN) == 0)
	{
		this->y	-=	MV;
		this->muki = UP; 
		if(CheckHitKey(KEY_INPUT_LEFT) == 1) this->x -= MV;
		if(CheckHitKey(KEY_INPUT_RIGHT) == 1) this->x += MV;
		
	}				
	else if(CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		this->y	+=	MV;
		this->muki = DOWN; 
		if(CheckHitKey(KEY_INPUT_LEFT) == 1) this->x -= MV;
		if(CheckHitKey(KEY_INPUT_RIGHT) == 1) this->x += MV;
		
	}

	this->rx = this->x+32;
	this->dy = this->y+32;
}

/*
void Player::CheckHit(Map &map)
{
	int lx, rx, uy, dy;

	lx = (x+HABA) / 32;
	rx = (x+32-HABA) / 32;
	uy = (y+HABA) / 32;
	dy = (y+32-HABA) / 32;

	//□←
	if( (map.rx[uy][lx]-DHIT <= this->x && this->x <= map.rx[uy][lx]) && (map.y[uy][lx]+DHIT <= this->y && this->y < map.dy[uy][lx]-DHIT) && map.ID[uy][lx] == 1)this->x = map.x[uy][lx] + map.width;//途中
	if( (map.rx[dy][lx]-DHIT <= this->x && this->x <= map.rx[dy][lx]) && (map.y[dy][lx]+DHIT <= this->dy && this->dy < map.dy[dy][lx]-DHIT) && map.ID[dy][lx] == 1)this->x = map.x[dy][lx] + map.width;//上いった
	
	//→□
	if((map.x[uy][lx] <= this->x && this->x < map.x[uy][lx]+DHIT) && (map.y[uy][rx]+DHIT <= this->y && this->y < map.dy[uy][rx]-DHIT) && map.ID[uy][rx] == 1)this->x = map.x[uy][rx]- map.width ;//途中
	if((map.x[dy][lx] <= this->x && this->x < map.x[dy][lx]+DHIT) && (map.y[dy][rx]+DHIT <=this->dy && this->dy < map.dy[dy][rx]-DHIT) && map.ID[dy][rx] == 1)this->x = map.x[dy][rx] - map.width;//上いった
	
	//□
	//↑
	if( (map.dy[uy][lx]-DHIT < this->y && this->y <= map.dy[uy][lx]) && (map.x[uy][lx]+DHIT <= this->x && this->x < map.rx[uy][lx]-DHIT) && map.ID[uy][lx] == 1)this->y = map.dy[uy][lx];//左行く
	if( (map.dy[uy][rx]-DHIT < this->y && this->y <= map.dy[uy][rx]) && (map.x[uy][rx]+DHIT <= this->rx && this->rx < map.rx[uy][rx]-DHIT) && map.ID[uy][rx] == 1)this->y = map.dy[uy][rx];//右行く

	//↓
	//□
	if( (map.y[dy][lx] < this->dy && this->dy <= map.y[dy][lx]+DHIT) && (map.x[dy][lx]+DHIT <= this->x && this->x < map.rx[dy][lx]-DHIT) && map.ID[dy][lx] == 1)this->y = map.y[dy][lx]-32;//左行く
	if( (map.y[dy][rx] < this->dy && this->dy <= map.y[dy][rx]+DHIT) && (map.x[dy][rx]+DHIT <= this->rx && this->rx < map.rx[dy][rx]-DHIT) && map.ID[dy][rx] == 1)this->y = map.y[dy][rx]-32;//右行く

	//真左
	if( (map.y[uy][lx] <= this->y && this->y < map.y[uy][lx]+DHIT) && (map.rx[uy][lx]-DHIT < this->x && this->x <= map.rx[uy][lx]) && map.ID[uy][lx] == 1)this->x = map.x[uy][lx] + map.width;
	if( (map.dy[dy][lx]-DHIT <= this->dy && this->dy <= map.dy[dy][lx]) && (map.rx[dy][lx]-DHIT < this->x && this->x <= map.rx[dy][lx]) && map.ID[dy][lx] == 1 )this->x = map.x[dy][lx] + map.width;

	//真右
	if( (map.y[uy][rx] <= this->y && this->y < map.y[uy][rx]+DHIT) && (map.x[uy][rx] <= this->rx && this->rx < map.x[uy][rx]+DHIT) && map.ID[uy][rx] == 1)this->x = map.x[uy][rx]- map.width;
	if( (map.dy[dy][rx]-DHIT <= this->dy && this->dy <= map.dy[dy][rx]) && (map.x[dy][rx] <= this->rx && this->rx < map.x[dy][rx]+DHIT) && map.ID[dy][rx] == 1)this->x = map.x[dy][rx] - map.width;

	//真上
	if( (map.x[uy][lx] <= this->x && this->x < map.x[uy][lx]+DHIT) && (map.dy[uy][lx]-DHIT < this->y && this->y <= map.dy[uy][lx]) && map.ID[uy][lx] == 1)this->y = map.dy[uy][lx];
	if( (map.rx[uy][rx]-DHIT <= this->rx && this->rx <= map.rx[uy][rx]) && (map.dy[uy][rx]-DHIT < this->y && this->y <= map.dy[uy][rx]) && map.ID[uy][rx] == 1)this->y = map.dy[uy][rx];

	//真下
	if( (map.x[dy][lx] <= this->x && this->x < map.x[dy][lx]+DHIT) && (map.y[dy][lx] < this->dy && this->dy <= map.y[dy][lx]+DHIT) && map.ID[dy][lx] == 1)this->y = map.y[dy][lx] - map.width;
	if( (map.rx[dy][rx]-DHIT <= this->rx && this->rx <= map.rx[dy][rx]) && (map.y[dy][rx] < this->dy && this->dy <= map.y[dy][rx]+DHIT) && map.ID[dy][rx] == 1)this->y = map.y[dy][rx] - map.width;

	//角
	if(this->x == map.rx[uy][lx] && this->y == map.dy[uy][lx])
	{
		this->x = map.rx[uy][lx];
		this->y = map.dy[uy][lx];
	}

	if(this->x < 64)this->x = 64;
	if(this->x > 32*14)this->x = 32*14;
	if(this->y < 32)this->y = 32;
	if(this->y > 32*11)this->y = 32*11;
}
*/

int Player::GetStateFire(const Item &item)//存在がFALSE の物の数を数えればよい。その数を戻り値にする。
{
	//static int firelevel = 1;
	if(item.GetFlag() == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int Player::GetStateBomb(const ItemManager &manageItem)
{
	static int bombNum;
	return 0;

}

Player::~Player(void)
{
}
