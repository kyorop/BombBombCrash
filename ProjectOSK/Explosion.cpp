#include "Explosion.h"
#include "Image.h"
#include "Collision.h"
#include "GameManager.h"
#include "Timer.h"

#define DHIT 6

using namespace BombBombCrash;
using namespace std;

/*
FireBlock
*/

FireBlock::FireBlock(const ln::Vector2& position, int fireImage):
MapObject(position, 32,32),
fireImageHandle(fireImage)
{
}

void FireBlock::Draw() const
{
	if (Exists())
		DrawGraph(Position().X, Position().Y, fireImageHandle, false);
}

/*
FirePillar
*/

FirePillar::FirePillar(FirePillarDirection direction, int fireLevel, const std::shared_ptr<FireBlock>& center) :
pillar(0),
center(center),
direction(direction),
fireLevel(fireLevel)
{
}

shared_ptr<IFireIterator> FirePillar::Iterator()
{
	return make_shared<FirePillarIterator>(*this);
}

ln::Vector2 FirePillar::Direction() const
{
	switch (direction)
	{
	case FirePillarDirection::Up:
		return ln::Vector2(-center->Height(),0);
	case FirePillarDirection::Right:
		return ln::Vector2(0, center->Width());
	case FirePillarDirection::Down:
		return ln::Vector2(center->Height(), 0);
	case FirePillarDirection::Left:
		return ln::Vector2(0, -center->Width());
	default:
		return ln::Vector2(0,0);
	}
}

void FirePillar::Initialize()
{
	for (size_t i = 0; i < fireLevel; i++)
	{
		pillar.push_back(make_shared<FireBlock>(center->Position()+Direction()*(i + 1), Image::GetInstance()->GetImage(Image::FIRE)));
	}
}

void FirePillar::Increment()
{
	if (pillar.empty())
	{
		auto newBlock = make_shared<FireBlock>(center->Position() + Direction(), Image::GetInstance()->GetImage(Image::FIRE));
	}
	else
	{
		auto last = FireBlockAt(Size() - 1);
		auto newBlock = make_shared<FireBlock>(last->Position() + Direction(), Image::GetInstance()->GetImage(Image::FIRE));
		pillar.push_back(newBlock);
	}
}

int FirePillar::Size() const
{
	if (pillar.empty())
		return 0;

	return pillar.size();
}

std::shared_ptr<FireBlock> FirePillar::FireBlockAt(int i)
{
	return pillar[i];
}

/*
FirePillarIterator
*/

FirePillarIterator::FirePillarIterator(FirePillar& pillar) :
fire(pillar),
index(0)
{
}

std::shared_ptr<FireBlock> FirePillarIterator::Next()
{
	return fire.FireBlockAt(index++);
}

bool FirePillarIterator::HasNext()
{
	return fire.Size() > index;
}


/*
Fire
*/

Fire::Fire(const ln::Vector2& centerPos):
timer(make_shared<Timer>()),
center(make_shared<FireBlock>(centerPos, Image::GetInstance()->GetImage(Image::FIRE))),
firePillars()
{
}

void Fire::Initialize(GameManager& game)
{
	timer->TurnReset();
	firePillars.clear();
	firePillars.push_back(make_shared<FirePillar>(FirePillarDirection::Up, 1, center));
	firePillars.push_back(make_shared<FirePillar>(FirePillarDirection::Right, 1, center));
	firePillars.push_back(make_shared<FirePillar>(FirePillarDirection::Down, 1, center));
	firePillars.push_back(make_shared<FirePillar>(FirePillarDirection::Left, 1, center));
	for (auto& pillar : firePillars)
		pillar->Initialize();
	
	Collision::Instance()->RegisterWithFire(this);
}

void Fire::Update(GameManager& game)
{
	if (timer->CountDownFrame(fireTime))
	{
		for (auto& pillar: firePillars)
		{
			auto itr = pillar->Iterator();
			if (itr->HasNext())
			{
				itr->Next()->SetExists(false);
			}
		}
	}
}

void Fire::Draw(const GameManager& game)
{
	center->Draw();
	for (auto& fire:firePillars)
	{
		auto itr = fire->Iterator();
		if (itr->HasNext())
		{
			itr->Next()->Draw();
		}
	}
}

void Fire::Destroy(const GameManager& game)
{
}

bool Fire::CanRemove()
{
	for (auto& pillar : firePillars)
	{
		auto itr = pillar->Iterator();
		while (itr->HasNext())
		{
			if (itr->Next()->Exists())
				return false;
		}
	}

	return true;
}


void Fire::Maintain()
{
//	if (explosion == TRUE)
//	{
//		if (retainFire.CountDownFrame(displayingTime) == true)
//		{
//			explosion = FALSE;
//			for (int i = 0, size = vex.size(); i<size; i++)
//			{
//				vex[i]->SetExplosion(FALSE);
//			}
//		}
//	}
}


void Fire::Register(void)
{
//	for (int i = 0, size = vex.size(); i<size; ++i)
//	{
//		if (vex[i]->GetExplosion() == 0)
//			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 0);
//		else if (vex[i]->GetExplosion() == 1)
//			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 1);
//	}
}



int Fire::GetX(int i)const
{
	return vex[i]->X();
}

int Fire::GetY(int i)const
{
	return vex[i]->Y();
}

int Fire::GetFlag(int i)const
{
	return vex[i]->Exists();
}

int Fire::GetSize()const
{
	return vex.size();
}

void Fire::SetFlag(int i, int flag)
{
	vex[i]->SetExists(flag);
}
