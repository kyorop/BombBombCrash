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
	const int image_item;
	const int i_graph;
public:
	Item();
	~Item(void);
	void Draw();
	int GetKind()const;
};

