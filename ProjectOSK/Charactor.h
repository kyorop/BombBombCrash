#pragma once
#include "IRegister.h"
#include "IDrawable.h"
#include "MapObject.h"

class Map;
class Charactor
	:public IRegister,
	public IDrawable,
	public MapObject
{
protected:
	int preX;
	int preY;
	int mv;//�X�s�[�h
	int bombNum;//�o����{���̌�
	int fireLevel;//���S����̉΂̃}�X��(���S�͊܂߂Ȃ�)
	const int id;
	static int idGenerator;
public:
	Charactor(void);
	virtual ~Charactor(void);

	//virtual void SetCharactorState(int flag);
	int GetBombNum(void)const;
	int GetFireLevel(void)const;
	int GetMV(void)const;
	void AddBombNum(void);
	void AddFireLevel(void);
	void AddMV(void);
	virtual void Move() = 0;
	virtual void Draw() = 0;
	void Register();
	virtual int EnableBomb(void)const = 0;
};

