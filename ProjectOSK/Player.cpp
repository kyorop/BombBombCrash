#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "ItemManager.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
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
	:image_left(Image::GetInstance()->GetPlayerImage(Image::LEFT)),
	image_right(Image::GetInstance()->GetPlayerImage(Image::RIGHT)),
	image_up(Image::GetInstance()->GetPlayerImage(Image::UP)),
	image_down(Image::GetInstance()->GetPlayerImage(Image::DOWN))
{
	x = 32*2;
	rx = x+32;
	y = 32*1;
	dy = y+32;
	muki = DOWN;
	flag =1;
	animpat = 0;
	Collision::GetInstance()->Register(this);
}


Player::~Player(void)
{
}


void Player::Draw()
{
	if(this->flag == 1)
	{
		if(CheckHitKey(KEY_INPUT_LEFT) == 1)			DrawGraph(this->x, this->y, image_left[animpat], TRUE);//動いているときはアニメーション
		else if(CheckHitKey(KEY_INPUT_RIGHT) == 1)	DrawGraph(this->x, this->y, image_right[animpat], TRUE);
		else if(CheckHitKey(KEY_INPUT_UP) == 1)		DrawGraph(this->x, this->y, image_up[animpat], TRUE);
		else if(CheckHitKey(KEY_INPUT_DOWN) == 1)	DrawGraph(this->x, this->y, image_down[animpat], TRUE);	
		else if(this->muki == LEFT)		DrawGraph(this->x, this->y, *image_left, TRUE);//止まっているときは最後の向きを表示
		else if(this->muki == RIGHT)	DrawGraph(this->x, this->y, *image_right, TRUE);
		else if(this->muki == UP)		DrawGraph(this->x, this->y, *image_up,TRUE);
		else if(this->muki == DOWN)	DrawGraph(this->x, this->y, *image_down, TRUE);
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
	
	if(CheckHitKey(KEY_INPUT_BACKSLASH)==1)
	{
		this->x += MV;
		this->y += MV;
		this->muki = LEFT;
	}
	else if(CheckHitKey(KEY_INPUT_SLASH)==1)
	{
		this->x -= MV;
		this->y += MV;
		this->muki = RIGHT;
	}
	else if(CheckHitKey(KEY_INPUT_SEMICOLON)==1)
	{
		this->x -= MV;
		this->y -= MV;
		this->muki = LEFT;
	}
	else if(CheckHitKey(KEY_INPUT_COLON)==1)
	{
		this->x += MV;
		this->y -= MV;
		this->muki = RIGHT;
	}

	this->rx = this->x+32;
	this->dy = this->y+32;

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

	animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
}


int Player::EnableBomb()const
{
	if(CheckHitKey(KEY_INPUT_Z) == 1)
		return 1;
	else
		return 0;
}




