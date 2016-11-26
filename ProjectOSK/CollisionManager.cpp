#include "CollisionManager.h"
#include "CollisionUtil.h"
#include "CollisionableObject.h"
#include "Rect.h"

using namespace BombBombCrash;

void BombBombCrash::CollisionManager::Update()
{
	CheckRemove();
	CheckCollide();
}

void CollisionManager::CheckCollide()
{
	for (auto i = begin(objects); i != end(objects); ++i)
	{
		auto temp_i = i;
		for (auto j = ++temp_i ; j != end(objects); ++j)
		{
			if (CollisionUtil::Test((*i)->Rect(), (*j)->Rect()))
			{
				(*i)->OnCollide((*j).get());
				(*j)->OnCollide((*i).get());
			}
		}
	}
}

void CollisionManager::CheckRemove()
{
	objects.remove_if([](const std::shared_ptr<CollisionableObject> object)
	{
		return !object->Exists();
	});
}

void CollisionManager::Add(const std::shared_ptr<CollisionableObject>& object)
{
	objects.push_back(object);
}
