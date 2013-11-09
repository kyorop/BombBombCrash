#pragma once
class ISoundPlayer
{
public:
	virtual ~ISoundPlayer(void){}

	virtual int EnableToPlaySound()const = 0;
};