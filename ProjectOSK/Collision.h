#pragma once
#include <vector>
#include <list>

class ICollisionable;

//�V���O���g��
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

	//�ʂ�Ȃ��n
	void CheckEnbleToStop();
	//�ʏ�̂����蔻��
	void CheckOneUponAnother();
	//�΂Ƃ̐ڐG����
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

