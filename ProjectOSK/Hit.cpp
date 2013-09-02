#include "Hit.h"

/*
void Hit::CheckHit(Player *player)
{
	if( (this->x		< player->x+player->width)	&&
		(player->x	< this->x+this->width)			&&
		(this->y		< player->y+player->height)	&&
		(player->y	< this->y+this->height)				)
		{
			switch(player->muki[0])
			{
			case LEFT:	player->x		=	this->x	+	player->width;break;
			case RIGHT: player->x	=	this->x	-	player->width;break;
			case UP:		 player->y =	this->y	+	this->height;break;
			case DOWN:player->y	=	this->y	-	player->height;break;
			}
		}
		else
		{
			player->muki[0] = NOHIT;
		}
}
*/



Hit::Hit(void)
{
}


Hit::~Hit(void)
{
}
