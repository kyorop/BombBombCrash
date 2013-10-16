#pragma once
#include "GameConstant.h"

class DangerState
{
private:
	struct DangerNode
	{
	public:
		//DangerNode (*pBrastCenter)[];
		//DangerNode *pBrastCenter;
		int danger;
		int i_brastCenter;
		int j_brastCenter;
	public:
		DangerNode();
	};

public:
	static DangerNode node[GameConst::MAP_ROW][GameConst::MAP_LINE];

private:
	DangerState(void);
	DangerState(const DangerState &ds);
	~DangerState(void);

public:
	static DangerState *GetInstance()
	{
		static DangerState dsInstance;
		return &dsInstance;
	}
	
	void Update();
	int GetDangerState(int i, int j);
};

