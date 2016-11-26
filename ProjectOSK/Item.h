#pragma once
#include "MapObject.h"


namespace BombBombCrash
{
	class Item:public MapObject
	{
	public:
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;

		enum
		{
			FIRE,
			BOMB, 
			SPEED,
		};

	private:
		static const int itemNum = 3;
		const int i_graph;
		const int image_item;

	public:
		Item();
		~Item();
		int GetKind()const;
		GameObjectType Type()const override{ return GameObjectType::Item; }
	};
}




