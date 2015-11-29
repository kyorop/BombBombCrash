#include "KeyboardInput.h"

bool KeyboardInput::GetInputMoveUp()
{
	return CheckHitKey(KEY_INPUT_UP);
}

bool KeyboardInput::GetInputMoveRight()
{
	return CheckHitKey(KEY_INPUT_RIGHT);
}

bool KeyboardInput::GetInputMoveDown()
{
	return CheckHitKey(KEY_INPUT_DOWN);
}

bool KeyboardInput::GetInputMoveLeft()
{
	return CheckHitKey(KEY_INPUT_LEFT);
}

bool KeyboardInput::GetInputPutBomb()
{
	return CheckHitKey(KEY_INPUT_Z);
}

KeyboardInput::KeyboardInput()
{

}


KeyboardInput::~KeyboardInput()
{
}

interface ITestInter
{

};
