#include "ItemManager.h"
#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "DxLib.h"
#define FIRE 0
#define BOMB 1
#define SPEED 2


ItemManager::ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
	{
		this->item[i] = new Item;
	}
}

void ItemManager::SetItem(const Block &block)
{
	item[0]->SetItem(block);//まず一か所決める
	for(int i=1; i<ITEMNUM; i++)
	{
		do
		{
			item[i]->SetItem(block);

			if(ProcessMessage() == -1)//念のため
			break;

		}while( *(item[0]) == *(item[i]) );//初期アイテムと比べる座標が同じなら違うところに描かせる
	}
}

int ItemManager::CheckHitCharactor(Player &player)const
{
	int hitGraph;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->CheckHItCharactor(player)==0 || this->item[i]->CheckHItCharactor(player)==1 || this->item[i]->CheckHItCharactor(player)==2 || this->item[i]->CheckHItCharactor(player)==-1)
		{
			hitGraph = this->item[i]->CheckHItCharactor(player);
			break;
		}
	}
	return hitGraph;
}

void ItemManager::Draw()
{
	for(int i=0; i<ITEMNUM; i++)
		item[i]->Draw();
}

Item* ItemManager::GetFirstItemPointa()
{
	return this->item[0];
}

int ItemManager::GetNowBombNum()
{
	static int bombNum;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->GetFlag() == 0 && this->item[i]->GetKindGraph() == BOMB)
			bombNum++;
	}
	return bombNum;
}

int ItemManager::GetNowFireNum()
{
	static int fireNum;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->GetFlag() == 0 && this->item[i]->GetKindGraph() == FIRE)
			fireNum++;
	}
	return fireNum;
}

int ItemManager::GetNowSpeedNum()
{
	static int speedNum;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->GetFlag() == 0 && this->item[i]->GetKindGraph() == SPEED)
			speedNum++;
	}
	return speedNum;
}

ItemManager::~ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
		delete item[i];
}
