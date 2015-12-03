#pragma once
#include "MapObject.h"
#include "IDrawable.h"

class Item:public MapObject, public IDrawable
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
	void Draw() override;
	int GetKind()const;
};

