#pragma once

namespace BombBombCrash
{
	class NewFire;
	class FireManager
	{
		std::shared_ptr<NewFire> center;
		std::vector<std::shared_ptr<NewFire>> up;
		std::vector<std::shared_ptr<NewFire>> right;
		std::vector<std::shared_ptr<NewFire>> down;
		std::vector<std::shared_ptr<NewFire>> left;
	public:
		FireManager();
		std::vector<std::shared_ptr<NewFire>> Create(const ln::Vector2& centerPosition);
		void IncreaseFirePower();
	};
}



