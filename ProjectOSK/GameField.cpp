#include "GameField.h"
#include "ItemManager.h"
#include "Map.h"

GameField::GameField(void)
	:item(new ItemManager),
	map(new Map)
{

}

GameField::~GameField(void)
{
	delete item;
	delete map;
}

void GameField::Initialize()
{
	item->SetItem(*map);
}

void GameField::Update()
{
	map->Register();
}

void GameField::Draw()
{
	map->Draw();
	item->Draw();
}