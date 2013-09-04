#include "Object.h"
#include "Player.h"
#include "DxLib.h"
#define DHIT 10

Object::Object()
{
	this->x = 0;
	this->y = 0;
	this->flag = 0;
	//this->graph = LoadGraph(graph);
}

void Object::CheckHItCharactor(Player *player)
{
	if(this->flag == 1)//•¨‘Ì‚ª•\Ž¦‚³‚ê‚Ä‚¢‚é‚Æ‚«
	{
		if(this->x+32-DHIT > player->x && this->x+DHIT < player->rx && this->y+DHIT < player->dy && player->y < this->y+32-DHIT)
		{
			this->flag = 0;
		}
	}
}

Object::~Object(void)
{
}

int Object::GetFlag()const
{
	return this->flag;
}

void Object::SetFlag(int flag)
{
	this->flag = flag;
}
