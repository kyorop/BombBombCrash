#include "Key.h"

Key::Key(void)
{
	for(int i=0; i<256; ++i)
		this->key[i] = 0;
}

int Key::CheckOnePushKey(int keyCode)
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for(int i=0; i<256; ++i)
	{
		if(tmpKey[i] == 1)
			++this->key[i];
		else
			this->key[i] = 0;
	}

	if(this->key[keyCode] == 1)//‰Ÿ‚³‚ê‚½‚ÌƒtƒŒ[ƒ€‚¾‚¯TRUE‚ğ•Ô‚·
		return TRUE;
	else
		return FALSE;
}

Key::~Key(void)
{
}
