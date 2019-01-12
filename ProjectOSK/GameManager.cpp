#include "GameManager.h"
#include "GameEffect.h"
#include "MapState.h"
#include "Player.h"
#include "CollisionUtil.h"
#include "Rect.h"
#include "HardBlock.h"
#include "MapFactory.h"

using namespace BombBombCrash;


GameManager::GameManager():
gameEffect(std::make_shared<GameEffect>()),
tasks_()
{
}

void GameManager::Initialize()
{
	AddTask(std::make_unique<Player>(ln::Vector2(32 * 13, 32), Player::KEYBORAD));
	MapFactory map_maker;
	map_maker.Create();
	MapState::GetInstance()->Initialize();
}

void GameManager::Update()
{
	gameEffect->Update(*this);

	UpdateTaskList(tasks_, new_tasks_, delete_reserved_tasks_);

	for (auto& task : tasks_)
	{
		if (task->Exists())
			task->Update();
	}

	CollisionExit();
	Collide();
	

	for (auto& task : tasks_)
	{
		if (task->Exists())
			task->LateUpdate();
	}
}

void GameManager::Draw()
{
	gameEffect->Draw(*this);

	for (auto& task : tasks_)
	{
		if (task->Exists())
			task->Draw();
	}
}

void GameManager::Finalize()
{
}


void GameManager::AddTask(std::unique_ptr<MapObject> task){
	new_tasks_.push_back(move(task));
}


void GameManager::DeleteTask(MapObject* task){
	auto itr = find(begin(delete_reserved_tasks_), end(delete_reserved_tasks_), task);
	if (itr == end(delete_reserved_tasks_))
	{
		task->OnDeleted();
		delete_reserved_tasks_.push_back(task);
	}
}

void GameManager::Collide()
{
	for (auto itr_object = begin(tasks_); itr_object != end(tasks_); ++itr_object)
	{
		for (auto itr_other = itr_object; itr_other != end(tasks_); ++itr_other)
		{
			if (itr_object == itr_other)
				continue;

			if (CollisionUtil::Test((*itr_object)->Rect(), (*itr_other)->Rect()))
			{
				(*itr_object)->OnCollide(**itr_other);
				(*itr_other)->OnCollide(**itr_object);
				collision_task_pairs_.emplace_back(itr_object->get(), itr_other->get());
			}
		}
	}
}

void GameManager::CollisionExit()
{
	for (auto& collision_pair : collision_task_pairs_)
	{
		auto object = collision_pair.first;
		auto other = collision_pair.second;
		if (IsRegistered(object) && IsRegistered(other))
		{
			if (!CollisionUtil::Test(object->Rect(), other->Rect()))
			{
				object->OnCollisionExit(*other);
				other->OnCollisionExit(*object);
			}
		}
	}

	collision_task_pairs_.clear();
}

void GameManager::DeleteTask(std::list<std::unique_ptr<MapObject>>& original_tasks,
	std::list<MapObject*>& delete_tasks)
{
	for (auto delete_task : delete_tasks)
	{
		auto itr = std::find_if(begin(original_tasks), end(original_tasks),[delete_task](std::unique_ptr<MapObject>& task)
		{
			return task.get() == delete_task;
		});
		original_tasks.erase(itr);
	}
}

void GameManager::AddNewTask(std::list<std::unique_ptr<MapObject>>& original_tasks,
	std::list<std::unique_ptr<MapObject>>& new_tasks)
{
	for (auto& new_task : new_tasks)
	{
		original_tasks.push_back(move(new_task));
	}
}

void GameManager::UpdateTaskList(std::list<std::unique_ptr<MapObject>>& original_tasks, 
	std::list<std::unique_ptr<MapObject>>& new_tasks,
	std::list<MapObject*>& delete_tasks)
{
	if (!delete_tasks.empty())
	{
		for (auto delete_task : delete_tasks)
		{
			if (IsRegistered(delete_task))
				delete_task->Finalize();
		}

		DeleteTask(original_tasks, delete_tasks);
		delete_tasks.clear();
	}

	if (!new_tasks.empty())
	{
		for (auto& new_task : new_tasks)
			new_task->Initialize();

		AddNewTask(original_tasks, new_tasks);
		new_tasks.clear();
	}
}

bool GameManager::IsRegistered(MapObject* task)
{
	auto itr = find_if(begin(tasks_), end(tasks_), [task](std::unique_ptr<MapObject>& registered_task)
	{
		return registered_task.get() == task;
	});
	return itr != end(tasks_);
}
