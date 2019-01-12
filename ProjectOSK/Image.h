#pragma once
#include "AnimationClip.h"

namespace BombBombCrash
{
	class Image
	{
	public:
		enum
		{
			FLOOR,
			HARDBLOCK,
			SOFTBLOCK,
			ITEM,
			PLAYER,
			ENEMY,
			BOMB,
			FIRE,
		};
		enum
		{
			FIREUP,
			BOMBUP, 
			SPEEDUP,
		};
		enum characterState
		{
			LEFT,
			RIGHT,
			UP,
			DOWN,
			DEATH,
		};
	private:
		static const int itemDivideNum = 3;
		static const int characterDivideNum = 20;
		static const int bombDivideNum = 60;
		int floor;
		int hardBlock;
		int softBlock;
		int item[itemDivideNum];
		int player[characterDivideNum];
		int redEnemy[characterDivideNum];
		int blackEnemy[characterDivideNum];
		int blueEnemy[characterDivideNum];
		int purpleEnemy[characterDivideNum];
		int bomb[bombDivideNum];
		int fire;
		std::map<std::string, std::vector<int>> loaded_handles_;
	public:
		int number[10];
		int colon;
	private:
		Image(void);
		Image(const Image &);
		Image& operator=(const Image&);
	public:
		~Image(void);

		static Image* GetInstance()
		{
			static Image image;
			return &image;
		}

		void Initialize();
		void Finalize();
		int GetImage(int kindofImage);
		int GetItemImage(int kindofItem);
		int* GetCharacterImage(int id, int direction);
		int* GetBombImage();

		AnimationClip Load(const std::string& file_path, int all_num, int x_num, int y_num, int x_size, int y_size);
		AnimationClip Load(const std::string& file_path);
	};

	
}


