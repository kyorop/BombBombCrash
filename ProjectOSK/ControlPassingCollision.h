#pragma once

namespace BombBombCrash
{
	class Character;
	class MapObject;

	class ControlPassingCollision
	{
		static const int padding = 5;
		static const int haba = 16;

		static std::vector<std::shared_ptr<Character>> movers;
		static std::vector<std::shared_ptr<MapObject>> notPassables;
	public:
		ControlPassingCollision();

		static void Add(const std::shared_ptr<Character>& movingObject);
		static void Add(const std::shared_ptr<MapObject>& notPassable);
		void Update();
	};
}




