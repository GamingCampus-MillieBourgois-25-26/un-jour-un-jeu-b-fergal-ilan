
#pragma once

struct GameState
{
    int   points = 0;
    int   pointsPerClick = 1;
    float autoClickRate = 0.f;  // points par seconde (pas clics/seconde)
    float autoAccumulator = 0.f;  // accumule les fractions
};

extern GameState gGameState;