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

int ItemManager::CheckHitCharactor(Charactor &charctor)const
{
	int hitGraph = -1;
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->CheckHItCharactor(charctor)==0 || this->item[i]->CheckHItCharactor(charctor)==1 || this->item[i]->CheckHItCharactor(charctor)==2 /*|| this->item[i]->CheckHItCharactor(charctor)==-1*/)
		{
			hitGraph = this->item[i]->CheckHItCharactor(charctor);
			break;
		}
	}
	return hitGraph;
}

void ItemManager::Draw()
{
	for(int i=0; i<ITEMNUM; ++i)
		item[i]->Draw();
}

Item* ItemManager::GetItemInstance(int index)const
{
	return this->item[index];
}

int ItemManager::GetBombState()const
{
	int bombNum=0;
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->GetKindGraph() == BOMB && this->item[i]->GetFlag() == 0)
			bombNum++;
	}
	return bombNum; 
}

int ItemManager::GetFireState()const
{
	int fireNum=0;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->GetKindGraph() == FIRE && this->item[i]->GetFlag() == 0)
			fireNum++;
	}
	return fireNum;
}

int ItemManager::GetSpeedState()const
{
	int speedNum=0;
	for(int i=0; i<ITEMNUM; i++)
	{
		if(this->item[i]->GetFlag() == 0 && this->item[i]->GetKindGraph() == SPEED)
			speedNum++;
	}
	return speedNum;
}

int ItemManager::GetCharactorHitBombNum()const
{
	int bombNum=0;
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->GetKindGraph() == BOMB && this->item[i]->GetCharactorHit() == TRUE)
			bombNum++;
	}
	return bombNum;
}


int ItemManager::GetCharactorHitSpeedNum()const
{
	int speedNum=0;
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->GetKindGraph() == SPEED && this->item[i]->GetCharactorHit() == TRUE)
			speedNum++;
	}
	return speedNum;
}

ItemManager::~ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
		delete item[i];
}
