#pragma once
class Node
{
private:
	int i_preNode;		//ひとつ前のノードを指す
	int j_preNode;		
	int minCost;		//そのノードまでの最短距離
	int settled;		//そのノードまでの最短経路が確定したかどうか
public:
	void SetComponent(int i, int j);
	Node(void);
	~Node(void);
};

