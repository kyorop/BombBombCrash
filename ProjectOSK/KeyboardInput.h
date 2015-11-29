#pragma once
#include "IPlayerInput.h"

class KeyboardInput:public IPlayerInput
{
public:
	bool GetInputMoveUp() override;
	bool GetInputMoveRight() override;
	bool GetInputMoveDown() override;
	bool GetInputMoveLeft() override;
	bool GetInputPutBomb() override;
	KeyboardInput();
	~KeyboardInput();
};

