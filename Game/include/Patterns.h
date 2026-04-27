#pragma once
#include <cmath>
#include "Core/GameObject.h"
#include "Bullet.h"
#include "BulletPool.h"

namespace FPatterns
{
    inline void FShootCircle(GameObject* owner)
    {
        for (int i = 0; i < 36; i++)
        {
            float angle = i * 10.f;
            float rad = angle * 3.14159f / 180.f;

            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(
                    std::cos(rad) * 200.f,
                    std::sin(rad) * 200.f
                )
            );
        }
    }

    inline void FShootSpiral(GameObject* owner)
    {
        static float baseAngle = 0.f;

        for (int i = 0; i < 8; i++)
        {
            float angle = baseAngle + i * 20.f;
            float rad = angle * 3.14159f / 180.f;

            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(
                    std::cos(rad) * 200.f,
                    std::sin(rad) * 200.f
                )
            );
        }

        baseAngle += 5.f;
    }

    inline void FShootWave(GameObject* owner)
    {
        static float t = 0.f;

        for (int i = 0; i < 10; i++)
        {
            float offsetY = (i - 5) * 20.f;

            float angle = std::sin(t + i * 0.5f) * 45.f;
            float rad = angle * 3.14159f / 180.f;

            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition() + Maths::Vector2f(0, offsetY),
                Maths::Vector2f(
                    std::cos(rad) * 250.f,
                    std::sin(rad) * 100.f
                )
            );
        }

        t += 0.1f;
    }

    inline void FShootLaser(GameObject* owner)
    {
        float angle = 0.f;
        float rad = angle * 3.14159f / 180.f;

        for (int i = 0; i < 20; i++)
        {
            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            Maths::Vector2f pos = owner->GetPosition() + Maths::Vector2f(
                std::cos(rad) * i * 10.f,
                std::sin(rad) * i * 10.f
            );

            b->Activate(
                pos,
                Maths::Vector2f(
                    std::cos(rad) * 300.f,
                    std::sin(rad) * 300.f
                )
            );
        }
    }
    inline void FShootRadialBurst(GameObject* owner, int bulletCount = 72)
    {
        float step = 360.f / bulletCount;

        for (int i = 0; i < bulletCount; i++)
        {
            float angle = i * step;
            float rad = angle * 3.14159f / 180.f;

            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            Maths::Vector2f dir(
                std::cos(rad),
                std::sin(rad)
            );

            b->Activate(
                owner->GetPosition(),
                dir * 250.f // vitesse
            );
        }
    }
    inline void FShootRadialBurstSpiral(GameObject* owner)
    {
        static float offset = 0.f;

        int bulletCount = 72;
        float step = 360.f / bulletCount;

        for (int i = 0; i < bulletCount; i++)
        {
            float angle = i * step + offset;
            float rad = angle * 3.14159f / 180.f;

            FBullet* b = gBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad), std::sin(rad)) * 250.f
            );
        }

        offset += 2.f; // rotation lente
    }
}