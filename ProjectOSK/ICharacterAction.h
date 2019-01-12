#pragma once

class ICharacterAction
{
public:
	virtual ~ICharacterAction(){}
	virtual void Move() = 0;
	virtual void PutBomb() = 0;
};

