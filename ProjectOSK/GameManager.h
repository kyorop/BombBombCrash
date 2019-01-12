#pragma once
#include "MapObject.h"

namespace BombBombCrash
{
interface IGameProgress;
class ControlPassingCollision;
class Drawing;
class GameEffect;
class Timer;
class Player;
class GameObjectManager;
class CollisionManager;
class CollisionableObject;
class GameManager
{
	GameManager();
	~GameManager(){}
	GameManager(const GameManager&);
	GameManager& operator=(const GameManager&);
	GameManager(GameManager&&);
	GameManager& operator=(GameManager&&);
	std::shared_ptr<GameEffect> gameEffect;
	std::list<std::unique_ptr<MapObject>> tasks_;
	std::list<std::unique_ptr<MapObject>> new_tasks_;
	std::list<MapObject*> delete_reserved_tasks_;
	std::list<std::pair<MapObject*, MapObject*>> collision_task_pairs_;

	void Collide();

	void CollisionExit();

	void DeleteTask(std::list<std::unique_ptr<MapObject>>& original_tasks,
		std::list<MapObject*>& delete_tasks);
	
	void AddNewTask(std::list<std::unique_ptr<MapObject>>& original_tasks,
		std::list<std::unique_ptr<MapObject>>& new_tasks);

	void UpdateTaskList(std::list<std::unique_ptr<MapObject>>& original_tasks,
		std::list<std::unique_ptr<MapObject>>& new_tasks, 
		std::list<MapObject*>& delete_tasks);

	bool IsRegistered(MapObject*);

public:
	static GameManager& Instance(){
		static GameManager instance;
		return instance;
	}

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	void AddTask(std::unique_ptr<MapObject> task);
	
	void DeleteTask(MapObject* task);
};

}


