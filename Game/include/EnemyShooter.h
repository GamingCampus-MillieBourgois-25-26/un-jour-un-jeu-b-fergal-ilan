#pragma once

#include "Core/Component.h"
#include "Bullet.h"
#include "Patterns.h"
class EnemyShooter : public Component
{
public:
    int phase = 0;
    float timer = 0.f;

    void Update(float _delta_time) override
    {
        timer += _delta_time;

        if (timer > 1.f + (phase * 0.2f))
        {
            if (phase == 0)
                FPatterns::FShootCircle(GetOwner());
            else if (phase == 1)
                FPatterns::FShootSpiral(GetOwner());
            else if (phase == 2)
                FPatterns::FShootWave(GetOwner());
            else
                FPatterns::FShootLaser(GetOwner());

            timer = 0.f;
            phase = (phase + 1) % 4;
        }
    }
};
//Patterns::ShootCircle(GetOwner());
//Patterns::ShootSpiral(GetOwner());
//Patterns::ShootWave(GetOwner());
//Patterns::ShootLaser(GetOwner());