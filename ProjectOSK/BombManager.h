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
	int bombImage[60];
public:
	int size;
	virtual void AddBomb(const Charactor &charactor);
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
	virtual ~BombManager(void);
	
	std::vector<Bomb*> *vbomb;
	void Register(const Charactor &chara);
};

