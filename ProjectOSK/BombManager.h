#pragma once
#include <vector>

class Bomb;
class ItemManager;
class Charactor;
class BombManager
{
private:
	std::vector<Bomb*> *vbomb;
public:
	int size;
	void AddBomb(const ItemManager &manageItem);
	void BombSet(const Charactor &charactor);
	void MaintainBomb(int time);
	void Draw();
	int GetBombNum();
	BombManager(void);
	~BombManager(void);
};

