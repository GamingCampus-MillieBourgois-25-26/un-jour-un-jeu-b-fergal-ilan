#pragma once
#include "Core/Component.h"
#include "Core/Scene.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Patterns.h"
class Boss : public Component
{
public:
    int maxHP = 300;
    int hp = 300;
    int lastPhase = -1;
    int phase = 0;
    float timer = 0.f;
    bool dead = false;
    void Update(float dt) override
    {
        if (dead) return;
        timer += dt;

        // phase update
        if (hp > 200) phase = 0;
        else if (hp > 100) phase = 1;
        else phase = 2;

        switch (phase)
        {
        case 0: PhaseOne(dt); break;
        case 1: PhaseTwo(dt); break;
        case 2: PhaseThree(dt); break;
        }
        if (phase != lastPhase)
        {
            std::cout << "PHASE CHANGE: " << phase << "\n";
            lastPhase = phase;

            timer = 0.f;
        }
    }

    void TakeDamage(int dmg)
    {
        if (dead) return;

        hp -= dmg;

        if (hp <= 0)
        {
            dead = true;
            std::cout << "BOSS DEAD\n";
        }
    }

    void PhaseOne(float dt)
    {
        if (timer > 1.f)
        {
            Patterns::ShootRadialBurst(GetOwner(), 36);
            timer = 0.f;
        }
    }
    void PhaseTwo(float dt)
    {
        if (timer > 0.2f)
        {
            Patterns::ShootSpiral(GetOwner());
            timer = 0.f;
        }
    }
    void PhaseThree(float dt)
    {
        if (timer > 0.1f)
        {
            Patterns::ShootWave(GetOwner());
            Patterns::ShootRadialBurst(GetOwner(), 24);
            timer = 0.f;
        }
    }
};



