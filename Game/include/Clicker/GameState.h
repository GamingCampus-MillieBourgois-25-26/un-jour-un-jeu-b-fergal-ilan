#pragma once

struct GameState
{
    int   points = 0;
    int   pointsPerClick = 1;
    float autoClickRate = 0.f;
    float autoAccumulator = 0.f;
};

extern GameState gGameState;