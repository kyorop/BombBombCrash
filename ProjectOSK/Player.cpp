#include "Player.h"
#include "MapState.h"
#include "SecretCommand.h"
#include "GameConstant.h"
#include "KeyboardPlayerInput.h"
#include "MapObject.h"
#include "PlayerWalkingAnimation.h"
#include "CharacterKilledAnimation.h"
#include "Rect.h"
#include "CollisionUtil.h"


using namespace BombBombCrash;

Player::Player(const ln::Vector2& position, KeyState device) :
Character(position, GameConstant::BlockWidth, GameConstant::BlockHeight),
isJoypad(device),
input(new KeyboardPlayerInput()),
walking_animation_(std::make_unique<PlayerWalkingAnimation>(*input)),
bomb_bag_(std::make_shared<BombBag>())
{
	SetPosition(position);
	MapState::GetInstance()->RegisterWithCharacter(this);

	if(isJoypad == JOYPAD)
	{
		SetPosition(ln::Vector2(BombBombCrash::FIRST_X_RIGHT, BombBombCrash::FIRST_Y_DOWN));
	}
}


void Player::Move()
{
	if (input->GetInputMoveLeft() && !input->GetInputMoveDown() && !input->GetInputMoveUp() && !input->GetInputMoveRight())
	{
		Translate(ln::Vector2(-Speed(), 0));
		if (input->GetInputMoveUp())
		{
			Translate(ln::Vector2(0, -Speed()));
		}
		if (input->GetInputMoveDown())
		{
			Translate(ln::Vector2(0, Speed()));
		}
	}
	else if (input->GetInputMoveRight() && !input->GetInputMoveDown() && !input->GetInputMoveUp())
	{
		Translate(ln::Vector2(Speed(), 0));
		if (input->GetInputMoveUp())
		{
			Translate(ln::Vector2(0, -Speed()));
		}
		if (input->GetInputMoveDown())
		{
			Translate(ln::Vector2(0, Speed()));
		}

	}
	else if (input->GetInputMoveUp() && input->GetInputMoveDown() == 0)
	{
		Translate(ln::Vector2(0, -Speed()));
		if (input->GetInputMoveLeft())
		{
			Translate(ln::Vector2(-Speed(), 0));
		}
		if (input->GetInputMoveRight())
		{
			Translate(ln::Vector2(Speed(), 0));
		}
	}
	else if (input->GetInputMoveDown())
	{
		Translate(ln::Vector2(0, Speed()));
		if (input->GetInputMoveLeft())
		{
			Translate(ln::Vector2(-Speed(), 0));
		}
		if (input->GetInputMoveRight())
		{
			Translate(ln::Vector2(Speed(), 0));
		}
	}

	auto pos = Position();
	if (pos.X < 64)
		SetPosition(ln::Vector2(64, pos.Y));
	if (pos.X > 32 * 14)
		SetPosition(ln::Vector2(32 * 14, pos.Y));
	if (pos.Y < 32)
		SetPosition(ln::Vector2(pos.X, 32));
	if (pos.Y > 32 * 11)
		SetPosition(ln::Vector2(pos.X, 32 * 11));
}


void Player::Initialize()
{
	bomb_bag_->IncrementMaxBombNum();
}

void Player::Update()
{
	Move();
	PutBomb();
	
	if (CheckHitKey(KEY_INPUT_D))
	{
		Create(std::make_unique<CharacterKilledAnimation>(Position()));
		Delete();
	}

}

void Player::Draw()
{
	walking_animation_->Play(Position());
}

void Player::PutBomb()
{
	if (input->GetInputPutBomb())
	{
		auto new_bomb = BombBag::Request(bomb_bag_, Position());
		if (new_bomb)
		{
			on_bomb_ids_.emplace_back(new_bomb->Id());
			Create(move(new_bomb));
		}
	}
}

MapObject::ObjectType Player::Type()const{
	return ObjectType::Player;
}

void Player::OnCollide(MapObject& other)
{
	if (other.Type()==BombUpItem)
	{
		bomb_bag_->IncrementMaxBombNum();
		return;
	}

	if (other.Type()==FireUpItem)
	{
		bomb_bag_->IncrementFireLevel();
		return;
	}

	if (other.Type() == Fire)
	{
		// Delete();
	}

	if (other.Type() == Bomb)
	{
		auto itr = find(begin(on_bomb_ids_), end(on_bomb_ids_), other.Id());
		if (itr != end(on_bomb_ids_))
		{
			return;
		}
	}

	if (other.Type() == HardBlock
		|| other.Type() == BREAKABLE_BLOCK
		|| (other.Type() == Bomb))
	{
		const int padding = 5;
		float wallW = other.Width();
		float wallH = other.Height();
		auto wallPos = other.Position();
		auto wallLowerRightPos = other.LowerRightPosition();

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

void Player::OnCollisionExit(MapObject& other)
{
	auto itr = find(begin(on_bomb_ids_), end(on_bomb_ids_), other.Id());
	if (itr != end(on_bomb_ids_))
	{
		on_bomb_ids_.erase(itr);
	}
}
