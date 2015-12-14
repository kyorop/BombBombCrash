#pragma once
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

namespace BombBombCrash
{
	class Graph
	{
	private:
		class Node
		{
		public:
			//�ЂƂO�̃m�[�h���w��
			int i_preNode;		
			int j_preNode;
			//���̃m�[�h�܂ł̍ŒZ����
			int minCost;
			//���̃m�[�h�܂ł̍ŒZ�o�H���m�肵�����ǂ���
			int settled;
		public:
			Node(void);
			~Node(void);
		};
		//���ׂẴ}�X���m�[�h�Ƃ݂�
		Node nodeMatrix[MAPSIZE_Y][MAPSIZE_X];
	public:
		//Node* GetNode(int i, int j);
		void Initialize();
		void SetCost(int i, int j, int cost);
		int GetCost(int i, int j)const;
		void SetPreNode(int i, int j, int i_pre, int j_pre);
		int GetPreNode_i(int i, int j)const;
		int GetPreNode_j(int i, int j)const;
		void SettleShortestPath(int i, int j);
		int GetSettled(int i, int j)const;
		Graph(void);
		virtual ~Graph(void);
	};
}




