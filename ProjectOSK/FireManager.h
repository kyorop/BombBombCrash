#pragma once

namespace BombBombCrash
{
	class Fire;
	class FireManager
	{
		std::shared_ptr<Fire> center;
		std::vector<std::shared_ptr<Fire>> up;
		std::vector<std::shared_ptr<Fire>> right;
		std::vector<std::shared_ptr<Fire>> down;
		std::vector<std::shared_ptr<Fire>> left;
	public:
		FireManager();
		std::vector<std::shared_ptr<Fire>> Create(const ln::Vector2& centerPosition);
		void IncreaseFirePower();
	};
}



