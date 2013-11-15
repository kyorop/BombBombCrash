#include "GameEffect.h"
#include "MapState.h"
#include "DxLib.h"


GameEffect::GameEffect(void)
	:white(GetColor(255,255,255)),
	x(32*18),
	y(32*2)
{
}


GameEffect::~GameEffect(void)
{
}


void GameEffect::DrawGameEffect()
{
	DrawFormatString(x, y, white, "BOMB LEVEL		%d", MapState::GetInstance()->GetPlayerState()->bombLevel);
	DrawFormatString(x,y+25, white, "FIRE LEVEL		%d", MapState::GetInstance()->GetPlayerState()->fireLevel);
	DrawFormatString(x,y+25+25, white, "SPEED LEVEL		%d", MapState::GetInstance()->GetPlayerState()->speedLevel);
}


void GameEffect::DrawMenuEffect()
{

}