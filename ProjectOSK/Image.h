#pragma once
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
	enum
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
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
	int enemy[characterDivideNum];
	int bomb[bombDivideNum];
	int fire;
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
	int* GetPlayerImage(int direction);
	int* GetEnemyImage(int direction);
	int* GetBombImage();
};

