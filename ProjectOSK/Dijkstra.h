#pragma once
#include <vector>

class Graph;
class Dijkstra
{
private:
	static const int edgeCost = 1;
	static const int ud[4];		//基点ノードから効率よく上下左右を調べるための向き配列
	static const int lr[4];
	Graph *graph;
	int i_currentNode;
	int j_currentNode;
	std::vector<int> vecRoute;
private:
	//startのpreNodeから調べて、goalまでのルートをセットする
	void SetRoute(int i_start, int j_start, int i_goal, int j_goal);
public:
	void ResetRoute();
	//スタートからゴールまでの最短距離を調べる
	void SearchShortestPath(int i_start, int j_start, int i_goal, int j_goal);
	int GetRoute(int num)const;
	void SetBombAction(int bombState);
	Dijkstra();
	virtual ~Dijkstra(void);
};

