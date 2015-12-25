#pragma once

namespace BombBombCrash
{
	class Key
	{
		int key[256];
	public:
		int CheckOnePushKey(int keyCode);
		Key(void);
		~Key(void);
	};
	
}



