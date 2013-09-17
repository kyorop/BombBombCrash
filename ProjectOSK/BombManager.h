#pragma once
#include "IDrawable.h"
#include "IRegister.h"
#include <vector>
#include "Key.h"

class Bomb;
class PlayerBomb;
class ItemManager;
class Charactor;
class BombManager:
	virtual public IDrawable, virtual public IRegister
{
protected:
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
	void CheckHit(Charactor *charactor);
	Bomb* GetBombObject(int index)const;
	BombManager(void);
	~BombManager(void);
	
	std::vector<Bomb*> *vbomb;
	void Register(void);
};

