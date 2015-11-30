#pragma once
#include <vector>
#include <memory>

class Bomb;
class BombController
{
private:
	std::vector<std::unique_ptr<Bomb>> bombs;
	int num_upFireLevel;

public:
	BombController(void);
	~BombController(void);

	void Set(int x, int y);
	void Update(void);
	void Draw(void);
	void Increment(void);
	void IncrementFirepower(void);
	int BombSize() const;
	int Firepower();
};

