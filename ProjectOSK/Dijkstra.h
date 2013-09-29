#pragma once
#include <vector>

class Node;
class Dijkstra
{
private:
	int i_currentNode;
	int j_currentNode;
	std::vector<Node*> vecNode;

public:
	void Search(int i_start, int j_start);
	Dijkstra(int nodeNum);
	~Dijkstra(void);
};

