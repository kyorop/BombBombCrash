#pragma once

class AnimationClip
{
	std::vector<int> image_handles_;
public:
	AnimationClip() = default;
	explicit AnimationClip(std::vector<int> image_handles)
		: image_handles_(std::move(image_handles))
	{
	}

	explicit AnimationClip(int image_handle) :
		image_handles_(std::vector<int>(1, image_handle))
	{
	}
	
	void AddImage(int image_handle);
	void SetAnimation(std::vector<int> image_handles);
	int get_handle(int i)const;
	int get_handle()const{ return image_handles_[0]; }
	int Length() const{	return image_handles_.size(); }
};
