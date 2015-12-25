#pragma once

namespace BombBombCrash
{
	class Character;
	class MapObject;

	class ControlPassingCollision
	{
		static const int degreeOfHit = 5;
		static const int haba = 16;

		std::vector<std::shared_ptr<Character>> mover;
		static std::vector<std::shared_ptr<MapObject>> notPassables;
	public:
		ControlPassingCollision();
		~ControlPassingCollision();

		void Add(const std::shared_ptr<Character>& movingObject);
		static void Add(const std::shared_ptr<MapObject>& notPassable);
		void Update();
	};
}




