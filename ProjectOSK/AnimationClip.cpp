#include "AnimationClip.h"

void AnimationClip::AddImage(int image_handle)
{
	image_handles_.push_back(image_handle);
}

void AnimationClip::SetAnimation(std::vector<int> image_handles)
{
	if (image_handles.empty())
		return;

	image_handles_ = std::move(image_handles);
}


int AnimationClip::get_handle(int i)const
{
	if (i < 0 || image_handles_.size() <= i)
		return image_handles_[0];

	return image_handles_[i];
}

