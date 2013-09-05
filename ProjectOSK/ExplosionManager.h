#pragma once
#include <vector>

class Explosion;
class Bomb;
class MapObstacle;
class Player;
class ItemManager;
class BombManager;
enum firestate;
class ExplosionManager
{
private:
	std::vector<Explosion*> *vex;//vectorクラスのオブジェクト生成
	int addFireNum;
	int nowFireLevel;
	firestate flag;

public:
	//void SetExplosion(const BombManager &bombManager);
	void SetExplosion(int x, int y);
	void CheckHitObject(MapObstacle *mapobstacle);
	void AddExplosion(const ItemManager &manageItem);	
	void CheckHitExplosion(Player *player);
	void DrawExplosion();
	void SetFlag(firestate flag);
	firestate GetFlag()const;
	ExplosionManager();
	~ExplosionManager(void);
};

