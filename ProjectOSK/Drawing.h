#pragma once
#include "Key.h"

namespace BombBombCrash
{
	class Key;
	interface IDrawable;

	class Drawing
	{
		static std::vector<std::weak_ptr<IDrawable>> drawables;
	public:
		Drawing();
		~Drawing();

		static void Add(const std::shared_ptr<IDrawable> & drawable);
		void Update() const;
	};
}




