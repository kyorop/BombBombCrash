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
	int GetBombFlag(int index)const;
	int GetBombX(int index)const;
	int GetBombY(int index)const;
	Bomb* GetBombObject(int index)const;
	BombManager(void);
	~BombManager(void);
	
	std::vector<Bomb*> *vbomb;
};

