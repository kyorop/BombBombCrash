#pragma once
#include "route.h"
#include <vector>
#include <list>

class Search;
class Dijkstra;
class Target :
	public Route
{
private:
enum
{
	END = -1,
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BOMBSET,
	BOMBSETOFF,
};
	static const int radiusOfSearch = 8;
private:
	std::vector<int> i_toList;
	std::vector<int> j_toList;
	int rand;
	std::list<int> routeList;
	Search *const search;
	Dijkstra *const dijkstra;
	int hasCalculated;
	int x_next;
	int y_next;
private:
	int CheckExistenceOfCharacterAroundMyself(int i, int j, int *i_to, int *j_to);
public:
	Target(void);
	~Target(void);
	void DecideGoal(const Enemy &myself);
	void SetRoute(const Enemy &myself);
	int GetRoute(const Enemy &myself);

};

