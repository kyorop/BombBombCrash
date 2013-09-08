#pragma once

class Map;
class Charactor
{
protected:
	int x;
	int rx;
	int y;
	int dy;
	int flag;
public:
	virtual void Draw()=0;
	virtual void Move(int g_lastTime)=0;
	virtual int GetX()const;
	virtual int GetY()const;
	virtual int GetRX()const;
	virtual int GetDY()const;
	virtual void SetX(int x);
	virtual void SetY(int y);
	//virtual void SetRX();
	//virtual void SetDY();
	virtual void SetCharactorState(int flag);
	Charactor(void);
	~Charactor(void);

};

