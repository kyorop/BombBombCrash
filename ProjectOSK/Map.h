#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#include "GameConstant.h"

class Charactor;
class Map
	:public IDrawable,
	public IRegister
{
public:
	enum{FLOOR, HARDBLOCK, SOFTBLOCK};
private:
	int floor;
	int hardBlock;
	int softBlock;
	MapObstacle map[GameConst::MAP_ROW][GameConst::MAP_LINE];
public:
	Map(void);
	~Map(void);

	int IsSoftBlock(int i, int j)const;
	void Register();
	void Draw();

};

