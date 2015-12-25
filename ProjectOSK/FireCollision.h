#pragma once


namespace BombBombCrash
{
	class Fire;
	class MapObject;

	class FireCollision
	{
		std::weak_ptr<MapObject> burnables;
		std::weak_ptr<Fire> fires;
	public:
		FireCollision();
		~FireCollision();

		void Update();
	};
}