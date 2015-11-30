#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#include "GameConstant.h"

class Character;
class Map
	:public IDrawable,
	public IRegister
{
private:
	const int image_floor;
	const int image_hardBlock;
	MapObstacle map[GameConst::MAP_ROW][GameConst::MAP_LINE];
public:
	Map(void);
	~Map(void);

	//int IsSoftBlock(int i, int j)const;
	void Register();
	void Draw();

};

