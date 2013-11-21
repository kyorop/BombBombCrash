#pragma once

class Key;
class SecretCommand
{
private:
	static int hasHittedSecretCommand;
	Key* key;
	int up, up2;
	int down, down2;
	int right, right2;
	int left, left2;
	int stack;
public:
	SecretCommand();
	~SecretCommand();

	void CheckHitSecretCommand();
	static int HittedSecretCommand(){return hasHittedSecretCommand;}
};

