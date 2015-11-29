#include "KeyboardPlayerInput.h"

bool KeyboardPlayerInput::GetInputMoveUp()
{
	return CheckHitKey(KEY_INPUT_UP);
}

bool KeyboardPlayerInput::GetInputMoveRight()
{
	return CheckHitKey(KEY_INPUT_RIGHT);
}

bool KeyboardPlayerInput::GetInputMoveDown()
{
	return CheckHitKey(KEY_INPUT_DOWN);
}

bool KeyboardPlayerInput::GetInputMoveLeft()
{
	return CheckHitKey(KEY_INPUT_LEFT);
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

interface ITestInter
{

};
