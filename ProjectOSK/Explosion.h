#pragma once
#include "MapObject.h"
#include "IFireIterator.h"
#include "IFreAggregate.h"
#include "IGameProgress.h"


namespace BombBombCrash
{
	class Timer;
	class GameManager;
	class FirePillar;
	class FireId;
	class Bomb;

	enum class FirePillarDirection
	{
		Up,
		Right,
		Down,
		Left,
	};


	class FireBlock:public MapObject
	{
	public:
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;

		GameObjectType Type() const override{ return GameObjectType::Fire; }
	private:
		const int fireImageHandle;
	public:
		FireBlock(const ln::Vector2& position, int fireImage);
		void Draw() const;

	};


	class FirePillar :public IFireAggregate
	{
		std::vector<std::shared_ptr<FireBlock>> pillar;
		std::shared_ptr<FireBlock> center;
		FirePillarDirection direction;
		size_t fireLevel;
	public:
		std::shared_ptr<IFireIterator> Iterator() override;

	protected:
		ln::Vector2 Direction() const;

	public:
		FirePillar(FirePillarDirection direction, int fireLevel, const std::shared_ptr<FireBlock>& center);

		void Initialize();

		void Increment();

		int Size() const;

		void Remove();


		std::shared_ptr<FireBlock> FireBlockAt(int i);
	};


	class Fire : public IGameProgress
	{
		std::vector<FireBlock*> vex;

		static const int fireTime = 200;

		std::shared_ptr<Timer> timer;
		

		std::shared_ptr<FireBlock> center;
		std::vector<std::shared_ptr<FirePillar>> firePillars;

	public:
		Fire(const ln::Vector2& centerPos);

		int GetX(int i)const;
		int GetY(int i)const;
		int GetFlag(int i)const;
		void SetFlag(int i, int flag);
		int GetSize()const;
		void Register(void);
		void Maintain();

		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;
		void Destroy(const GameManager& game) override;
		bool CanRemove() override;

		std::shared_ptr<IFireIterator> Iterator(FirePillarDirection direction);
		void Remove(FireId id);
	};
	

	class FirePillarIterator :public IFireIterator
	{
		FirePillar& fire;
		int index;
	public:

		explicit FirePillarIterator(FirePillar& pillar);

		bool HasNext() override;
		std::shared_ptr<FireBlock> Next() override;
	};

}


