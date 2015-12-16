#include "stdafx.h"
#include "Drawing.h"
#include "IDrawable.h"

using namespace BombBombCrash;

std::vector<std::weak_ptr<IDrawable>> Drawing::drawables;

Drawing::Drawing()
{
}


Drawing::~Drawing()
{
}

void Drawing::Add(const std::shared_ptr<IDrawable> & drawable)
{
	drawables.push_back(drawable);
}

void Drawing::Update() const
{
	for (int i = 0; i < drawables.size(); i++)
	{
		if (auto sharedDrawing = drawables[i].lock())
		{
			sharedDrawing->Draw();
		}
		else
			drawables.erase(begin(drawables)+i);
	}
}
