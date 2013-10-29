#pragma once
#include "IMediator.h"

class Player;
class BombSetManager;
class CharacterSet
{
private:
	Player *const player;
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
	//�e�I�u�W�F�N�g�̕`��n�̍X�V
	void Move();

public:
	CharacterSet(void);
	~CharacterSet(void);

	void Update();
	//�S�ẴI�u�W�F�N�g�̕\��
	void Draw();
};

