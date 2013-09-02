#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "DxLib.h"
#define DHIT 6

/*
void Explosion::Draw(const Map &map, const Bomb &bomb)
{
	//DrawGraph(this->x,this->y, this->graph, FALSE);

	this->x = bomb.x;
	this->y = bomb.y;

	//int x_center = (this->x + this->x + 32) / 2;
	//int y_center = (this->y + this->y + 32) / 2;

	if(bomb.flag == 1)
		this->flag = 1;

	if(bomb.flag == 0)
	{
		if(this->flag == 1)
			this->flag = 2;
	}
	if(this->flag == 2)
	{
		if(Timer(3000))
		{
			//DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32],this->graph,FALSE);//���S

			//DrawGraph(this->x+32*p-32*q, this->y+32*r-32*s,this->graph,FALSE);//���S
			DrawGraph(this->xHZ, this->yHZ,this->graph,FALSE);//���S
			//if(map.mapchip[y_center/32][x_center/32-1] == 0)DrawGraph(map.x[y_center/32][x_center/32]-32, map.y[y_center/32][x_center/32],	this->graph, TRUE);//��	
			//if(map.mapchip[y_center/32][x_center/32+1] == 0)DrawGraph(map.x[y_center/32][x_center/32]+32, map.y[y_center/32][x_center/32],this->graph, TRUE);//�E
			//if(map.mapchip[y_center/32-1][x_center/32] == 0)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]-32,	this->graph, TRUE);//��	
			//if(map.mapchip[y_center/32+1][x_center/32] == 0)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]+32,this->graph, TRUE);//��

			//if(map.mapchip[y_center/32][x_center/32-1] == 0)DrawGraph(this->x-32, this->y,	this->graph, TRUE);//��	
			//if(map.mapchip[y_center/32][x_center/32+1] == 0)DrawGraph(this->x+32, this->y,this->graph, TRUE);//�E
			//if(map.mapchip[y_center/32-1][x_center/32] == 0)DrawGraph(this->x, this->y-32,	this->graph, TRUE);//��	
			//if(map.mapchip[y_center/32+1][x_center/32] == 0)DrawGraph(this->x, this->y+32,this->graph, TRUE);//��
		}
		else
			this->flag = 0;
	}
}
*/

//�R���X�g���N�^
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph(LoadGraph("fire.bmp")),upx(upx),downx(downx),upy(upy),downy(downy)
{
}

//�{�����u����āA���ꂪ��������ƁA�΂𑶍݂�����
void Explosion::SetExplosion(const Bomb &bomb)//���e�̂���ExplosionManager�̒��ň�ԏ��߂ɕ`��
{
	if(bomb.flag == 1)//�{�����u���ꂽ
		this->flag = 1;

	else if(bomb.flag == 0 && this->flag == 1)//�{������������
	{
		this->flag = 2;
		this->x = bomb.x + 32*upx - 32*downx;//���S����̍L����
		this->y = bomb.y + 32*upy - 32*downy;
	}
}

//�΂����݂��Ă���Ȃ�΁A���W��^����
void Explosion::SetZahyou(const Bomb &bomb)//���S���W
{
	this->x = bomb.x + 32*upx - 32*downx;//���S����̍L����
	this->y = bomb.y + 32*upy - 32*downy;
}

//�v���C���[�Ƃ̂����蔻��
int Explosion::CheckHItCharactor(Charactor *charactor)//Object��CheckHit���I�[�o�[���C�h
{
	if(this->flag == 2)//�΂����݂��Ă���Ƃ�
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

	if(this->flag == 2)
	{
		if(mapobstacle->GetID(i, j) == 1)//�΂��`�����\��̏ꏊ�̎��ʒl���}�b�v�̕ǂȂ�A�΂������Ȃ��悤�ɂ���B
		{
			this->flag = 0;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//�΂��`�����\��̏ꏊ�̎��ʒl���A����u���b�N�Ȃ�A���̃u���b�N���󂵂āA�΂͕`���Ȃ�
		{
			mapobstacle->SetFlag(i, j, FALSE);//�u���b�N������
			//mapobstacle->SetID(i, j, 0);//���Ƃ݂Ȃ�
			this->flag = 0;//�΂͏���
		}
	}
}

//�΂����݂��Ă���΁A�`��
void Explosion::Draw(const Bomb &bomb)
{
	if(this->flag == 2)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//�f�X�g���N�^
Explosion::~Explosion(void)
{
}

//�Ă΂�Ă�������~���b�J�E���g����
bool Explosion::Timer(int time)
{
	static bool resetTime = true;
	static int startTime;

	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
	}

	if(GetNowCount() - startTime < time)//3�b�Ԃ̓X�^�[�g���Ԃ����Z�b�g���Ȃ�
	{
		return TRUE;		//���e��\��������
	}
	else
	{
		resetTime = true;//3�b��������X�^�[�g���Ԃ����Z�b�g����
		return FALSE;		//���e������
	}
}

int Explosion::GetFlag()const
{
	return this->flag;
}

void Explosion::SetFlag(int flag)
{
	this->flag = flag;
}