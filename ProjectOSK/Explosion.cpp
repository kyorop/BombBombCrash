#include "Explosion.h"
#include "Timer.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "BombManager.h"
#include "Item.h"
#include "DxLib.h"
#define DHIT 6

//�R���X�g���N�^
Explosion::Explosion(int right,int left,int down,int up):
	graph( LoadGraph("fire.bmp") ), 
	upx(right), 
	downx(left),
	upy(down),
	downy(up),
	time(new Timer),
	fuse(0),
	explosion(0)
{
}

Explosion::~Explosion(void)
{
}

//�{�����u����āA���ꂪ��������ƁA�΂𑶍݂�����
void Explosion::Set(int x, int y)//���e�̂���ExplosionManager�̒��ň�ԏ��߂ɕ`��
{
	this->x = x + 32*upx - 32*downx;//���S����̍L����
	this->y = y + 32*upy - 32*downy;
}

void Explosion::SetExplosion(int flag)
{
	explosion = flag;
}

int Explosion::GetExplosion()
{
	return explosion;
}

//void Explosion::SetNext(Explosion *next)
//{
//	nextFire.push_back(next);
//}