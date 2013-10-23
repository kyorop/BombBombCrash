#pragma once

class IMediator
{
public:
	virtual ~IMediator(){}
	
	virtual void CreateColleague() = 0;
	virtual void ColleagueChange() = 0;


};