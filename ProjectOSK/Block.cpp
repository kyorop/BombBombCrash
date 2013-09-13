#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "DxLib.h"
#include <cstring>
#define HABA 0
#define DHIT 5
#define KBHABA 16

Block::Block(void)
{
	this->graph = LoadGraph("breakblock.bmp");

	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	memcpy(this->ID,temp, sizeof temp);

	//ç¿ïWÇÃê›íË
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			this->x[i][j] = 32 * j;
			this->rx[i][j] = 32 * j + 32;
			this->y[i][j] = 32 * i;
			this->dy[i][j] = 32 * i + 32;
		}
	}

	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(this->ID[i][j] == 2)
				this->flag[i][j] = TRUE;
			else
				this->flag[i][j] = FALSE;
		}
	}
}

void Block::Draw()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(this->ID[i][j] == 2 && this->flag[i][j] == TRUE)
				DrawGraph(this->x[i][j], this->y[i][j], this->graph, FALSE);
		}
	}
}

void Block::CheckHit(Charactor *charactor)
{
	int lx, rx, uy, dy;

	lx = (charactor->GetX()+HABA) / 32;
	rx = (charactor->GetX()+32-HABA) / 32;
	uy = (charactor->GetY()+HABA) / 32;
	dy = (charactor->GetY()+32-HABA) / 32;

			//Å†Å©
			if( (this->rx[uy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[uy][lx]) && (this->y[uy][lx]+DHIT <= charactor->GetY() && charactor->GetY() < this->dy[uy][lx]-DHIT) && this->flag[uy][lx] == TRUE)charactor->SetX(this->x[uy][lx] + 32);//ìríÜ
			if( (this->rx[dy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[dy][lx]) && (this->y[dy][lx]+DHIT <= charactor->GetDY() && charactor->GetDY() < this->dy[dy][lx]-DHIT) && this->flag[dy][lx] == TRUE)charactor->SetX(this->x[dy][lx] + 32);//è„Ç¢Ç¡ÇΩ
	
			////Å®Å†
			//if((this->x[uy][lx] <= charactor->GetX() && charactor->GetX() < this->x[uy][lx]+DHIT) && (this->y[uy][rx]+DHIT <= charactor->GetY() && charactor->GetY() < this->dy[uy][rx]-DHIT) && this->flag[uy][rx] == TRUE)charactor->SetX(this->x[uy][rx]- 32) ;//ìríÜ
			//if((this->x[dy][lx] <= charactor->GetX() && charactor->GetX() < this->x[dy][lx]+DHIT) && (this->y[dy][rx]+DHIT <=charactor->GetDY() && charactor->GetDY() < this->dy[dy][rx]-DHIT) && this->flag[dy][rx] == TRUE)charactor->SetX(this->x[dy][rx] - 32);//è„Ç¢Ç¡ÇΩ
	
			//Å®Å†
			if((this->x[uy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[uy][rx]+DHIT) && (this->y[uy][rx]+DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]-DHIT) && this->flag[uy][rx] == 1)charactor->SetX(this->x[uy][rx]- 32);//ìríÜ
			if((this->x[dy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[dy][rx]+DHIT) && (this->y[dy][rx]+DHIT <=charactor->GetDY() && charactor->GetDY() <= this->dy[dy][rx]-DHIT) && this->flag[dy][rx] == 1)charactor->SetX(this->x[dy][rx] - 32);//è„Ç¢Ç¡ÇΩ

					
			//Å†
			//Å™
			if( (this->dy[uy][lx]-DHIT < charactor->GetY() && charactor->GetY() <= this->dy[uy][lx]) && (this->x[uy][lx]+DHIT <= charactor->GetX() && charactor->GetX() < this->rx[uy][lx]-DHIT) && this->flag[uy][lx] == TRUE)charactor->SetY(this->dy[uy][lx]);//ç∂çsÇ≠
			if( (this->dy[uy][rx]-DHIT < charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]) && (this->x[uy][rx]+DHIT <= charactor->GetRX() && charactor->GetRX() < this->rx[uy][rx]-DHIT) && this->flag[uy][rx] == TRUE)charactor->SetY(this->dy[uy][rx]);//âEçsÇ≠

			//Å´
			//Å†
			if( (this->y[dy][lx] < charactor->GetDY() && charactor->GetDY() <= this->y[dy][lx]+DHIT) && (this->x[dy][lx]+DHIT <= charactor->GetX() && charactor->GetX() < this->rx[dy][lx]-DHIT) && this->flag[dy][lx] == TRUE)charactor->SetY(this->y[dy][lx]-32);//ç∂çsÇ≠
			if( (this->y[dy][rx] < charactor->GetDY() && charactor->GetDY() <= this->y[dy][rx]+DHIT) && (this->x[dy][rx]+DHIT <= charactor->GetRX() && charactor->GetRX() < this->rx[dy][rx]-DHIT) && this->flag[dy][rx] == TRUE)charactor->SetY(this->y[dy][rx]-32);//âEçsÇ≠

			//ê^ç∂
			if( (this->y[uy][lx] <= charactor->GetY() && charactor->GetY() < this->y[uy][lx]+DHIT) && (this->rx[uy][lx]-DHIT < charactor->GetX() && charactor->GetX() <= this->rx[uy][lx]) && this->flag[uy][lx] == TRUE)charactor->SetX(this->x[uy][lx] + 32);
			if( (this->dy[dy][lx]-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy[dy][lx]) && (this->rx[dy][lx]-DHIT < charactor->GetX() && charactor->GetX() <= this->rx[dy][lx]) && this->flag[dy][lx] == TRUE )charactor->SetX(this->x[dy][lx] + 32);

			//ê^âE
			if( (this->y[uy][rx] <= charactor->GetY() && charactor->GetY() < this->y[uy][rx]+DHIT) && (this->x[uy][rx] <= charactor->GetRX() && charactor->GetRX() < this->x[uy][rx]+DHIT) && this->flag[uy][rx] == TRUE)charactor->SetX(this->x[uy][rx]- 32);
			if( (this->dy[dy][rx]-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy[dy][rx]) && (this->x[dy][rx] <= charactor->GetRX() && charactor->GetRX() < this->x[dy][rx]+DHIT) && this->flag[dy][rx] == TRUE)charactor->SetX(this->x[dy][rx] - 32);

			//ê^è„
			if( (this->x[uy][lx] <= charactor->GetX() && charactor->GetX() < this->x[uy][lx]+DHIT) && (this->dy[uy][lx]-DHIT < charactor->GetY() && charactor->GetY() <= this->dy[uy][lx]) && this->flag[uy][lx] == TRUE)charactor->SetY(this->dy[uy][lx]);
			if( (this->rx[uy][rx]-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[uy][rx]) && (this->dy[uy][rx]-DHIT < charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]) && this->flag[uy][rx] == TRUE)charactor->SetY(this->dy[uy][rx]);

			//ê^â∫
			if( (this->x[dy][lx] <= charactor->GetX() && charactor->GetX() < this->x[dy][lx]+DHIT) && (this->y[dy][lx] < charactor->GetDY() && charactor->GetDY() <= this->y[dy][lx]+DHIT) && this->flag[dy][lx] == TRUE)charactor->SetY(this->y[dy][lx] - 32);
			if( (this->rx[dy][rx]-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[dy][rx]) && (this->y[dy][rx] < charactor->GetDY() && charactor->GetDY() <= this->y[dy][rx]+DHIT) && this->flag[dy][rx] == TRUE)charactor->SetY(this->y[dy][rx] - 32);

			//ï«ÇÃç∂è„äp
			if( (this->x[dy][rx]+DHIT < charactor->GetRX() && charactor->GetRX() < this->x[dy][rx]+KBHABA) && (this->y[dy][rx]+DHIT < charactor->GetDY() && charactor->GetDY() < this->y[dy][rx]+KBHABA) && this->flag[dy][rx] == 1)charactor->SetX(this->x[dy][rx]-32+DHIT-charactor->GetMV());
			//ï«ÇÃâEè„äp
			if( (this->rx[dy][lx]-KBHABA < charactor->GetX() && charactor->GetX() < this->rx[dy][lx]-DHIT) && (this->y[dy][lx]+DHIT < charactor->GetDY() && charactor->GetDY() < this->y[dy][lx]+KBHABA) && this->flag[dy][lx] == 1)charactor->SetX(this->rx[dy][lx]-DHIT+charactor->GetMV());
			//ï«ÇÃç∂â∫äp
			if( (this->x[uy][rx]+DHIT < charactor->GetRX() && charactor->GetRX() < this->x[uy][rx]+KBHABA) && (this->dy[uy][rx]-KBHABA < charactor->GetY() && charactor->GetY() < this->dy[uy][rx]-DHIT) && this->flag[uy][rx] == 1)charactor->SetX(this->x[uy][rx]-32+DHIT-charactor->GetMV());
			//ï«ÇÃâEâ∫äp
			if( (this->rx[uy][lx]-KBHABA < charactor->GetX() && charactor->GetX() < this->rx[uy][lx]-DHIT) && (this->dy[uy][lx]-KBHABA < charactor->GetY() && charactor->GetY() < this->dy[uy][lx]-DHIT) && this->flag[uy][lx] == 1)charactor->SetX(this->rx[uy][lx]-DHIT+charactor->GetMV());
	
}

Block::~Block(void)
{
}
