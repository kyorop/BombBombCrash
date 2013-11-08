#pragma once
#include "GameConstant.h"
#include "IStateChanger.h"

class State;
class Enemy;
class EnemyAI
	:public IStateChanger
{
private:
	int nextState;
	State* state;
private:
	void UpdateState();
public:
	EnemyAI();
	~EnemyAI(void);
	
	void ChangeState(int nextState)override;
	void Analyse(const Enemy &myself);
	int GetAction(const Enemy &myself);


	//static void ShowState(int x, int y);
};

