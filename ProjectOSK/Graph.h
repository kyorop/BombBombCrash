#pragma once
#include "Node.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Graph
{
private:
	//���ׂẴ}�X���m�[�h�Ƃ݂�
	Node nodeMatrix[MAPSIZE_Y][MAPSIZE_X];
public:
	//�e�m�[�h�ɃA�N�Z�X����
	Node* GetNode(int i, int j);
	void Initialize();
	Graph(void);
	virtual ~Graph(void);
};

