#pragma once


class IGettable
{
public:
	virtual ~IGettable(void){};

	virtual int GetX()const = 0;
	virtual int GetRX()const = 0;
	virtual int GetY()const = 0;
	virtual int GetDY()const = 0;
	virtual int GetFlag()const = 0;
};

