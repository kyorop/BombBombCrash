#pragma once
//#include <vector>
#include <list>

class Graph;
class Dijkstra
{
private:
	static const int edgeCost = 1;
	//��_�m�[�h��������悭�㉺���E�𒲂ׂ邽�߂̌����z��
	static const int ud[4];
	static const int lr[4];
	Graph *graph;
	int i_currentNode;
	int j_currentNode;
	//std::vector<int> vecRoute;
private:
	//start��preNode���璲�ׂāAgoal�܂ł̃��[�g���Z�b�g����
	void SetRoute(int i_start, int j_start, int i_goal, int j_goal, std::list<int> *shortestRoute);
public:
	void SearchShortestPath(int i_from, int j_from, int i_to, int j_to, std::list<int> *shortestRoute);
	/*void ResetRoute();*/
	//�X�^�[�g����S�[���܂ł̍ŒZ�����𒲂ׂ�
	
	/*int GetRoute(int num)const;
	void SetBombAction(int bombState);*/

	Dijkstra();
	virtual ~Dijkstra(void);
};

