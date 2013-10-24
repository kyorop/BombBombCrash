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
private:
	int floor;
	int hardBlock;
	int softBlock;
	MapObstacle map[GameConst::MAP_ROW][GameConst::MAP_LINE];
public:
	Map(void);
	~Map(void);
	
	void CheckHitCharactor(Charactor *charactor);
	void Register();
	void Draw();

};

