#pragma once 

class IObserver
{
public:
	virtual ~IObserver(){}
	virtual void Update() = 0;
};