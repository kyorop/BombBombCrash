#pragma once
#include <vector>

class Bomb;
class Player;
class Map;
class ItemManager;
class Charactor;
class BombManager
{
private:
	std::vector<Bomb*> *vbomb;
public:
	void AddBomb(const ItemManager &manageItem);
	void BombSet(const Charactor &charactor);
	void Draw();
	BombManager(void);
	~BombManager(void);
};

