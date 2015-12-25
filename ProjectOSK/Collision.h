#pragma once
#include <vector>
#include <list>


//�V���O���g��


namespace BombBombCrash
{
	class ICollisionable;
	class Fire;
	class Item;

	class Collision
	{
		std::vector<ICollisionable*> disableGoingThrough;
		std::vector<ICollisionable*> bomb;
		std::vector<ICollisionable*> character;
		std::list<ICollisionable*> softBlock;
		std::list<ICollisionable*> hardBlock;
		std::list<ICollisionable*> map;
		std::list<Fire*> fire;
		std::list<ICollisionable*> fragile;
		std::list<Item*> item;

		static const int degreeOfHit = 5;
		static const int collisionLevelWithFire = 5;
		static const int haba = 16;
	
		Collision(void);
		Collision(const Collision &collision);

		//�ʂ�Ȃ��n
		void CheckEnableToPass();

		//�ʏ�̂����蔻��
		int CheckOneUponAnother(int x1, int y1,int x2, int y2, int collisionLevel);

		//�΂Ƃ̐ڐG����
		void CheckCollisionWithFire();

		//�΂�������Ɖ��镨�̂����蔻��
		void CheckCollisionFireAndFragile();

		//�L�����N�^�[�ƃA�C�e���̂����蔻��
		void CheckCollisionItemAndCharactor();

	public:
		~Collision(void);
		static Collision* Instance();
		void Finalize();
		void Register(ICollisionable *anythingCollisionable);
		void RegisterWithFire(Fire *fire);
		void RegisterWithItem(Item *item);
		void CheckAllCollision();
	};
}

