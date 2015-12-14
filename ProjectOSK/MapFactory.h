#pragma once

namespace BombBombCrash
{
	enum MapType
	{
		FLOOR,
		HARDBLOCK,
		SOFTBLOCK,
	};

	class Map;
	class MapFactory
	{
	public:
		MapFactory();
		~MapFactory();

		std::unique_ptr<Map> Craete() const;
	};
}


