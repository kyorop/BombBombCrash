#pragma once
#define PLAYERDEVIDENUMBER 20
#define MAPSIZE_X 17
#define MAPSIZE_Y 13
enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOHIT,
};

class Map;
class Item;
class Player
{
	friend class Block;

public:	
	int graph[PLAYERDEVIDENUMBER];
	int width;
	int height;
	int muki;
	int x,rx;
	int y,dy;
	int flag;
	void Draw(int graphnum, Map &map, int g_lasttime);
	int Get(int member)const;
	void CheckHit(Map &map);
	void SetFlag(int tf);
	void Move();
	int GetStateFire(const Item &item);
	Player();//コンストラクタ
	~Player(void);//デストラクタ
private:
	
	
};

