#pragma once
#include "IMediator.h"

class Player;
class BombManager;
class BlastManager;
class CharacterSet
	//:public IMediator
{
private:
	Player *player;
	BombManager *bomb;
	BlastManager *fire;
	int currentSpeed;
	int currentBombNum;
	int currentFireLevel;
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


	//void CreateColleague() override;
	//void ColleagueChange() override;

};

