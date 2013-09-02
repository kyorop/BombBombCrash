#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "ItemManager.h"
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
		if(CheckHitKey(KEY_INPUT_LEFT) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+8], TRUE);//�����Ă���Ƃ��̓A�j���[�V����
		else if(CheckHitKey(KEY_INPUT_RIGHT) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+12], TRUE);
		else if(CheckHitKey(KEY_INPUT_UP) == 1)		DrawGraph(this->x, this->y, this->graph[animpat+0], TRUE);
		else if(CheckHitKey(KEY_INPUT_DOWN) == 1)	DrawGraph(this->x, this->y, this->graph[animpat+4], TRUE);	
		else if(this->muki == LEFT)DrawGraph(this->x, this->y, this->graph[8], TRUE);//�~�܂��Ă���Ƃ��͍Ō�̌�����\��
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

int Player::GetStateFire(const Item &item)//���݂�FALSE �̕��̐��𐔂���΂悢�B���̐���߂�l�ɂ���B
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
