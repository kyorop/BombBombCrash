#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "BombManager.h"
#include "Item.h"
#include "DxLib.h"
#define DHIT 6

//�R���X�g���N�^
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph( LoadGraph("fire.bmp") ), upx(upx), downx(downx), upy(upy), downy(downy)
{
	this->fuse = 0;
	this->explosion = 0;
}

//�{�����u����āA���ꂪ��������ƁA�΂𑶍݂�����
void Explosion::Set(const Bomb &bomb)//���e�̂���ExplosionManager�̒��ň�ԏ��߂ɕ`��
{
	this->x = bomb.GetX() + 32*upx - 32*downx;//���S����̍L����
	this->y = bomb.GetY() + 32*upy - 32*downy;
}

//�v���C���[�Ƃ̂����蔻��
int Explosion::CheckHItCharactor(Charactor *charactor)//Object��CheckHit���I�[�o�[���C�h
{
	if(this->explosion == TRUE)//�΂����݂��Ă���Ƃ�
	{
		if(this->x+32-DHIT > charactor->GetX() && this->x+DHIT < charactor->GetRX() && this->y+DHIT < charactor->GetDY() && charactor->GetY() < this->y+32-DHIT)
		{
			charactor->SetCharactorState(FALSE);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

//�ǂƂ̂����蔻��
void Explosion::CheckHitObject(MapObstacle *mapobstacle)
{
	int i = this->y / 32;
	int j = this->x / 32;

	if(this->explosion == TRUE)
	{
		if(mapobstacle->GetID(i, j) == 1)//�΂��`�����\��̏ꏊ�̎��ʒl���}�b�v�̕ǂȂ�A�΂������Ȃ��悤�ɂ���B
		{
			this->explosion = FALSE;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//�΂��`�����\��̏ꏊ�̎��ʒl���A����u���b�N�Ȃ�A���̃u���b�N���󂵂āA�΂͕`���Ȃ�
		{
			mapobstacle->SetFlag(i, j, FALSE);//�u���b�N������
			this->explosion = FALSE;//�΂͏���
		}
	}
}

void Explosion::CheckHitBomb(Bomb *bomb)
{
	if(this->explosion == TRUE && bomb->GetFlag() == TRUE)
	{
		if(this->x+32-DHIT > bomb->GetX() && this->x+DHIT < bomb->GetX()+32 && this->y+DHIT < bomb->GetY()+32 && bomb->GetY() < this->y+32-DHIT)
		{
			this->explosion = FALSE;
			bomb->SetFlag(FALSE);
		}
	}
}

void Explosion::CheckHitItem(Item *item)
{
	if(this->explosion == TRUE && item->GetFlag() == TRUE)
	{
		if( this->x+32 > item->GetX() && this->x < item->GetX()+32 && this->y < item->GetY()+32 && this->y+32 > item->GetY() )
		{
			this->explosion = FALSE;
			item->SetFlag(FALSE);
		}
	}
}

//�΂����݂��Ă���΁A�`��
void Explosion::Draw()
{
	if(this->explosion == TRUE)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//�f�X�g���N�^
Explosion::~Explosion(void)
{
}


void Explosion::SetExplosion(int flag)
{
	this->explosion = flag;
}

int Explosion::GetExplosion()
{
	return this->explosion;
}