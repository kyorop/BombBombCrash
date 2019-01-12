#pragma once


namespace BombBombCrash
{
	class Rect;
	class GameManager;
class MapObject
{
	bool visible = true;
	bool exists = true;
	ln::Vector2 upperLeftPos;
	const int id_;
	int width_ = 32;
	int height_ = 32;
	static int id_generator_;

public:
	enum ObjectType
	{
		None,
		Player,
		Enemy,
		Bomb,
		HardBlock,
		BREAKABLE_BLOCK,
		Item,
		Fire,
		FireUpItem,
		BombUpItem,
		SpeedUpItem,
	};

	MapObject();
	MapObject(const ln::Vector2& position, int width, int height);
	explicit MapObject(ln::Vector2 initial_position);
	MapObject(int i, int j);
	virtual ~MapObject(){}

	int X()const{return upperLeftPos.X;}
	int RX()const{ return upperLeftPos.X + width_; }
	int Y()const{return upperLeftPos.Y;}
	int DY()const{ return upperLeftPos.Y + height_; }
	void SetX(float x);
	void SetY(float y);
	bool Exists() const{return exists;}
	bool Visible() const{return visible;}
	void SetVisible(bool isVisible){visible = isVisible;}
	void MakeInvisible(){ visible = false; }
	void MakeVisible(){ visible = true; }
	void SetExists(bool isExists){exists = isExists;}
	ln::Vector2 Position() const{return upperLeftPos;}
	ln::Vector2 LowerRightPosition() const;
	void SetPosition(const ln::Vector2& position);
	void SetPosition(int i, int j);
	void Translate(const ln::Vector2& translation);
	int Width() const;
	int Height() const;
	Rect Rect() const;
	int Id()const{ return id_; }

	static void Create(std::unique_ptr<MapObject> new_entity);
	void Delete();

	virtual ObjectType Type() const{ return None; }

	// Game Task Functions. 
	virtual void Initialize(){}
	
	virtual void Update(){}

	// Functions with "On" on the top are invoked in Update().
	virtual void OnCollide(MapObject& other){}

	virtual void OnCollisionExit(MapObject& other){}

	virtual void OnDeleted(){}
	
	virtual void LateUpdate(){}
	
	virtual void Draw(){}
	
	virtual void Finalize(){}
};
}




