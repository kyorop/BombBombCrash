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
	~MapObject(void);

	int GetX()const;
	int GetRX()const;
	int GetY()const;
	int GetDY()const;
	int GetFlag()const;
	void SetFlag();

};

