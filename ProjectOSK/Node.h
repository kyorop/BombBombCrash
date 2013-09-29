#pragma once
class Node
{
private:
	int i_preNode;		//�ЂƂO�̃m�[�h���w��
	int j_preNode;		
	int minCost;		//���̃m�[�h�܂ł̍ŒZ����
	int settled;		//���̃m�[�h�܂ł̍ŒZ�o�H���m�肵�����ǂ���
public:
	void Initialize();
	void SetCost(int cost);
	int GetCost()const;
	void SetPreNode(int i_pre, int j_pre);
	//�ŒZ�o�H���m�肳����
	void SettleShortestPath();
	int GetSettled()const;
	Node(void);
	virtual ~Node(void);
};

