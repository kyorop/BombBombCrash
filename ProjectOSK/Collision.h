#pragma once
#include <vector>
#include <list>

class ICollisionable;

//�V���O���g��
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

	//�ʂ�Ȃ��n
	void CheckEnableToPass();
	//�ʏ�̂����蔻��
	int CheckOneUponAnother(int x1, int y1,int x2, int y2);
	//�΂Ƃ̐ڐG����
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(ExplosionManager *fire);
	void CheckCollision();
};

