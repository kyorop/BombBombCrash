#pragma once
#include <vector>
#include <list>

class ICollisionable;

//ƒVƒ“ƒOƒ‹ƒgƒ“
class Collision
{
private:
	std::vector<ICollisionable*> disableGoingThrough;
	std::vector<ICollisionable*> bomb;
	std::vector<ICollisionable*> character;
	std::list<ICollisionable*> block;
	std::list<ICollisionable*> map;

	static const int degreeOfHit = 5;
	static const int haba = 16;
private:
	Collision(void);
	Collision(const Collision &collision);

	//’Ê‚ê‚È‚¢Œn
	void CheckEnbleToStop();
	//’Êí‚Ì‚ ‚½‚è”»’è
	void CheckOneUponAnother();
	//‰Î‚Æ‚ÌÚG”»’è
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void RegiPlayer(ICollisionable *player);
	//void RegisterWithBomb(ICollisionable *bomb);
	//void RegisterWithCharactor(ICollisionable *charactor);
	void Register(ICollisionable *anythingCollisionable);
	void CheckCollision();
};

