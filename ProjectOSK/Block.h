#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#include "GameConstant.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Character;
class Block
	:public IDrawable,
	public IRegister
{
private:
	const int image_softBlock;
	MapObstacle block[GameConst::MAP_ROW][GameConst::MAP_LINE];
public:
	Block(void);
	~Block(void);

	void Register();
	void Draw();
	//(i,j)がソフトブロックなら１を返す
	int IsSoftBlock(int i, int j)const;
};

