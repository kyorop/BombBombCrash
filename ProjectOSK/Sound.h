#pragma once
#include "Resource.h"
#include <list>


class ISoundPlayer;
class Sound
	:public Resource
{
private:
	int explosion;
private:
	Sound();
	Sound(const Sound&);
	Sound& operator=(const Sound&);

	void PlayExplosion();
	std::list<ISoundPlayer*> soundList;
public:
	~Sound(void);
	static Sound* GetInstance()
	{
		static Sound soundInstance;
		return &soundInstance;
	}

	void Register(ISoundPlayer* anythingToPlaySound);
	void Initialize();
	void Finalize();
	//int GetExplosionHandle();
	void PlayTitleMusic();
	void PlaySE();

};

