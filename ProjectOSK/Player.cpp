#include "Player.h"
#include "MapState.h"
#include "Collision.h"
#include "SecretCommand.h"
#include "GameConstant.h"
#include "KeyboardPlayerInput.h"
#include "Bomb.h"
#include "GameManager.h"
#include "MapObject.h"
#include "PlayerAnimation.h"
#include "Timer.h"
#include "CollisionUtil.h"
#include "Rect.h"
using namespace BombBombCrash;


void Player::OnCollide(CollisionableObject* object)
{
	if (object->Type() == GameObjectType::HardBlock
		|| object->Type() == GameObjectType::SoftBlock
		|| object->Type() == GameObjectType::Bomb)
	{
		const int padding = 5;
		float wallW = object->Width();
		float wallH = object->Height();
		auto wallPos = object->Position();
		auto wallLowerRightPos = object->LowerRightPosition();

		ln::Vector2 upperPading(padding, 0);
		ln::Vector2 lowerPadding(-padding, -(wallH - padding));
		::Rect upperBlock(wallPos + upperPading, wallLowerRightPos + lowerPadding);
		if (CollisionUtil::Test(this->Rect(), upperBlock))
		{
			this->Translate(ln::Vector2(0, -(this->DY() - upperBlock.Top())));
			return;
		}

		ln::Vector2 leftPaddingForUpper(0, padding);
		ln::Vector2 leftPaddingForLower(-(wallW - padding), -padding);
		::Rect leftBlock(wallPos + leftPaddingForUpper, wallLowerRightPos + leftPaddingForLower);
		if (CollisionUtil::Test(this->Rect(), leftBlock))
		{
			this->Translate(ln::Vector2(-(this->X() - wallPos.X + this->Width()), 0));
			return;
		}

		ln::Vector2 bottomPaddingForUpper(padding, wallH - padding);
		ln::Vector2 bottomPaddingForLower(-padding, 0);
		::Rect bottomBlock(wallPos + bottomPaddingForUpper, wallLowerRightPos + bottomPaddingForLower);
		if (CollisionUtil::Test(this->Rect(), bottomBlock))
		{
			this->Translate(ln::Vector2(0, wallLowerRightPos.Y - this->Y()));
			return;
		}

		ln::Vector2 rightPaddingForUpper(wallW - padding, padding);
		ln::Vector2 rightPaddingForLower(0, -padding);
		::Rect rightBlock(wallPos + rightPaddingForUpper, wallLowerRightPos + rightPaddingForLower);
		if (CollisionUtil::Test(this->Rect(), rightBlock))
		{
			this->Translate(ln::Vector2(wallLowerRightPos.X - this->X(), 0));
			return;
		}
	}
}

Player::Player(const ln::Vector2& position, KeyState device):
Character(position,GameConstant::BlockWidth, GameConstant::BlockHeight),
isJoypad(device),
input(new KeyboardPlayerInput()),
bomb(std::make_unique<BombController>()),
speed(1),
fireLevel(1),
isWalking(false),
animation(new PlayerAnimation(*this)),
muki(DOWN)
{
	bomb->IncrementBomb(fireLevel);
	SetPosition(position);
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
	bomb->IncrementBomb(fireLevel);
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
		auto newBomb = bomb->Request(Position(), fireLevel);
		if (newBomb != nullptr)
			game.AddGameObject(newBomb);
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