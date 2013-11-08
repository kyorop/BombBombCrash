#pragma once

class Resource
{
public:
	virtual ~Resource(){}
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
};