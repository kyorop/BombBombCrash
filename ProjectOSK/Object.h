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
	int GetFlag()const;
	void SetFlag(int flag);
	Object();
	~Object(void);
};

