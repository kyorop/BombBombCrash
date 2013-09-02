#pragma once
#include <vector>

class Bomb;
class Player;
class Map;
class ItemManager;
class BombManager
{
private:
	std::vector<Bomb*> *vbomb;
public:
	void AddBomb(const ItemManager &manageItem, Player &player);
	void BombSet(const Player &player,const Map &map);
	void Draw();
	BombManager(void);
	~BombManager(void);
};

