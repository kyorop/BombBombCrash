#pragma once

namespace BombBombCrash
{
	class FireBlock;
	interface IFireIterator
	{
		virtual ~IFireIterator(){}
		virtual bool HasNext() = 0;
		virtual std::shared_ptr<FireBlock> Next() = 0;
	};
}



