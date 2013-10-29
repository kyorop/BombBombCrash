#include "GameField.h"
#include "ItemManager.h"
#include "Map.h"
#include "Block.h"

GameField::GameField(void)
	:item(new ItemManager),
	map(new Map),
	block(new Block)
{
	//�A�C�e���̔z�u
	item->SetItem(*block);
}

GameField::~GameField(void)
{
	delete item;
	delete map;
	delete block;
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
	item->Draw();
	block->Draw();
}