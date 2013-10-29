#pragma once
#include <vector>

class BombSet;
class BombSetManager
{
private:
	std::vector<BombSet*> bombSet;
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

