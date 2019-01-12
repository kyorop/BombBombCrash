#pragma once
#include "IBombAction.h"
#include "MapObject.h"
#include "Timer.h"
#include "Animator.h"
#include "ISubject.h"

namespace BombBombCrash{

class StandardBomb:public MapObject, public IBombAction, public ISubject
{
	Timer timer_;
	std::unique_ptr<Animator> bomb_animator_;
	std::list<std::shared_ptr<IObserver>> observers_;
	int fire_level_;
public:
	explicit StandardBomb(int fire_level);
	void Explode() override{}
	ObjectType Type()const override{return Bomb;}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
	void AddObserver(const std::shared_ptr<IObserver>& observer) override;
	void DeleteObserver(const std::shared_ptr<IObserver>& observer) override;
	void Notify() override;
	void OnCollide(MapObject& other) override;
};

}
