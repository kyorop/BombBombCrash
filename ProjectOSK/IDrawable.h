#pragma once
class IDrawable
{
public:
	virtual void Draw() = 0;
	IDrawable(void);
	~IDrawable(void);
};

