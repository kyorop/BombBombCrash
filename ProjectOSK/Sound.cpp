#include "Sound.h"
#include "ISoundPlayer.h"


Sound::Sound(void)
	:explosion()
{
}


Sound::~Sound(void)
{
}


void Sound::Register(ISoundPlayer* anythingToPlaySound)
{
	soundList.push_back(anythingToPlaySound);
}



void Sound::InitializeForGame()
{
	explosion = LoadSoundMem("explosion.mp3");
}


void Sound::InitializeForMenu()
{

}



void Sound::FinalizeForGame()
{
	DeleteSoundMem(explosion);
	soundList.clear();
}


void Sound::FinalizeForMenu()
{

}


void Sound::PlayTitleMusic()
{
}


void Sound::PlaySE()
{
	std::list<ISoundPlayer*>::iterator itr = soundList.begin();
	for(itr; itr != soundList.end(); ++itr)
	{
		if((*itr)->EnableToPlaySound() == 1)
			PlaySoundMem(explosion,DX_PLAYTYPE_BACK);
	}
}