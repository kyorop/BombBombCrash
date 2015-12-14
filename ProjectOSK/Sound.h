#pragma once
#include <list>


namespace BombBombCrash
{
	class ISoundPlayer;
	class Sound
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
		void InitializeForGame();
		void InitializeForMenu();
		void FinalizeForGame();
		void FinalizeForMenu();
		void PlayTitleMusic();
		void PlaySE();
	};
	
}



