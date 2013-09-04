#include "ItemManager.h"
#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "DxLib.h"

ItemManager::ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
	{
		this->item[i] = new Item;
	}
}

void ItemManager::SetItem(const Block &block)
{
	item[0]->SetItem(block);//�܂��ꂩ�����߂�
	for(int i=1; i<ITEMNUM; i++)
	{
		do
		{
			item[i]->SetItem(block);

			if(ProcessMessage() == -1)//�O�̂���
			break;

		}while( *(item[0]) == *(item[i]) );//�����A�C�e���Ɣ�ׂ���W�������Ȃ�Ⴄ�Ƃ���ɕ`������
	}
}

void ItemManager::CheckHitCharactor(Player *player)
{
	for(int i=0; i<ITEMNUM; i++)
		this->item[i]->CheckHItCharactor(player);
}

void ItemManager::Draw()
{
	for(int i=0; i<ITEMNUM; i++)
		item[i]->Draw();
}

ItemManager::~ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
		delete item[i];
}
