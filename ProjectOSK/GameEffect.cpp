#include "GameEffect.h"
#include "GameConstant.h"
#include "MapState.h"
#include "Timer.h"
#include "Image.h"


using namespace BombBombCrash;

GameEffect::GameEffect():
white(GetColor(255, 255, 255)),
x(32 * 20),
y(32 * 4),
fpsTIme_i(0), fps(0)
{
	fpsTime[0] = 0;
	fpsTime[1] = 0;
}

GameEffect::~GameEffect(void)
{
}

void GameEffect::Initialize(GameManager& game)
{
}

void GameEffect::Update(GameManager& game)
{
}

void GameEffect::Draw(const GameManager& game)
{
	int black = GetColor(255, 255, 255);
	int red = GetColor(255, 0, 0);
	int blue = GetColor(0, 0, 255);
	int deepskyblue = GetColor(0, 191, 255);
	int cannotWalkBlockColor;
	for (int i = 0; i<BombBombCrash::MAP_ROW; ++i)
	{
		for (int j = 0; j<BombBombCrash::MAP_LINE; ++j)
		{
			if (i == 0 || i == 12 || j == 0 || j == 1 || j == 15 || j == 16 || MapState::GetInstance()->GetState(i, j, MapState::MAP) == 1)
				cannotWalkBlockColor = deepskyblue;
			else
				cannotWalkBlockColor = black;

			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i,j,MapState::BOMB));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i, j, CHARACTOR));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
		}
	}

	int newBlue = GetColor(0, 119, 182);
	int white = GetColor(255, 255, 255);


	if (fpsTIme_i == 0)
		fpsTime[0] = GetNowCount();               //1周目の時間取得
	if (fpsTIme_i == 49){
		fpsTime[1] = GetNowCount();               //50周目の時間取得
		fps = 1000.0f / ((fpsTime[1] - fpsTime[0]) / 50.0f);//測定した値からfpsを計算
		fpsTIme_i = 0;//カウントを初期化
	}
	else
		fpsTIme_i++;//現在何周目かカウント
	if (fps != 0)
		DrawFormatString(32 * 11, 32 * 14, white, "FPS %.1f", fps); //fpsを表示



	DrawString(x - 82, y - 30, "プレイヤーステータス", newBlue);
	DrawFormatString(x - 39, y, white, "BOMB  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->bombLevel);
	DrawFormatString(x - 39, y + 25, white, "FIRE  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->fireLevel);
	DrawFormatString(x - 39, y + 25 + 25, white, "SPEED LEVEL		%d", MapState::GetInstance()->GetPlayerState()->speedLevel);

	DrawFormatString(32 * 1, 32 * 14, white, "ｚキー　　　爆弾を置く");
	DrawFormatString(32 * 1, 32 * 14 + 30, white, "矢印キー　　各方向へ移動");

	int floorImage = Image::GetInstance()->GetImage(Image::FLOOR);
	for (size_t i = 0; i < MAP_ROW; i++)
	{
		for (size_t j = 0; j < MAP_LINE; j++)
		{
			DrawGraph(j*GameConstant::BlockWidth, i*GameConstant::BlockHeight, floorImage, false);
		}
	}
}




