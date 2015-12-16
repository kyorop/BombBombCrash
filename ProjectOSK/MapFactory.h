#pragma once

namespace BombBombCrash
{
	class MapObject;
	class Map;
	class MapFactory
	{
	public:
		MapFactory();
		~MapFactory();

		static std::unique_ptr<Map> Craete();

	private:
		static void InitBlock(const std::shared_ptr<MapObject>& block ,int i, int j);
	};
}


