#pragma once
#include "IDrawable.h"
#include <vector>
#include "Key.h"

class Bomb;
class ItemManager;
class Charactor;
class BombManager:
	virtual public IDrawable
{
private:
	int nowBombNum;
	Key key;
public:
	int size;
	void AddBomb(const Charactor &charactor);
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

