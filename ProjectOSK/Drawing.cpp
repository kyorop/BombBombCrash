#include "stdafx.h"
#include "Drawing.h"
#include "IDrawable.h"

std::vector<std::shared_ptr<IDrawable>> Drawing::drawables;

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

void Drawing::Remove(const std::shared_ptr<IDrawable>& drawable)
{
	auto removeItr = find(begin(drawables), end(drawables), drawable);
	drawables.erase(removeItr);
}

void Drawing::Update()
{
	for (auto& drawing : drawables)
	{
		drawing->Draw();
	}
}
