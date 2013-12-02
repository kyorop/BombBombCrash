#pragma once
#include <queue>

class Key;
class SecretCommand
{
private:
	static int hasHittedSecretCommand;
	std::queue<char> inputtedCommand;
	std::queue<char> commandForComparison;
private:
	void PushBack(char command);
public:
	SecretCommand();
	~SecretCommand();

	void CheckHitSecretCommand();
	static int HittedSecretCommand(){return hasHittedSecretCommand;}
};

