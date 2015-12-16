#include "KeyboardPlayerInput.h"

namespace BombBombCrash
{
	bool KeyboardPlayerInput::GetInputMoveUp()
	{
		return CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W);
	}

	bool KeyboardPlayerInput::GetInputMoveRight()
	{
		return CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D);
	}

	bool KeyboardPlayerInput::GetInputMoveDown()
	{
		return CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S);
	}

	bool KeyboardPlayerInput::GetInputMoveLeft()
	{
		return CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A);
	}

	bool KeyboardPlayerInput::GetInputPutBomb()
	{
		return CheckHitKey(KEY_INPUT_Z);
	}

	KeyboardPlayerInput::KeyboardPlayerInput()
	{

	}


	KeyboardPlayerInput::~KeyboardPlayerInput()
	{
	}	
}
