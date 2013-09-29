#pragma once
class Node
{
private:
	int i_preNode;		//ひとつ前のノードを指す
	int j_preNode;		
	int minCost;		//そのノードまでの最短距離
	int settled;		//そのノードまでの最短経路が確定したかどうか
public:
	void Initialize();
	void SetCost(int cost);
	int GetCost()const;
	void SetPreNode(int i_pre, int j_pre);
	//最短経路を確定させる
	void SettleShortestPath();
	int GetSettled()const;
	Node(void);
	virtual ~Node(void);
};

