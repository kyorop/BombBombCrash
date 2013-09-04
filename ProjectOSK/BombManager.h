#pragma once
#include <vector>

class Bomb;
class ItemManager;
class Charactor;
class BombManager
{
private:
	int nowBombNum;
public:
	int size;
	void AddBomb(const ItemManager &manageItem);
	void BombSet(const Charactor &charactor);
	void MaintainBomb();
	void Draw();
	int GetBombNum();
	BombManager(void);
	~BombManager(void);
	
	std::vector<Bomb*> *vbomb;
};

