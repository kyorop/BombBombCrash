#pragma once
#include <vector>

class Explosion;
class Bomb;
class MapObstacle;
class Player;
class ItemManager;
class ExplosionManager
{
private:
	std::vector<Explosion*> *vex;//vectorクラスのオブジェクト生成
	bool Timer(int time);

public:
	void SetExplosion(const Bomb &bomb);
	void CheckHitObject(MapObstacle *mapobstacle);
	void SetZahyou(const Bomb &bomb);
	void AddExplosion(const ItemManager &manageItem,Player &player);	
	void CheckHitExplosion(Player *player);
	void DrawExplosion(const Bomb &bomb);
	ExplosionManager();
	~ExplosionManager(void);
};

