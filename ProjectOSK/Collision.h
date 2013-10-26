#pragma once
#include <vector>
#include <list>

class ICollisionable;

//シングルトン
class Explosion;
class Collision
{
private:
	std::vector<ICollisionable*> disableGoingThrough;
	std::vector<ICollisionable*> bomb;
	std::vector<ICollisionable*> character;
	std::list<ICollisionable*> softBlock;
	std::list<ICollisionable*> hardBlock;
	std::list<ICollisionable*> map;
	std::list<Explosion*> fire;

	static const int degreeOfHit = 5;
	static const int haba = 16;
private:
	Collision(void);
	Collision(const Collision &collision);

	//通れない系
	void CheckEnableToPass();
	//通常のあたり判定
	void CheckOneUponAnother();
	//火との接触判定
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(Explosion *fire);
	void CheckCollision();
};

