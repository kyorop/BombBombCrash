#include "SecretCommand.h"
#include "Key.h"
#include "DxLib.h"

int SecretCommand::hasHittedSecretCommand;

SecretCommand::SecretCommand(void)
	:key(new Key()),
	up(0),
	up2(0),
	down(0),
	down2(0),
	right(0),
	right2(0),
	left(0),
	left2(0),
	stack(0)
{
	
}


SecretCommand::~SecretCommand(void)
{
	delete key;
}


void SecretCommand::CheckHitSecretCommand()
{
	if(up == 0 && key->CheckOnePushKey(KEY_INPUT_UP))
	{
		up = 1;
		++stack;
	}
	if(up2 == 0 && up && key->CheckOnePushKey(KEY_INPUT_UP))
	{
		up2 = 1;
		++stack;
	}
	if(down == 0 && up2 && key->CheckOnePushKey(KEY_INPUT_DOWN))
	{
		down = 1;
		++stack;
	}
	if(down2 == 0 && down && key->CheckOnePushKey(KEY_INPUT_DOWN))
	{
		down2 = 1;
		++stack;
	}
	if(left == 0 && down2 && key->CheckOnePushKey(KEY_INPUT_LEFT))
	{
		left = 1;
		++stack;
	}
	if(right == 0 && left && key->CheckOnePushKey(KEY_INPUT_RIGHT))
	{
		right = 1;
		++stack;
	}
	if(left2 == 0 && right && key->CheckOnePushKey(KEY_INPUT_LEFT))
	{
		left2 = 1;
		++stack;
	}
	if(right2 == 0 && left2 && key->CheckOnePushKey(KEY_INPUT_RIGHT))
	{
		right2 = 1;
		++stack;
	}
	

	if(stack == 8)
	{
		hasHittedSecretCommand = 1;
	}
}