#pragma once
#include <vector>

class Node;
class Graph;
class Dijkstra
{
private:
	static const int cost = 1;
	static const int ud[4];		//��_�m�[�h��������悭�㉺���E�𒲂ׂ邽�߂̌����z��
	static const int lr[4];
	Graph *graph;
	int i_currentNode;
	int j_currentNode;
	std::vector<int> vecRoute;
private:
	void SetRoute();
public:
	void SearchShortestPath(int i_start, int j_start, int i_goal, int j_goal);
	Dijkstra(int nodeNum);
	virtual ~Dijkstra(void);
};

