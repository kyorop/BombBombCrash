#include "NewFire.h"
#include "Image.h"
#include "Timer.h"

using namespace BombBombCrash;

int NewFire::imageHandle;

void BombBombCrash::NewFire::KillForwardFire()
{
	SetExists(false);
	if (!next.expired())
	{
		auto nextptr = next.lock();
		if (nextptr != nullptr)
			nextptr->KillForwardFire();
	}
}


void BombBombCrash::NewFire::RecordDeletedObjectBackward(CollisionableObject* deletedObject)
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

NewFire::NewFire(ln::Vector2 position, int width, int height, const std::weak_ptr<NewFire>& pre, const std::weak_ptr<NewFire>& next): 
CollisionableObject(position, width, height),
next(next),
pre(pre),
deletedObject(nullptr),
timer(std::make_shared<Timer>())
{
}


BombBombCrash::MapObject::GameObjectType NewFire::Type() const
{
	return GameObjectType::Fire;
}

void NewFire::Initialize(GameManager& game)
{
	imageHandle = Image::GetInstance()->GetImage(Image::FIRE);
}

void BombBombCrash::NewFire::Update(GameManager& game)
{
	deletedObject = nullptr;
	if (timer->CountDownFrame(1 * 1000))
	{
		SetExists(false);
	}
}

void BombBombCrash::NewFire::Draw(const GameManager& game)
{
	DrawGraph(X(), Y(), imageHandle, true);
}

void NewFire::SetPre(const std::weak_ptr<NewFire>& pre)
{
	this->pre = pre;
}

void NewFire::SetNext(const std::weak_ptr<NewFire>& next)
{
	this->next = next;
}

void BombBombCrash::NewFire::OnCollide(CollisionableObject* object)
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
