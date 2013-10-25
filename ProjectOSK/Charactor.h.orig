#pragma once
#include "IRegister.h"
<<<<<<< HEAD
#include "MapObject.h"
=======
#include "IDrawable.h"
>>>>>>> develop

class Map;
class Charactor
	:public IRegister,
<<<<<<< HEAD
	public MapObject
=======
	public IDrawable
>>>>>>> develop
{
protected:
	int preX;
	int preY;
	//スピード
	int mv;
	//出せるボムの個数
	int bombNum;
	//中心からの火のマス数(中心は含めない)
	int fireLevel;
public:
	Charactor(void);
	virtual ~Charactor(void);
	//virtual void Draw();
	//virtual void Move();
	virtual void SetCharactorState(int flag);
public:
	virtual int GetBombNum(void)const;
	virtual int GetFireLevel(void)const;
	virtual int GetMV(void)const;
	virtual void AddBombNum(void);
	virtual void AddFireLevel(void);
	virtual void AddMV(void);
	virtual int GetBombSet(void)const;
	virtual void Register();
};

