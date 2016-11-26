#pragma once

namespace BombBombCrash
{
	class Task
	{
	public:
		virtual ~Task()
		{
		}

		virtual void Initialize(){}
		virtual void Update() = 0;
		virtual void Draw(){}
		virtual void Finalize(){}
	};
}


