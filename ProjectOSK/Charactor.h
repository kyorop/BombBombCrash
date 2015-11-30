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
	int mv;//�X�s�[�h
	int bombNum;//�o����{���̌�
	int fireLevel;//���S����̉΂̃}�X��(���S�͊܂߂Ȃ�)
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

