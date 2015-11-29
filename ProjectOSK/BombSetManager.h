#pragma once
#include <vector>
#include <memory>

class Bomb;
class BombSetManager
{
private:
	std::vector<std::unique_ptr<Bomb>> bombs;
	int num_upFireLevel;

public:
	BombSetManager(void);
	~BombSetManager(void);

	void Set(int x, int y);
	void Update(void);
	void Draw(void);
	void UpNum(void);
	void UpFireLevel(void);
	void CheckBombOverlap(void);
};

