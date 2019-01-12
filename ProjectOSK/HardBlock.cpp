#include "HardBlock.h"
#include "Image.h"


void HardBlock::Initialize()
{
}

void HardBlock::Update()
{
}

void HardBlock::Draw()
{
	DrawGraph(X(), Y(), block_image_.get_handle(), true);
}

void HardBlock::Finalize()
{
}
