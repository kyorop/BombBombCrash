#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "DxLib.h"
#define DHIT 6
enum firestate
{
	FIREOFF,
	FIREON,
	EXPLOSION,
};


//�R���X�g���N�^
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph( LoadGraph("fire.bmp") ), upx(upx), downx(downx), upy(upy), downy(downy)
{
}

//�{�����u����āA���ꂪ��������ƁA�΂𑶍݂�����
void Explosion::SetExplosion(const Bomb &bomb)//���e�̂���ExplosionManager�̒��ň�ԏ��߂ɕ`��
{
	if(bomb.flag == 1)//�{�����u���ꂽ
		this->flag = FIREON;

	else if(bomb.flag == 0 && this->flag == FIREON)//�{������������
	{
		if(time.CountDown(1000) == false)
		{
			this->x = bomb.x + 32*upx - 32*downx;//���S����̍L����
			this->y = bomb.y + 32*upy - 32*downy;
			this->flag = EXPLOSION;
		}
		else
			this->flag = FIREOFF;
	}
}

//�v���C���[�Ƃ̂����蔻��
int Explosion::CheckHItCharactor(Charactor *charactor)//Object��CheckHit���I�[�o�[���C�h
{
	if(this->flag == EXPLOSION)//�΂����݂��Ă���Ƃ�
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

	if(this->flag == EXPLOSION)
	{
		if(mapobstacle->GetID(i, j) == 1)//�΂��`�����\��̏ꏊ�̎��ʒl���}�b�v�̕ǂȂ�A�΂������Ȃ��悤�ɂ���B
		{
			this->flag = FIREOFF;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//�΂��`�����\��̏ꏊ�̎��ʒl���A����u���b�N�Ȃ�A���̃u���b�N���󂵂āA�΂͕`���Ȃ�
		{
			mapobstacle->SetFlag(i, j, FALSE);//�u���b�N������
			this->flag = FIREOFF;//�΂͏���
		}
	}
}

//�΂����݂��Ă���΁A�`��
void Explosion::Draw()
{
	if(this->flag == EXPLOSION)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//�f�X�g���N�^
Explosion::~Explosion(void)
{
}

firestate Explosion::GetFlag()const
{
	return this->flag;
}

void Explosion::SetFlag(firestate flag)
{
	this->flag = flag;
}