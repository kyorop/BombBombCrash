#include "Fire.h"
#include "Image.h"
#include "Timer.h"

using namespace BombBombCrash;

int Fire::imageHandle;

void BombBombCrash::Fire::KillForwardFire()
{
	SetExists(false);
	if (!next.expired())
	{
		auto nextptr = next.lock();
		if (nextptr != nullptr)
			nextptr->KillForwardFire();
	}
}


void BombBombCrash::Fire::RecordDeletedObjectBackward(CollisionableObject* deletedObject)
{
	if (!pre.expired())
	{
		auto preptr = pre.lock();
		if (preptr != nullptr)
		{
			preptr->deletedObject = deletedObject;
			preptr->RecordDeletedObjectBackward(deletedObject);
		}
	}
}

Fire::Fire(ln::Vector2 position, int width, int height, const std::weak_ptr<Fire>& pre, const std::weak_ptr<Fire>& next): 
CollisionableObject(position, width, height),
next(next),
pre(pre),
deletedObject(nullptr),
timer(std::make_shared<Timer>())
{
}


BombBombCrash::MapObject::GameObjectType Fire::Type() const
{
	return GameObjectType::Fire;
}

void Fire::Initialize(GameManager& game)
{
	imageHandle = Image::GetInstance()->GetImage(Image::FIRE);
}

void BombBombCrash::Fire::Update(GameManager& game)
{
	deletedObject = nullptr;
	if (timer->CountDownFrame(1 * 1000))
	{
		SetExists(false);
	}
}

void BombBombCrash::Fire::Draw(const GameManager& game)
{
	DrawGraph(X(), Y(), imageHandle, true);
}

void Fire::SetPre(const std::weak_ptr<Fire>& pre)
{
	this->pre = pre;
}

void Fire::SetNext(const std::weak_ptr<Fire>& next)
{
	this->next = next;
}

void BombBombCrash::Fire::OnCollide(CollisionableObject* object)
{
	if (!Exists())
		return;

	KillForwardFire();
	if (deletedObject != nullptr)
		deletedObject->SetExists(true);
	this->SetExists(false);

	if (object->Type()==HardBlock)
		deletedObject = nullptr;
	else
	{
		object->SetExists(false);
		deletedObject = object;
	}

	RecordDeletedObjectBackward(deletedObject);
}
