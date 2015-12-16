#include "stdafx.h"
#include "Drawing.h"
#include "IDrawable.h"
#include <algorithm>

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
	for (auto& drawing : drawables)
	{
		if (auto pdrawing = drawing.lock())
		{
			pdrawing->Draw();
		}
		else
		{
			drawables.erase(remove_if(begin(drawables), end(drawables), [&](const std::weak_ptr<IDrawable>& weak_draw)
			{
				return weak_draw.lock() == pdrawing;
			}), end(drawables));
		}
	}
}
