#pragma once
#include "route.h"
#include <list>

class Search;
class Dijkstra;

class Avoid :
	public Route
{
private:
	enum
	{
		STOP,LEFT,RIGHT,UP,DOWN,
	};

private:
	Search *const search;
	Dijkstra *const dijkstra;

	int i_safe;
	int j_safe;

	std::list<int> routeList;

	int hasCalculated;
	int x_next;
	int y_next;

public:
	void DecideGoal(const Enemy &myself);
	void SetRoute(const Enemy &myself);
	int GetRoute(const Enemy &myself);
	Avoid(void);
	~Avoid(void);
};

