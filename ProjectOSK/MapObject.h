#pragma once
class MapObject
{
protected:
	int x;
	int rx;
	int y;
	int dy;
	int flag;

public:
	MapObject(void);
	virtual ~MapObject(void);

	int GetX()const;
	void SetX(int x);
	int GetRX()const;
	int GetY()const;
	void SetY(int y);
	int GetDY()const;
	int GetFlag()const;
	void SetFlag(int flag);

};

