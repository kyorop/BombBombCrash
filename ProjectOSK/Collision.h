#pragma once
#include <vector>
#include <list>

class ICollisionable;

//シングルトン
class ExplosionManager;
class Item;
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
	std::list<ICollisionable*> fragile;
	std::list<Item*> item;

	static const int degreeOfHit = 5;
	static const int haba = 16;
private:
	Collision(void);
	Collision(const Collision &collision);

	//通れない系
	void CheckEnableToPass();
	//通常のあたり判定
	int CheckOneUponAnother(int x1, int y1,int x2, int y2);
	//火との接触判定
	void CheckCollisionWithFire();
	//火が当たると壊れる物のあたり判定
	void CheckCollisionFireAndFragile();
	//キャラクターとアイテムのあたり判定
	void CheckCollisionItemAndCharactor();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(ExplosionManager *fire);
	void RegisterWithItem(Item *item);
	void CheckCollision();
};

