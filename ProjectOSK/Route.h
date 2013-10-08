#pragma once
#include <list>

class Enemy;
class Route
{
public:
	//virtual void Analyse() = 0;
	virtual void DecideGoal(const Enemy &myself) = 0;
	virtual void SetRoute(const Enemy &myself) = 0;
	virtual int GetRoute(const Enemy &myself) = 0;
	virtual ~Route(void){}
};

