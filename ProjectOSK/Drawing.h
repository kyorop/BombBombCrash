#pragma once
struct IDrawable;

class Drawing
{
	static std::vector<std::shared_ptr<IDrawable>> drawables;
public:
	Drawing();
	~Drawing();

	static void Add(const std::shared_ptr<IDrawable> & drawable);
	static void Remove(const std::shared_ptr<IDrawable>& drawable);
	void Update();
};

