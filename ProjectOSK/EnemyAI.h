#pragma once
#include "IStateChanger.h"


class State;
class Enemy;
class EnemyAI
	:public IStateChanger
{
private:
	int nextState;
	State* state;
	const Enemy& myself;
private:
	void UpdateState();
public:
	EnemyAI(const Enemy& myself);
	~EnemyAI();
	
	void ChangeState(int nextState)override;
	void Analyse(const Enemy &myself);
	int GetAction(const Enemy &myself);
};

