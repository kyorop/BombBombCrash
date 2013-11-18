#pragma once
class GameEffect
{
private:
	int image_bombLevel;
	int image_fireLevel;
	const int white;
	const int x;
	const int y;
public:
	GameEffect(void);
	~GameEffect(void);

	void DrawGameEffect();
	void DrawMenuEffect();
};

