#include "Sound.h"
#include "ISoundPlayer.h"
#include "DxLib.h"


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


void Sound::Initialize()
{
	explosion = LoadSoundMem("explosion.mp3");
}


void Sound::Finalize()
{
	DeleteSoundMem(explosion);
}


//int Sound::GetExplosionHandle()
//{
//	return explosion;
//}


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