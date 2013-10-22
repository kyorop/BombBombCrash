#include "Object.h"
#include "Player.h"
#include "Charactor.h"
#include "DxLib.h"
#define DHIT 10

Object::Object():
	x(0),
	y(0),
	flag(1)
{
}

Object::~Object(void)
{
}

int Object::CheckHItCharactor(Charactor &charactor)
{
	if(this->flag == 1)//•¨‘Ì‚ª•\Ž¦‚³‚ê‚Ä‚¢‚é‚Æ‚«
	{
		if(this->x+32-DHIT > charactor.GetX() && this->x+DHIT < charactor.GetRX() && this->y+DHIT < charactor.GetDY() && charactor.GetY() < this->y+32-DHIT)
		{
			this->flag = 0;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}



int Object::GetFlag()const
{
	return this->flag;
}

void Object::SetFlag(int flag)
{
	this->flag = flag;
}

int Object::GetX()const
{
	return this->x;
}

int Object::GetY()const
{
	return this->y;
}