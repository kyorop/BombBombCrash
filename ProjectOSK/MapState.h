#pragma once
#define ROW 17
#define LINE 13
#define OBJECT 6
#define TOPIC 2

class MapState
{
private:
	int mapState[ROW][LINE][OBJECT][TOPIC];
private:
	MapState(void);
	MapState(const MapState &ms);
	~MapState(void);
private:
	void SetState(int x, int y, int object, int state, int option=0);
public:
	static MapState* GetInstance();
	void SetMapState(int x, int y, int flag, int option=0);
	void SetBlockState(int x, int y, int state, int option=0);
	void SetItemState(int x, int y, int state, int option=0);
	void SetCharactorState(int x, int y, int flag, int option=0);
	void SetBombState(int x, int y, int state, int fireLevel);
	void SetFireState(int x, int y, int state, int option=0);
};

