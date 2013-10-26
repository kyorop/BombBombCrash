#pragma once
#include <vector>
#include <list>

class ICollisionable;

//ƒVƒ“ƒOƒ‹ƒgƒ“
class ExplosionManager;
class Collision
{
private:
	std::vector<ICollisionable*> disableGoingThrough;
	std::vector<ICollisionable*> bomb;
	std::vector<ICollisionable*> character;
	std::list<ICollisionable*> softBlock;
	std::list<ICollisionable*> hardBlock;
	std::list<ICollisionable*> map;
	std::list<ExplosionManager*> fire;

	static const int degreeOfHit = 5;
	static const int haba = 16;
private:
	Collision(void);
	Collision(const Collision &collision);

	//’Ê‚ê‚È‚¢Œn
	void CheckEnableToPass();
	//’Êí‚Ì‚ ‚½‚è”»’è
	int CheckOneUponAnother(int x1, int y1,int x2, int y2);
	//‰Î‚Æ‚ÌÚG”»’è
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(ExplosionManager *fire);
	void CheckCollision();
};

