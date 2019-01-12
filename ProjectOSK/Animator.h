#pragma once

class Animator
{
	ln::Vector2 position_;
	virtual void Play() = 0;
protected:
	int get_x() const { return position_.X; }
	int get_y() const { return position_.Y; }
public:
	virtual ~Animator() = default;
	void Play(int x, int y);
	void Play(const ln::Vector2& position);
};
