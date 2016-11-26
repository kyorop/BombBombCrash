#include "CollisionManager.h"
#include "CollisionUtil.h"
#include "CollisionableObject.h"
#include "Rect.h"

using namespace BombBombCrash;

void BombBombCrash::CollisionManager::Update()
{
	const int size = objects.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i+1; j < size; j++)
		{
			if (CollisionUtil::Test(objects[i]->Rect(), objects[j]->Rect()))
			{
				objects[i]->OnCollide(objects[j].get());
				objects[j]->OnCollide(objects[i].get());
			}
		}
	}
}

void CollisionManager::Add(const std::shared_ptr<CollisionableObject>& object)
{
	objects.push_back(object);
}
