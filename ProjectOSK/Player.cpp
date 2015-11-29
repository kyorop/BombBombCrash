#include "Player.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "SecretCommand.h"
#include "Timer.h"
#include "GameConstant.h"
#include "DxLib.h"
#include "KeyboardInput.h"


enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOHIT,
};

Player::Player(KeyState device)
	:image_left(Image::GetInstance()->GetCharacterImage(id, Image::LEFT)),
	image_right(Image::GetInstance()->GetCharacterImage(id, Image::RIGHT)),
	image_up(Image::GetInstance()->GetCharacterImage(id, Image::UP)),
	image_down(Image::GetInstance()->GetCharacterImage(id, Image::DOWN)),
	image_death(Image::GetInstance()->GetCharacterImage(id, Image::DEATH)),
	hasFinished(0),
	animationTime(new Timer),
	animationFrame(0),
	isJoypad(device),
	input(new KeyboardInput())
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

	if(isJoypad == JOYPAD)
	{
		x = GameConst::FIRST_X_RIGHT;
		y = GameConst::FIRST_Y_DOWN;
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
		if(input->GetInputMoveLeft() && ! input->GetInputMoveDown() && input->GetInputMoveUp() == 0 && input->GetInputMoveRight() == 0)
		{
			this->x -=	mv;
			this->muki = LEFT;
			if(input->GetInputMoveUp() )
				this->y -= mv;			
			if(input->GetInputMoveDown())
				this->y += mv;
		}	
		else if(input->GetInputMoveRight() && input->GetInputMoveDown() == 0 && input->GetInputMoveUp() == 0)	
		{
			this->x += mv;
			this->muki = RIGHT;
			if(input->GetInputMoveUp())
				this->y -= mv;			
			if(input->GetInputMoveDown())
				this->y += mv;
		
		}			
		else if(input->GetInputMoveUp()  && input->GetInputMoveDown() == 0)
		{
			this->y	-=	mv;
			this->muki = UP; 
			if(input->GetInputMoveLeft())
				this->x -= mv;
			if(input->GetInputMoveRight()) 
				this->x += mv;
		
		}				
		else if(input->GetInputMoveDown())
		{
			this->y	+=	mv;
			this->muki = DOWN; 
			if(input->GetInputMoveLeft()) 
				this->x -= mv;
			if(input->GetInputMoveRight())
				this->x += mv;
		}
		//		else
//		{
//			int inputState = GetJoypadInputState(DX_INPUT_PAD1);
//			int up = inputState & PAD_INPUT_UP;
//			int down = inputState & PAD_INPUT_DOWN;
//			int left = inputState & PAD_INPUT_LEFT;
//			int right = inputState & PAD_INPUT_RIGHT;
//
//			if( left && (down == 0) && (up == 0) && (right== 0))
//			{
//				this->x -=	mv;
//				this->muki = LEFT;
//				if(up)this->y -= mv;
//				if(down)this->y += mv;
//			}	
//			else if( right && (down == 0) && (up == 0))	
//			{
//				this->x += mv;
//				this->muki = RIGHT;
//				if(up)this->y -= mv;			
//				if(down)this->y += mv;
//			}			
//			else if(up  && (down == 0))
//			{
//				this->y	-=	mv;
//				this->muki = UP; 
//				if(left) this->x -= mv;
//				if(right) this->x += mv;
//			}				
//			else if(down)
//			{
//				this->y	+=	mv;
//				this->muki = DOWN; 
//				if(left) this->x -= mv;
//				if(right) this->x += mv;
//			}
//		}

		//if(CheckHitKey(KEY_INPUT_BACKSLASH)==1)
		//{
		//	this->x += mv;
		//	this->y += mv;
		//	this->muki = LEFT;
		//}
		//else if(CheckHitKey(KEY_INPUT_SLASH)==1)
		//{
		//	this->x -= mv;
		//	this->y += mv;
		//	this->muki = RIGHT;
		//}
		//else if(CheckHitKey(KEY_INPUT_SEMICOLON)==1)
		//{
		//	this->x -= mv;
		//	this->y -= mv;
		//	this->muki = LEFT;
		//}
		//else if(CheckHitKey(KEY_INPUT_COLON)==1)
		//{
		//	this->x += mv;
		//	this->y -= mv;
		//	this->muki = RIGHT;
		//}
		//
		//if(CheckHitKey(KEY_INPUT_Q) == 1)
		//{
		//	this->x = 32*2;
		//	this->y = 32*1;
		//	this->muki = DOWN;
		//	this->flag = 1;
		//}
		//if(CheckHitKey(KEY_INPUT_W) == 1)
		//{
		//	this->x = 32*14;
		//	this->y = 32*1;
		//	this->muki = DOWN;
		//}
		//if(CheckHitKey(KEY_INPUT_E) == 1)
		//{
		//	this->x = 32*2;
		//	this->y = 32*11;
		//	this->muki = DOWN;
		//}
		//if(CheckHitKey(KEY_INPUT_R) == 1)
		//{
		//	this->x = 32*14;
		//	this->y = 32*11;
		//	this->muki = DOWN;
		//}
		//if(CheckHitKey(KEY_INPUT_X) == 1)
		//{
		//	this->x = 32*10;
		//	this->y = 32*10;
		//	this->muki = DOWN;
		//}

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
	if(flag)
	{
		int image;
		{
			if(input->GetInputMoveLeft() == 1) 
				image = image_left[animpat];
			else if(input->GetInputMoveRight() == 1) 
				image = image_right[animpat];
			else if(input->GetInputMoveUp() == 1)
				image = image_up[animpat];
			else if(input->GetInputMoveDown() == 1) 
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
		}
//		else if(isJoypad == JOYPAD)
//		{
//			int inputState = GetJoypadInputState(DX_INPUT_PAD1);
//			int up = inputState & PAD_INPUT_UP;
//			int down = inputState & PAD_INPUT_DOWN;
//			int left = inputState & PAD_INPUT_LEFT;
//			int right = inputState & PAD_INPUT_RIGHT;
//
//			if(left) 
//				image = image_left[animpat];
//			else if(right) 
//				image = image_right[animpat];
//			else if(up)
//				image = image_up[animpat];
//			else if(down) 
//				image = image_down[animpat];
//			else
//			{
//				//キーを押してないときはアニメーションしないことを意味する
//				animpat = 0;
//				if(muki == LEFT)
//					image = image_left[animpat];
//				else if(muki == RIGHT)
//					image = image_right[animpat];
//				else if(muki == UP)
//					image = image_up[animpat];
//				else if(muki == DOWN)
//					image = image_down[animpat];
//			}
//		}

		DxLib:: DrawGraph(x, y, image, TRUE);
	}
	else		//死亡時のアニメーション
	{
		if( !hasFinished )
		{
			if(animationTime->CountDownFrame(1*1000))
			{
				++animationFrame;
				if(animationFrame == 3)
					hasFinished = 1;
			}
			DxLib::DrawGraph(x, y, image_death[animationFrame], true);
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
	if(isJoypad == KEYBORAD)
	{
		if(CheckHitKey(KEY_INPUT_Z) == 1)
			return 1;
		else
			return 0;
	}
	else
	{
		int inputState = GetJoypadInputState(DX_INPUT_PAD1);
		int input2 = inputState & PAD_INPUT_2;

		if(input2)
			return 1;
		else
			return 0;
	}
}