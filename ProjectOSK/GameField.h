#pragma once

class Map;
class Block;
class ItemManager;
class GameField
{
private:
	ItemManager *const item;
	Map *const map;
	Block *const block;
public:
	GameField(void);
	~GameField(void);
	void Initialize();
	void Update();
	void Draw();
};

