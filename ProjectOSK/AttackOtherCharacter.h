#pragma once
#include "State.h"


class AttackOtherCharacter
	:public State
{
private:
	static const int radiusOfSearch = 8;
private:
	void ChangeState();
	int CheckCharacterAroundMyself(int i_now, int j_now, int* i_to, int* j_to);
public:
	AttackOtherCharacter(IStateChanger *stateMrg);
	~AttackOtherCharacter(void);

	void Analyse(const Enemy &myself)override;
};

