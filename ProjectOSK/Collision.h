#pragma once
#include <vector>
#include <list>

class ICollisionable;

//�V���O���g��
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

	//�ʂ�Ȃ��n
	void CheckEnableToPass();
	//�ʏ�̂����蔻��
	void CheckOneUponAnother();
	//�΂Ƃ̐ڐG����
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(Explosion *fire);
	void CheckCollision();
};

