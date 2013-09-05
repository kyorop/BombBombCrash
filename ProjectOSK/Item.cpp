#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include"DxLib.h"
#define FIRE 0
#define BOMB 1
#define SPEED 2
#define DHIT 10

int Item::graph[KINDITEMNUM];

Item::Item(void):
	//i_graph(BOMB)
	i_graph(GetRand(KINDITEMNUM-1))//���̃A�C�e�����o�������߂�
{
	LoadDivGraph("itemup.bmp", 3, 3, 1, 32, 32, Item::graph, FALSE);
	this->flag = 1;
}

void Item::SetItem(const Block &block)
{
	int i = GetRand(MAPSIZE_Y);
	int j = GetRand(MAPSIZE_X);
	
	while(block.GetID(i, j) != 2)//ID�����ɂȂ�܂ŗ����擾
	{
		i = GetRand(MAPSIZE_Y);
		j = GetRand(MAPSIZE_X);

		if(ProcessMessage() == -1)//�O�̂���
			break;
	}
	this->x = 32 * j;
	this->y = 32 * i;
}

void Item::Draw()
{
	if(this->flag == 1)
	{
		DrawGraph(this->x, this->y, this->graph[i_graph],FALSE);
	}
}

int Item::GetKindGraph()
{
	return this->i_graph;
}

int Item::CheckHItCharactor(const Charactor &charactor)
{
	if(this->flag == 1)//���̂��\������Ă���Ƃ�
	{
		if(this->x+32-DHIT > charactor.GetX() && this->x+DHIT < charactor.GetRX() && this->y+DHIT < charactor.GetDY() && charactor.GetY() < this->y+32-DHIT)
		{
			this->flag = 0;
			return this->i_graph;
		}
		else
			return -1;
	}
	else
		return -1;
}

Item::~Item(void)
{
}

//���Z�q�I�[�o�[���[�h
bool Item::operator==(const Item &other)
{
	if(this->x == other.x && this->y == other.y)
		return true;
	else
		return false;
}

bool Item::operator==(const Player &player)
{
	return 0;
}