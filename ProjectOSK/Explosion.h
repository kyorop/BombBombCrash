#pragma once
#include "MapObject.h"
#include "Timer.h"
#include "IFireIterator.h"
#include "IFreAggregate.h"


namespace BombBombCrash
{
	class FirePillar;
	class FireId;
	class Bomb;

	class FireBlock:public MapObject
	{
//		const int upx,downx,upy,downy;
		int fuse;
		int explosion;

	public:
//		FireBlock(int right,int left,int down,int up);

		FireBlock(const ln::Vector2& position, int width, int height)
			: MapObject(position, width, height),
			fuse(0),
			explosion(0)
		{
		}

		FireBlock(const std::shared_ptr<FireId>& id);
		~FireBlock(void);

		void Set(int x, int y);
		int GetExplosion();
		void SetFuse(int flag);
		void SetExplosion(int flag);
	};


	class Fire
	{
		enum FirePillarDirection
		{
			Up,
			Right,
			Down,
			Left,
		};

		int nowFireLevel;
		int fuse;
		int explosion;
		Timer retainFire;
		Timer beforeExplosion;
		static const int displayingTime = 200;
		const int image_fire;
		std::vector<FireBlock*> vex;


		std::shared_ptr<FireBlock> center;
		std::vector<std::shared_ptr<FirePillar>> firePillars;

	public:
		Fire();
		~Fire(void);
	
	public:
		int GetX(int i)const;
		int GetY(int i)const;
		int GetFlag(int i)const;
		void SetFlag(int i, int flag);
		int GetSize()const;
		void Register(void);
		int Firepower(void);
		void Maintain();

		void FireUp();
		void Draw();
		void Update(const Bomb &bomb);

		std::shared_ptr<IFireIterator> Iterator(FirePillarDirection direction);
		void Remove(FireId id);
	};


	class FirePillar :public IFireAggregate
	{
		std::vector<std::shared_ptr<FireBlock>> pillar;
		std::shared_ptr<FireBlock> center;
	public:
		std::shared_ptr<IFireIterator> Iterator() override;
	protected:
		virtual ln::Vector2 Direction() = 0;
	public:
		explicit FirePillar(const std::shared_ptr<FireBlock>& center);

		void Add();
		virtual ~FirePillar(){};
		void Remove();
		int Size() const;
		FireBlock FireBlockAt(int i);
	};
	

	class UpFirePillar : public FirePillar
	{
	public:
		explicit UpFirePillar(const std::shared_ptr<FireBlock>& center)
			: FirePillar(center)
		{
		}

	protected:
		ln::Vector2 Direction() override;
	};

	
	class RightFirePillar:public FirePillar
	{
	public:
		explicit RightFirePillar(const std::shared_ptr<FireBlock>& center)
			: FirePillar(center)
		{
		}

	protected:
		ln::Vector2 Direction() override;
	};

	
	class DownFirePillar:public FirePillar
	{
	public:
		explicit DownFirePillar(const std::shared_ptr<FireBlock>& center)
			: FirePillar(center)
		{
		}

	protected:
		ln::Vector2 Direction() override;
	};


	class LeftFirePillar:public FirePillar
	{
	public:
		explicit LeftFirePillar(const std::shared_ptr<FireBlock>& center)
			: FirePillar(center)
		{
		}

	protected:
		ln::Vector2 Direction() override;
	};


	class FirePillarIterator :public IFireIterator
	{
		std::shared_ptr<FirePillar> fire;
		int index;
	public:

		explicit FirePillarIterator(const FirePillar& firePillar);

		bool HasNext() override;
		MapObject Next() override;
	};

}


