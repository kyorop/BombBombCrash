#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"
#include <vector>
#include <list>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Player;
class Enemy:
	public Charactor, virtual public IDrawable, virtual public IRegister
{
private:
	int graph[20];
	int muki;
	int animpat;
	int resetRoutine;
	int bombSet;
	int action[10];
	int actionloop;
	int visited[MAPSIZE_Y][MAPSIZE_X];
	struct Component
	{
		int i;
		int j;

		Component(int i=0, int j=0)
		{
			this->i = i;
			this->j = j;
		}
	};
	std::vector<Component*> vecBranch;
	
	std::list<Component*> listRoute;
public:
	std::vector<Component*> vecGoal;
	void DeleteComponent();
	Enemy(int x, int y);
	~Enemy(void);
	void Analyse();
	void Move(int g_lastTime);
	void Draw();
	int GetBombSet(void)const;
	void SetDestination(const int i, const int j);
	int CheckAbleBombSet();
};

