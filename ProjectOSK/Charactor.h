#pragma once
#include "IRegister.h"
#include "IDrawable.h"
#include "MapObject.h"

class Map;
class Charactor:public IRegister,public IDrawable,public MapObject
{
protected:
	int preX;
	int preY;
	int mv;//スピード
	int bombNum;//出せるボムの個数
	int fireLevel;//中心からの火のマス数(中心は含めない)
	const int id;
	static int idGenerator;
	virtual bool PutBomb() = 0;
public:
	Charactor(void);
	virtual ~Charactor(void);

	int GetBombNum()const;
	int GetFireLevel()const;
	int GetMV()const;
	void AddBombNum();
	void AddFireLevel();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetMv() = 0;
	virtual void Move() = 0;
	
	void Register();
};

