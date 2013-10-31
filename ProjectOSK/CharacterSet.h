#pragma once
#include "IMediator.h"

class Charactor;
class BombSetManager;
class CharacterSet
{
private:
	Charactor *const character;
	BombSetManager *const bomb;
	int currentSpeed;
	int currentBombNum;
	int currentFireLevel;
	int pre_i_bombSet;
	int pre_j_bombSet;
private:
	//�v���C���[�̃A�C�e���擾�ő��₷
	void UpdateNumber();
	//���W��t���O�̃Z�b�g
	void Set();
public:
	CharacterSet(Charactor *character);
	~CharacterSet(void);

	void Update();
	//�S�ẴI�u�W�F�N�g�̕\��
	void Draw();
};

