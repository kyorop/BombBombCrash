#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "ItemManager.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "SecretCommand.h"
#include "Timer.h"
#include "DxLib.h"


enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOHIT,
};

Player::Player()
	:image_left(Image::GetInstance()->GetCharacterImage(id, Image::LEFT)),
	image_right(Image::GetInstance()->GetCharacterImage(id, Image::RIGHT)),
	image_up(Image::GetInstance()->GetCharacterImage(id, Image::UP)),
	image_down(Image::GetInstance()->GetCharacterImage(id, Image::DOWN)),
	image_death(Image::GetInstance()->GetCharacterImage(id, Image::DEATH)),
	hasFinished(0),
	animationTime(new Timer),
	animationFrame(0)
{
	x = 32*2;
	rx = x+32;
	y = 32*1;
	dy = y+32;
	muki = DOWN;
	flag =1;
	animpat = 0;
	MapState::GetInstance()->RegisterWithCharacter(this);
	Collision::GetInstance()->Register(this);
	//隠しコマンド
	if(SecretCommand::HittedSecretCommand())
	{
		bombNum = 10;
		fireLevel = 10;
		mv = 4;
	}
}


Player::~Player(void)
{
	delete animationTime;
}


void Player::Move()
{
	if(flag)
	{
		if(CheckHitKey(KEY_INPUT_LEFT) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 0)
		{
			this->x -=	mv;
			this->muki = LEFT;
			if(CheckHitKey(KEY_INPUT_UP) == 1)this->y -= mv;			
			if(CheckHitKey(KEY_INPUT_DOWN) == 1)this->y += mv;
		}	
		else if(CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_UP) == 0)	
		{
			this->x += mv;
			this->muki = RIGHT;
			if(CheckHitKey(KEY_INPUT_UP) == 1)this->y -= mv;			
			if(CheckHitKey(KEY_INPUT_DOWN) == 1)this->y += mv;
		
		}			
		else if(CheckHitKey(KEY_INPUT_UP) == 1  && CheckHitKey(KEY_INPUT_DOWN) == 0)
		{
			this->y	-=	mv;
			this->muki = UP; 
			if(CheckHitKey(KEY_INPUT_LEFT) == 1) this->x -= mv;
			if(CheckHitKey(KEY_INPUT_RIGHT) == 1) this->x += mv;
		
		}				
		else if(CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			this->y	+=	mv;
			this->muki = DOWN; 
			if(CheckHitKey(KEY_INPUT_LEFT) == 1) this->x -= mv;
			if(CheckHitKey(KEY_INPUT_RIGHT) == 1) this->x += mv;
		}

		if(CheckHitKey(KEY_INPUT_BACKSLASH)==1)
		{
			this->x += mv;
			this->y += mv;
			this->muki = LEFT;
		}
		else if(CheckHitKey(KEY_INPUT_SLASH)==1)
		{
			this->x -= mv;
			this->y += mv;
			this->muki = RIGHT;
		}
		else if(CheckHitKey(KEY_INPUT_SEMICOLON)==1)
		{
			this->x -= mv;
			this->y -= mv;
			this->muki = LEFT;
		}
		else if(CheckHitKey(KEY_INPUT_COLON)==1)
		{
			this->x += mv;
			this->y -= mv;
			this->muki = RIGHT;
		}

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

		this->rx = this->x+32;
		this->dy = this->y+32;

		if(this->x < 64)this->x = 64;
		if(this->x > 32*14)this->x = 32*14;
		if(this->y < 32)this->y = 32;
		if(this->y > 32*11)this->y = 32*11;

		animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
	}
}


void Player::Draw()
{
	if(this->flag == 1)
	{
		int image;
		if(CheckHitKey(KEY_INPUT_LEFT) == 1) 
			image = image_left[animpat];
		else if(CheckHitKey(KEY_INPUT_RIGHT) == 1) 
			image = image_right[animpat];
		else if(CheckHitKey(KEY_INPUT_UP) == 1)
			image = image_up[animpat];
		else if(CheckHitKey(KEY_INPUT_DOWN) == 1) 
			image = image_down[animpat];
		else
		{
			//キーを押してないときはアニメーションしないことを意味する
			animpat = 0;
			if(muki == LEFT)
				image = image_left[animpat];
			else if(muki == RIGHT)
				image = image_right[animpat];
			else if(muki == UP)
				image = image_up[animpat];
			else if(muki == DOWN)
				image = image_down[animpat];
		}

		DrawGraph(x, y, image, TRUE);
	}
	else
	{
		if( !hasFinished )
		{
			if(animationTime->CountDownFrame(1*1000))
			{
				++animationFrame;
				if(animationFrame == 3)
					hasFinished = 1;
			}
			DrawGraph(x, y, image_death[animationFrame], true);
		}
	}
}


void Player::AddMV(void)
{
	//スピードの上限は４まで
	if(mv < 4)
	{
		++mv;
	}
}


int Player::EnableBomb()const
{
	if(CheckHitKey(KEY_INPUT_Z) == 1)
		return 1;
	else
		return 0;
}