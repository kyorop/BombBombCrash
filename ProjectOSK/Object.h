#pragma once

class Player;
class Object
{
protected:
	int x;
	int y;
	//int graph;
	int flag;
	

public:
	virtual int CheckHItCharactor(Charactor &charactor);
	int GetX()const;
	int GetY()const;
	int GetFlag()const;
	void SetFlag(int flag);
	Object();
	~Object(void);
};

