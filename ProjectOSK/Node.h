#pragma once
class Node
{
private:
	int i_preNode;		//�ЂƂO�̃m�[�h���w��
	int j_preNode;		
	int minCost;		//���̃m�[�h�܂ł̍ŒZ����
	int settled;		//���̃m�[�h�܂ł̍ŒZ�o�H���m�肵�����ǂ���
public:
	void SetComponent(int i, int j);
	Node(void);
	~Node(void);
};

