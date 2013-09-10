#pragma once

class Charactor;
class Object
{
protected:
	int x;
	int y;
	int flag;
public:
	virtual int CheckHItCharactor(Charactor &charactor);
	virtual int GetX()const;
	virtual int GetY()const;
	virtual int GetFlag()const;
	virtual void SetFlag(int flag);
	Object();
	virtual ~Object(void);
};

