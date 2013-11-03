#pragma once
#include "State.h"
#include <list>

class Search;
class Dijkstra;

class Avoid :
	public State
{
public:
	Avoid(IStateChanger *stateMrg);
	~Avoid(void);
private:
	void ChangeState()override;
public:
	void Analyse(const Enemy &myself)override;
};

