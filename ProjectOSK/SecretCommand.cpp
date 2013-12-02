#include "SecretCommand.h"
#include "DxLib.h"

int SecretCommand::hasHittedSecretCommand;

SecretCommand::SecretCommand(void)
{
	commandForComparison.push(CTRL_CODE_UP);
	commandForComparison.push(CTRL_CODE_UP);
	commandForComparison.push(CTRL_CODE_DOWN);
	commandForComparison.push(CTRL_CODE_DOWN);
	commandForComparison.push(CTRL_CODE_LEFT);
	commandForComparison.push(CTRL_CODE_RIGHT);
	commandForComparison.push(CTRL_CODE_LEFT);
	commandForComparison.push(CTRL_CODE_RIGHT);
	commandForComparison.push('b');
	commandForComparison.push('a');
}


SecretCommand::~SecretCommand(void)
{
}


void SecretCommand::PushBack(char command)
{
	if(inputtedCommand.size() < 10)
	{
		if(command != 0)
		inputtedCommand.push(command);
	}
	else
	{
		if(command != 0)
		{
			inputtedCommand.push(command);
			inputtedCommand.pop();
		}
	}
}


void SecretCommand::CheckHitSecretCommand()
{
	PushBack(GetInputChar(true));
	if(inputtedCommand == commandForComparison)
	{
		hasHittedSecretCommand = 1;
	}
}