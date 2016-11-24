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
#include "MapObject.h"
#include "PlayerAnimation.h"

using namespace BombBombCrash;



Player::Player(const ln::Vector2& position, KeyState device):
Character(position,GameConstant::BlockWidth, GameConstant::BlockHeight),
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
fireLevel(1),
isWalking(false),
animation(new PlayerAnimation(*this))
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
		SetPosition(ln::Vector2(BombBombCrash::FIRST_X_RIGHT, BombBombCrash::FIRST_Y_DOWN));
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
			isWalking = true;
			if(input->GetInputMoveUp())
			{
				Translate(ln::Vector2(0, -speed));
				muki = UP;
			}
			if(input->GetInputMoveDown())
			{
				Translate(ln::Vector2(0, speed));
				muki = DOWN;
			}
		}	
		else if(input->GetInputMoveRight() && !input->GetInputMoveDown() && !input->GetInputMoveUp())	
		{
			Translate(ln::Vector2(speed, 0));
			this->muki = RIGHT;
			isWalking = true;
			if(input->GetInputMoveUp())
			{
				Translate(ln::Vector2(0, -speed));
				muki = UP;
			}
			if(input->GetInputMoveDown())
			{
				Translate(ln::Vector2(0, speed));
				muki = DOWN;
			}
		
		}			
		else if(input->GetInputMoveUp()  && input->GetInputMoveDown() == 0)
		{
			Translate(ln::Vector2(0, -speed));
			this->muki = UP; 
			isWalking = true;
			if(input->GetInputMoveLeft())
			{
				Translate(ln::Vector2(-speed, 0));
				muki = LEFT;
			}
			if(input->GetInputMoveRight())
			{
				Translate(ln::Vector2(speed, 0));
				muki = RIGHT;
			}
		}			
		else if (input->GetInputMoveDown())
		{
			Translate(ln::Vector2(0, speed));
			this->muki = DOWN;
			isWalking = true;
			if (input->GetInputMoveLeft())
			{
				Translate(ln::Vector2(-speed, 0));
				muki = LEFT;
			}
			if (input->GetInputMoveRight())
			{
				Translate(ln::Vector2(speed, 0));
				muki = RIGHT;
			}
		}
		else
			isWalking = false;

		auto pos = Position();
		if (pos.X < 64)
			SetPosition(ln::Vector2(64,pos.Y));
		if (pos.X > 32 * 14)
			SetPosition(ln::Vector2(32 * 14, pos.Y));
		if (pos.Y < 32)
			SetPosition(ln::Vector2(pos.X, 32));
		if (pos.Y > 32 * 11)
			SetPosition(ln::Vector2(pos.X, 32 * 11));
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
	if (Exists())
		animation->Walk();
	else
		animation->Killed();
}

void Player::Destroy(const GameManager& game)
{
}

bool Player::CanRemove()
{
	return !Exists();
}