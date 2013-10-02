#pragma once
#include "IRegister.h"

class Map;
class Charactor:
	virtual public IRegister
{
protected:
	int x;
	int rx;
	int y;
	int dy;
	int flag;
	int preX;
	int preY;
public:
	//virtual void Draw();
	//virtual void Move();
	virtual int GetX()const;
	virtual int GetY()const;
	virtual int GetRX()const;
	virtual int GetDY()const;
	virtual void SetX(int x);
	virtual void SetY(int y);
	virtual void SetCharactorState(int flag);
	Charactor(void);
	virtual ~Charactor(void);

	
protected:
	//�X�s�[�h
	int mv;
	//�o����{���̌�
	int bombNum;
	//���S����̉΂̃}�X��(���S�͊܂߂Ȃ�)
	int fireLevel;
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

