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
	virtual void SetCharactorState(int flag);
	Charactor(void);
	virtual ~Charactor(void);

	
protected:
	int mv;
	int bombNum;
	int fireLevel;
public:
	virtual int GetBombNum(void)const;
	virtual int GetFireLevel(void)const;
	virtual int GetMV(void)const;
	virtual void AddBombNum(void);
	virtual void AddFireLevel(void);
	virtual void AddMV(void);
};

