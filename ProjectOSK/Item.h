#pragma once
#include "MapObject.h"

class Item
	:public MapObject
{
public:
	enum
	{
		FIRE,
		BOMB, 
		SPEED,
	};
private:
	static const int itemNum = 3;
	const int i_graph;
	const int image_item;
public:
	Item();
	~Item();
	void Draw();
	int GetKind()const;
};

