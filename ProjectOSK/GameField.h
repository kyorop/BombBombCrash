#pragma once

class Map;
class ItemManager;
class GameField
{
private:
	ItemManager *const item;
	Map *const map;
public:
	GameField(void);
	~GameField(void);
	void Initialize();
	void Update();
	void Draw();
};

