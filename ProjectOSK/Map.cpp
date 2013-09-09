#include "Map.h"
#include "Player.h"
#include "DxLib.h"
#include "Charactor.h"
#include <cstring>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13
#define DHIT 7
#define HABA 0
#define KBHABA 16//(DHIT+1)
#define MV 4

Map::Map(void)
{
	//ID
	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
	std::memcpy(this->ID, temp, sizeof temp);

	this->graph[0] = LoadGraph("yuka.bmp");
	//this->graph[1] = LoadGraph("rimblock.bmp");
	this->graph[1] = LoadGraph("redblock.bmp");
	
	//壁の座標セット
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
				this->x[i][j] = 32 * j;
				this->rx[i][j] = this->x[i][j]+32;
				this->y[i][j] = 32 * i;
				this->dy[i][j] = this->y[i][j]+32;
		}
	}
}

void Map::Draw()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(this->ID[i][j] == 1)
				DrawGraph(this->x[i][j], this->y[i][j], this->graph[1],FALSE);
			else if(this->ID[i][j] == 0)
				DrawGraph(this->x[i][j], this->y[i][j], this->graph[0],FALSE);
		}
	}
}

void Map::CheckHitCharactor(Charactor *charactor)
{
	int lx, rx, uy, dy;

	lx = (charactor->GetX() + HABA) / 32;
	rx = (charactor->GetX() + 32 - HABA) / 32;
	uy = (charactor->GetY() + HABA) / 32;
	dy = (charactor->GetY() + 32 - HABA) / 32;


	//□←
	if( (this->rx[uy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[uy][lx]) && (this->y[uy][lx]+DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][lx]-DHIT) && this->ID[uy][lx] == 1)charactor->SetX(this->rx[uy][lx]);//途中
	if( (this->rx[dy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[dy][lx]) && (this->y[dy][lx]+DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy[dy][lx]-DHIT) && this->ID[dy][lx] == 1)charactor->SetX(this->x[dy][lx] + 32);//上いった
	
	//→□
	if((this->x[uy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[uy][rx]+DHIT) && (this->y[uy][rx]+DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]-DHIT) && this->ID[uy][rx] == 1)charactor->SetX(this->x[uy][rx]- 32);//途中
	if((this->x[dy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[dy][rx]+DHIT) && (this->y[dy][rx]+DHIT <=charactor->GetDY() && charactor->GetDY() <= this->dy[dy][rx]-DHIT) && this->ID[dy][rx] == 1)charactor->SetX(this->x[dy][rx] - 32);//上いった

	//□
	//↑
	if( (this->dy[uy][lx]-DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][lx]) && (this->x[uy][lx]+DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[uy][lx]-DHIT) && this->ID[uy][lx] == 1)charactor->SetY(this->dy[uy][lx]);//左行く
	if( (this->dy[uy][rx]-DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]) && (this->x[uy][rx]+DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[uy][rx]-DHIT) && this->ID[uy][rx] == 1)charactor->SetY(this->dy[uy][rx]);//右行く

	//↓
	//□
	if( (this->y[dy][lx] <= charactor->GetDY() && charactor->GetDY() <= this->y[dy][lx]+DHIT) && (this->x[dy][lx]+DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[dy][lx]-DHIT) && this->ID[dy][lx] == 1)charactor->SetY(this->y[dy][lx]-32);//左行く
	if( (this->y[dy][rx] <= charactor->GetDY() && charactor->GetDY() <= this->y[dy][rx]+DHIT) && (this->x[dy][rx]+DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[dy][rx]-DHIT) && this->ID[dy][rx] == 1)charactor->SetY(this->y[dy][rx]-32);//右行く

	//真左□←
	if( (this->y[uy][lx] <= charactor->GetY() && charactor->GetY() < this->y[uy][lx]+DHIT) && (this->rx[uy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[uy][lx]) && this->ID[uy][lx] == 1)charactor->SetX(this->rx[uy][lx]);
	if( (this->dy[dy][lx]-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy[dy][lx]) && (this->rx[dy][lx]-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx[dy][lx]) && this->ID[dy][lx] == 1 )charactor->SetX(this->rx[dy][lx]);

	//真右→□
	if( (this->y[uy][rx] <= charactor->GetY() && charactor->GetY() < this->y[uy][rx]+DHIT) && (this->x[uy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[uy][rx]+DHIT) && this->ID[uy][rx] == 1)charactor->SetX(this->x[uy][rx]- 32);
	if( (this->dy[dy][rx]-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy[dy][rx]) && (this->x[dy][rx] <= charactor->GetRX() && charactor->GetRX() <= this->x[dy][rx]+DHIT) && this->ID[dy][rx] == 1)charactor->SetX(this->x[dy][rx] - 32); 

	//　　□　
	//真上↑
	if( (this->x[uy][lx] <= charactor->GetX() && charactor->GetX() < this->x[uy][lx]+DHIT) && (this->dy[uy][lx]-DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][lx]) && this->ID[uy][lx] == 1)charactor->SetY(this->dy[uy][lx]);
	if( (this->rx[uy][rx]-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[uy][rx]) && (this->dy[uy][rx]-DHIT <= charactor->GetY() && charactor->GetY() <= this->dy[uy][rx]) && this->ID[uy][rx] == 1)charactor->SetY(this->dy[uy][rx]);

	//　　↓
	//真下□
	if( (this->x[dy][lx] <= charactor->GetX() && charactor->GetX() <= this->x[dy][lx]+DHIT) && (this->y[dy][lx] <= charactor->GetDY() && charactor->GetDY() <= this->y[dy][lx]+DHIT) && this->ID[dy][lx] == 1)charactor->SetY(this->y[dy][lx] - 32);
	if( (this->rx[dy][rx]-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx[dy][rx]) && (this->y[dy][rx] <= charactor->GetDY() && charactor->GetDY() <= this->y[dy][rx]+DHIT) && this->ID[dy][rx] == 1)charactor->SetY(this->y[dy][rx] - 32);

	
	//壁の左上角
	if( (this->x[dy][rx]+DHIT < charactor->GetRX() && charactor->GetRX() < this->x[dy][rx]+KBHABA) && (this->y[dy][rx]+DHIT < charactor->GetDY() && charactor->GetDY() < this->y[dy][rx]+KBHABA) && this->ID[dy][rx] == 1)charactor->SetX(this->x[dy][rx]-32+DHIT-charactor->GetMV());
	//壁の右上角
	if( (this->rx[dy][lx]-KBHABA < charactor->GetX() && charactor->GetX() < this->rx[dy][lx]-DHIT) && (this->y[dy][lx]+DHIT < charactor->GetDY() && charactor->GetDY() < this->y[dy][lx]+KBHABA) && this->ID[dy][lx] == 1)charactor->SetX(this->rx[dy][lx]-DHIT+charactor->GetMV());
	//壁の左下角
	if( (this->x[uy][rx]+DHIT < charactor->GetRX() && charactor->GetRX() < this->x[uy][rx]+KBHABA) && (this->dy[uy][rx]-KBHABA < charactor->GetY() && charactor->GetY() < this->dy[uy][rx]-DHIT) && this->ID[uy][rx] == 1)charactor->SetX(this->x[uy][rx]-32+DHIT-charactor->GetMV());
	//壁の右下角
	if( (this->rx[uy][lx]-KBHABA < charactor->GetX() && charactor->GetX() < this->rx[uy][lx]-DHIT) && (this->dy[uy][lx]-KBHABA < charactor->GetY() && charactor->GetY() < this->dy[uy][lx]-DHIT) && this->ID[uy][lx] == 1)charactor->SetX(this->rx[uy][lx]-DHIT+charactor->GetMV());
	

	


}

Map::~Map(void)
{
}
