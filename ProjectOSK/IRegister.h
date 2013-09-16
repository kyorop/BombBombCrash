#pragma once

class IRegister
{
public:
	virtual ~IRegister(void);
	virtual void Register() = 0;
};

