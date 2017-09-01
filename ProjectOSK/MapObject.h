#pragma once
#include "ICollisionable.h"
#include "IGettable.h"


namespace BombBombCrash
{
	class Rect;
	class GameManager;
class MapObject:public ICollisionable,public IGettable
{
	bool visible;
	bool exists;
	ln::Vector2 upperLeftPos;
	ln::Vector2 lowerRightPos;

public:
	enum GameObjectType
	{
		Player,
		Enemy,
		Bomb,
		HardBlock,
		SoftBlock,
		Item,
		Fire,
		FireUpItem,
		BombUpItem,
		SpeedUpItem,
	};
	MapObject();
	MapObject(const ln::Vector2& position, int width, int height);

	virtual ~MapObject(void);

	virtual int X()const;
	virtual void SetX(int x);
	virtual int RX()const;
	virtual int Y()const;
	virtual void SetY(int y);
	virtual int DY()const;
	virtual bool Exists() const;
	virtual bool Visible() const;
	virtual void SetVisible(bool isVisible);
	virtual void SetExists(int isExists);

	ln::Vector2 Position() const;
	ln::Vector2 LowerRightPosition() const;
	void SetPosition(const ln::Vector2& position);
	void Translate(const ln::Vector2& translation);
	int Width() const;
	int Height() const;
	Rect Rect() const;
	virtual GameObjectType Type() const = 0;

	virtual void Initialize(GameManager& game){}
	virtual void Update(GameManager& game) = 0;
	virtual void Draw(GameManager& game) = 0;
	virtual void Finalize(GameManager& game){}
};
}




