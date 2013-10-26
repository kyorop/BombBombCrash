#pragma once
#include <vector>
#include <list>

class ICollisionable;

//�V���O���g��
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

	//�ʂ�Ȃ��n
	void CheckEnableToPass();
	//�ʏ�̂����蔻��
	int CheckOneUponAnother(int x1, int y1,int x2, int y2);
	//�΂Ƃ̐ڐG����
	void CheckCollisionWithFire();
	//�΂�������Ɖ��镨�̂����蔻��
	void CheckCollisionFireAndFragile();
	//�L�����N�^�[�ƃA�C�e���̂����蔻��
	void CheckCollisionItemAndCharactor();
public:
	~Collision(void);
	static Collision* GetInstance();
	void Register(ICollisionable *anythingCollisionable);
	void RegisterWithFire(ExplosionManager *fire);
	void RegisterWithItem(Item *item);
	void CheckCollision();
};

