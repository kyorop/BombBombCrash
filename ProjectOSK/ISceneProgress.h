#pragma once

namespace BombBombCrash
{
	interface ISceneProgress
	{
		virtual void Initialize()=0;
		virtual void Update()=0;
		virtual void Draw()=0;
		virtual void Destroy()=0;

		virtual ~ISceneProgress()
		{
		}

	};
}



