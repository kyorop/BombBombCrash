#pragma once

namespace BombBombCrash
{
	class MapObject;
	interface IFireIterator
	{
		virtual ~IFireIterator(){}
		virtual bool HasNext() = 0;
		virtual MapObject Next() = 0;
	};
}



