#pragma once
#include "Route.h"
#include <list>

class Dijkstra;
class Search;
class StopRoute:
	public Route
{
private:
	enum
	{
		STOP,LEFT,RIGHT,UP,DOWN,
	};
private:
	std::list<int> routeList;

	Search *const search;
	Dijkstra *const dijkstra;

	int i_safe;
	int j_safe;

	int hasCalculated;
	int x_next;
	int y_next;

public:
	void DecideGoal(const Enemy &myself);
	void SetRoute(const Enemy &myself);
	int GetRoute(const Enemy &myself);
public:
	StopRoute(void);
	~StopRoute(void);
};

