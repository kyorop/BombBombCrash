#include "BombManager.h"
#include "Bomb.h"
#include "ItemManager.h"
#include "Player.h"
#define BOMB 1

BombManager::BombManager(void):
	vbomb(new std::vector<Bomb*>(1))
{
	(*vbomb)[0] = new Bomb;
}

void BombManager::AddBomb(const ItemManager &manageItem, Player &player)
{
	if(manageItem.CheckHitCharactor(player) == BOMB)
		vbomb->push_back(new Bomb);
}

void BombManager::BombSet(const Player &player,const Map &map)
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		(*vbomb)[i]->BombSet(player, map);
	}
}

void BombManager::Draw()
{
	for(int i=0, size=vbomb->size(); i<size; ++i) 
	{
		(*vbomb)[i]->Draw();
	}
}

BombManager::~BombManager(void)
{
	std::vector<Bomb*>::iterator it = vbomb->begin();
	for(it; it != vbomb->end(); ++it)
	{
		delete *it;
	}
	delete vbomb;
}
