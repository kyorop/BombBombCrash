#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"

class Charactor;
class Map:
        public MapObstacle, public IDrawable
{
        friend class Explosion;
        friend class Bomb;

private:
        int graph[2];

public:
        void CheckHitCharactor(Charactor *charactor);
        void Draw();
        Map(void);
        ~Map(void);
};