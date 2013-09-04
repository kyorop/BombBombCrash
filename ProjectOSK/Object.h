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
	virtual void CheckHItCharactor(Player *player);
	int GetFlag()const;
	void SetFlag(int flag);
	Object();
	~Object(void);
};

