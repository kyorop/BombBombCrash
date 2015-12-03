#include "GameField.h"
#include "ItemManager.h"
#include "Map.h"
#include "Block.h"

GameField::GameField(void)
	:item(new ItemManager),
	map(new Map),
	block(new Block )
{
	//�A�C�e���̔z�u
	item->Initialize(*block);
}

GameField::~GameField(void)
{
	delete block;
	delete map;
	delete item;
}

void GameField::Initialize()
{

}

void GameField::Update()
{
	map->Register();
	block->Register();
}

void GameField::Draw()
{
	map->Draw();
	block->Draw();
}