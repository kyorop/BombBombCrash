#pragma once
#include <vector>

class Graph;
class Dijkstra
{
private:
	static const int edgeCost = 1;
	static const int ud[4];		//��_�m�[�h��������悭�㉺���E�𒲂ׂ邽�߂̌����z��
	static const int lr[4];
	Graph *graph;
	int i_currentNode;
	int j_currentNode;
	std::vector<int> vecRoute;
private:
	//start��preNode���璲�ׂāAgoal�܂ł̃��[�g���Z�b�g����
	void SetRoute(int i_start, int j_start, int i_goal, int j_goal);
public:
	void ResetRoute();
	//�X�^�[�g����S�[���܂ł̍ŒZ�����𒲂ׂ�
	void SearchShortestPath(int i_start, int j_start, int i_goal, int j_goal);
	int GetRoute(int num)const;
	void SetBombAction(int bombState);
	Dijkstra();
	virtual ~Dijkstra(void);
};

