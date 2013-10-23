#pragma once
#include "IDrawable.h"
#include <vector>
#include "Key.h"

class Bomb;
class PlayerBomb;
class ItemManager;
class Charactor;
class BombManager:
	virtual public IDrawable
{
protected:
	int nowBombNum;
	Key key;
public:
	int size;
	virtual void Add();
	void BombSet(int x, int y);
	void MaintainBomb();
	void Draw();
	int GetBombNum();
	int GetFlag(int index)const;
	int GetX(int index)const;
	int GetY(int index)const;
	void CheckHit(Charactor *charactor);
	Bomb* GetBombObject(int index)const;
	BombManager(void);
	virtual ~BombManager(void);
	int GetAllBombNum()const;
	std::vector<Bomb*> bomb;
	void Register(const Charactor &chara);
};

