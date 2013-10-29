#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#include "GameConstant.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Charactor;
class Block
	:public IDrawable,
	public IRegister
{
private:
	int image_softBlock;
	MapObstacle block[GameConst::MAP_ROW][GameConst::MAP_LINE];
public:
	Block(void);
	~Block(void);

	void Register();
	void Draw();
};

