#pragma once
#include "Scene_Base.h"

class Timer;
class Scene_Round
	:public Scene_Base
{
private:
	Timer* timer;
	static int roundNum;
private:
	void UpdateScene()override;
public:
	Scene_Round(void);
	~Scene_Round(void);
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

