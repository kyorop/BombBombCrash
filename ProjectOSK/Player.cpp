#include "Player.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "SecretCommand.h"
#include "Timer.h"
#include "GameConstant.h"
#include "KeyboardPlayerInput.h"
#include "Bomb.h"
#include "GameManager.h"

using namespace BombBombCrash;

enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOHIT,
};

Player::Player(const ln::Vector2& position, KeyState device)
	:
	image_left(Image::GetInstance()->GetCharacterImage(id, Image::LEFT)),
	image_right(Image::GetInstance()->GetCharacterImage(id, Image::RIGHT)),
	image_up(Image::GetInstance()->GetCharacterImage(id, Image::UP)),
	image_down(Image::GetInstance()->GetCharacterImage(id, Image::DOWN)),
	image_death(Image::GetInstance()->GetCharacterImage(id, Image::DEATH)),
	hasFinished(0),
	animationTime(new Timer),
	animationFrame(0),
	isJoypad(device),
	input(new KeyboardPlayerInput()),
	bomb(std::make_unique<BombController>()),
	speed(1),
	fireLevel(1)
{
	SetPosition(position);
	muki = DOWN;
	animpat = 0;
	MapState::GetInstance()->RegisterWithCharacter(this);
	Collision::Instance()->Register(this);
	//隠しコマンド
	if(SecretCommand::HittedSecretCommand())
	{
		speed = 4;
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
	if(Exists())
	{
		if(input->GetInputMoveLeft() && !input->GetInputMoveDown() && !input->GetInputMoveUp() && !input->GetInputMoveRight())
		{
			Translate(ln::Vector2(-speed, 0));
			this->muki = LEFT;
			if(input->GetInputMoveUp())
				Translate(ln::Vector2(0, -speed));
			if(input->GetInputMoveDown())
				Translate(ln::Vector2(0, speed));
		}	
		else if(input->GetInputMoveRight() && input->GetInputMoveDown() == 0 && input->GetInputMoveUp() == 0)	
		{
			Translate(ln::Vector2(speed, 0));
			this->muki = RIGHT;
			if(input->GetInputMoveUp())
				Translate(ln::Vector2(0, -speed));
			if(input->GetInputMoveDown())
				Translate(ln::Vector2(0, speed));
		
		}			
		else if(input->GetInputMoveUp()  && input->GetInputMoveDown() == 0)
		{
			Translate(ln::Vector2(0, -speed));
			this->muki = UP; 
			if(input->GetInputMoveLeft())
				Translate(ln::Vector2(-speed, 0));
			if(input->GetInputMoveRight()) 
				Translate(ln::Vector2(speed, 0));
		}			
		else if(input->GetInputMoveDown())
		{
			Translate(ln::Vector2(0, speed));
			this->muki = DOWN; 
			if(input->GetInputMoveLeft()) 
				Translate(ln::Vector2(-speed, 0));
			if(input->GetInputMoveRight())
				Translate(ln::Vector2(speed, 0));
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



void Player::Update()
{

}

void Player::IncrementSpeed(void)
{
	//スピードの上限は４まで
	if(speed < 4)
	{
		++speed;
	}
}

int Player::Speed()
{
	return speed;
}

int Player::BombSize()
{
	return bomb->MaxSize();
}

int Player::FireLevel()
{
	return fireLevel;
}

void Player::IncrementBomb()
{
	bomb->IncrementBomb();
}

void Player::IncrementFireLevel()
{ 
	++fireLevel;
}

void Player::Initialize(GameManager& game)
{
}

void Player::Update(GameManager& game)
{
	Move();

	if (input->GetInputPutBomb())
	{
		game.AddElement(bomb->Request(Position(), fireLevel));
	}
}

void Player::Draw(const GameManager& game)
{
	if (exists)
	{
		int image;
		{
			if (input->GetInputMoveLeft() == 1)
				image = image_left[animpat];
			else if (input->GetInputMoveRight() == 1)
				image = image_right[animpat];
			else if (input->GetInputMoveUp() == 1)
				image = image_up[animpat];
			else if (input->GetInputMoveDown() == 1)
				image = image_down[animpat];
			else
			{
				//キーを押してないときはアニメーションしないことを意味する
				animpat = 0;
				if (muki == LEFT)
					image = image_left[animpat];
				else if (muki == RIGHT)
					image = image_right[animpat];
				else if (muki == UP)
					image = image_up[animpat];
				else if (muki == DOWN)
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

		auto pos = Position();
		DrawGraph(pos.X, pos.Y, image, TRUE);
	}
	else		//死亡時のアニメーション
	{
		if (!hasFinished)
		{
			if (animationTime->CountDownFrame(1 * 1000))
			{
				++animationFrame;
				if (animationFrame == 3)
					hasFinished = 1;
			}
			auto pos = Position();
			DrawGraph(pos.X, pos.Y, image_death[animationFrame], true);
		}
	}
}

void Player::Destroy(const GameManager& game)
{
}

bool Player::CanRemove()
{
	return !Exists();
}