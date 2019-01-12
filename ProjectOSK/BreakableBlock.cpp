#include "stdafx.h"
#include "BreakableBlock.h"
#include "Image.h"


void BreakableBlock::OnCollide(MapObject& other)
{
	if (other.Type() == Fire)
	{
		Delete();

		if (item_ == nullptr)
			return;

		Create(move(item_));
	}
}

void BreakableBlock::Initialize()
{
	image_ = BombBombCrash::Image::GetInstance()->Load("Images\\breakblock.bmp");
}

void BreakableBlock::Draw()
{
	DrawGraph(X(), Y(), image_.get_handle(), false);
}
