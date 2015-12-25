#include "Explosion.h"
#include "MapState.h"
#include "Image.h"
#include "Collision.h"
#include "Bomb.h"

#define DHIT 6

using namespace BombBombCrash;
using namespace std;


//FireBlock

FireBlock::~FireBlock(void)
{
}

void FireBlock::Set(int x, int y)
{
}

void FireBlock::SetExplosion(int flag)
{
	explosion = flag;
}

int FireBlock::GetExplosion()
{
	return explosion;
}


//FirePillar

shared_ptr<IFireIterator> FirePillar::Iterator()
{
	return make_shared<FirePillarIterator>(*this);
}

FirePillar::FirePillar(const shared_ptr<FireBlock>& center):
center(center)
{
}

void FirePillar::Add()
{
	auto last = FireBlockAt(Size() - 1);
	auto newBlock = make_shared<FireBlock>(last.Position()+Direction(), last.Width(), last.Height());
	pillar.push_back(newBlock);
}

int FirePillar::Size() const
{
	return pillar.size();
}

FireBlock FirePillar::FireBlockAt(int i)
{
	return *pillar[i];
}


//UpFirePillar

ln::Vector2 UpFirePillar::Direction()
{
	return ln::Vector2(0,-32);
}


//RightFirePillar

ln::Vector2 RightFirePillar::Direction()
{
	return ln::Vector2(32, 0);
}


//DownFire

ln::Vector2 DownFirePillar::Direction()
{
	return ln::Vector2(0, 32);
}


//LeftFirePillar

ln::Vector2 LeftFirePillar::Direction()
{
	return ln::Vector2(-32, 0);
}


/*
FirePillarIterator
*/

FirePillarIterator::FirePillarIterator(const FirePillar& firePillar): 
//fire(make_shared<FirePillar>(firePillar)),
index(0)
{

}

bool FirePillarIterator::HasNext()
{
	return fire->Size() > index;
}

MapObject FirePillarIterator::Next()
{
	return fire->FireBlockAt(index++);
}


//Fire

Fire::Fire():
nowFireLevel(1),
fuse(0),
explosion(0),
beforeExplosion(),
image_fire(Image::GetInstance()->GetImage(Image::FIRE)),
firePillars(4)
{
	firePillars[Up] = make_shared<UpFirePillar>(center);
	firePillars[Right] = make_shared<RightFirePillar>(center);
	firePillars[Left] = make_shared<LeftFirePillar>(center);
	firePillars[Down] = make_shared<DownFirePillar>(center);

	Collision::Instance()->RegisterWithFire(this);
}

Fire::~Fire(void)
{
}

void Fire::FireUp()
{
	++nowFireLevel;
}

void Fire::Update(const Bomb &bomb)
{
	if (bomb.Exists() && explosion == 0 && fuse == 0)
	{
		fuse = TRUE;
		for (int i = 0, size = vex.size(); i<size; ++i)
		{
			vex[i]->Set(bomb.GetX(), bomb.GetY());
		}
	}

	if (fuse == TRUE && bomb.Exists() == FALSE)
	{
		fuse = FALSE;
		explosion = TRUE;
		for (int i = 0, size = vex.size(); i<size; ++i)
		{
			vex[i]->SetExplosion(TRUE);
		}
	}

	Maintain();
}

void Fire::Maintain()
{
	if (explosion == TRUE)
	{
		if (retainFire.CountDownFrame(displayingTime) == true)
		{
			explosion = FALSE;
			for (int i = 0, size = vex.size(); i<size; i++)
			{
				vex[i]->SetExplosion(FALSE);
			}
		}
	}
}

void Fire::Draw()
{
	if (this->explosion == TRUE)
	{
		for (int i = 0, size = vex.size(); i<size; ++i)
		{
			if (vex[i]->GetExplosion())
				DrawGraph(vex[i]->GetX(), vex[i]->GetY(), image_fire, FALSE);
		}
	}
}

void Fire::Register(void)
{
	for (int i = 0, size = vex.size(); i<size; ++i)
	{
		if (vex[i]->GetExplosion() == 0)
			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 0);
		else if (vex[i]->GetExplosion() == 1)
			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 1);
	}
}

int Fire::GetX(int i)const
{
	return vex[i]->GetX();
}

int Fire::GetY(int i)const
{
	return vex[i]->GetY();
}

int Fire::GetFlag(int i)const
{
	return vex[i]->GetExplosion();
}

int Fire::GetSize()const
{
	return vex.size();
}

void Fire::SetFlag(int i, int flag)
{
	vex[i]->SetExplosion(flag);
}

int Fire::Firepower(void)
{
	return nowFireLevel;
}
