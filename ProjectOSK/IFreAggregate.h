#pragma once

namespace BombBombCrash
{
	struct IFireIterator;
	interface IFireAggregate
	{
		virtual ~IFireAggregate(){}
		virtual std::shared_ptr<IFireIterator> Iterator() = 0;
	};

}



