#include "ItemManager.h"
#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "Map.h"
#include "DxLib.h"
#define FIRE 0
#define BOMB 1
#define SPEED 2

ItemManager::ItemManager(void):
	item()
{
	for(int i=0; i<ITEMNUM; i++)
	{
		this->item[i] = new Item;
		Collision::GetInstance()->RegisterWithItem(item[i]);
	}

}

ItemManager::~ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
		delete item[i];
}

void ItemManager::SetItem(const Map &map)
{
	for (int n = 0; n < ITEMNUM; ++n)
	{	
		//int end = 0;
		//while(!end)
		{
			int i = GetRand(MAPSIZE_Y-1);
			int j = GetRand(MAPSIZE_X-1);
			if(map.IsSoftBlock(i,j) == 1)
			{
				item[n]->SetX(j * 32);
				item[n]->SetY(i * 32);
				item[n]->SetFlag(1);
				//if(n == 0)
				//	break;
				//for(int m=0; m<n; ++m)
				//{
				//	if( item[n]->GetX() != item[m]->GetX() )
				//	{
				//		if(m == n-1)
				//		end = 1;
				//	}
				//}
			}
			else
				--n;
		}
	}

}

//void ItemManager::CheckHitCharactor(Charactor *charctor)const
//{
//	for(int i=0; i<ITEMNUM; ++i)
//	{
//		this->item[i]->CheckHItCharactor(charctor);
//	}
//}

void ItemManager::Draw()
{
	for(int i=0; i<ITEMNUM; ++i)
	{
			item[i]->Draw();
	}
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




void ItemManager::Register(void)
{
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->GetFlag() == 1)
			MapState::GetInstance()->SetItemState(this->item[i]->GetX(), this->item[i]->GetY(),1);
		else if(this->item[i]->GetFlag() == 0)
			MapState::GetInstance()->SetItemState(this->item[i]->GetX(), this->item[i]->GetY(),0);
	}
}
