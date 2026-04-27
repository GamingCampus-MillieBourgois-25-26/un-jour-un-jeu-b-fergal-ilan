// Pattern.h
#pragma once
#include <cmath>
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "BulletH/Bullet.h"
#include "BulletH/BulletPool.h"
#include "BulletH/Player.h"
#include "Core/Component.h"

namespace Patterns
{
    // Utilitaire : récupère l'angle en radians vers le joueur
    inline float GetAngleToPlayer(GameObject* owner)
    {
        Scene* scene = owner->GetScene();
        if (!scene) return 0.f;

        Maths::Vector2f playerPos = { 300.f, 300.f }; // fallback centre
        for (const auto& go : scene->GetGameObjects())
        {
            if (go->GetName() == "Player")
            {
                playerPos = go->GetPosition();
                break;
            }
        }

        const Maths::Vector2f origin = owner->GetPosition();
        float dx = playerPos.x - origin.x;
        float dy = playerPos.y - origin.y;
        float len = std::sqrt(dx * dx + dy * dy);
        if (len == 0.f) return 0.f;

        return std::atan2(dy / len, dx / len);
    }

    // Cercle centré sur la direction joueur
    inline void ShootCircle(GameObject* owner)
    {
        const float baseAngle = GetAngleToPlayer(owner);
        constexpr int count = 30;
        constexpr float speed = 120.f;

        for (int i = 0; i < count; i++)
        {
            float rad = baseAngle + i * (2.f * 3.14159f / count);

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }
    }

    // Spirale partant de la direction joueur
    inline void ShootSpiral(GameObject* owner)
    {
        static float spiralOffset = 0.f;

        const float baseAngle = GetAngleToPlayer(owner) + spiralOffset;
        constexpr int count = 8;
        constexpr float speed = 200.f;

        for (int i = 0; i < count; i++)
        {
            float rad = baseAngle + i * (2.f * 3.14159f / count);

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }

        spiralOffset += 0.15f;
    }

    inline void ShootSpiralspe(GameObject* owner)
    {
        static float spiralOffset = 0.f;

        const float baseAngle = GetAngleToPlayer(owner);

        // Seulement 3 balles par salve, serrées autour de la direction joueur
        // L'offset tourne à chaque appel → effet vrille qui arrive sur le joueur
        constexpr int count = 3;
        constexpr float spread = 25.f * 3.14159f / 180.f; // écart entre les 3 balles
        constexpr float speed = 120.f;

        for (int i = 0; i < count; i++)
        {
            float rad = baseAngle + (i - count / 2) * spread + spiralOffset;

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }

        // Le décalage tourne à chaque salve → les balles arrivent en vrille
        spiralOffset += 0.3f;
        if (spiralOffset > 2.f * 3.14159f)
            spiralOffset = 0.f;
    }

    // Vague perpendiculaire à la direction joueur
    inline void ShootWave(GameObject* owner)
    {
        static float t = 0.f;

        const float baseAngle = GetAngleToPlayer(owner);

        // Vecteur perpendiculaire pour le décalage latéral
        const float perpX = -std::sin(baseAngle);
        const float perpY = std::cos(baseAngle);

        constexpr int count = 10;
        constexpr float speed = 120.f;

        for (int i = 0; i < count; i++)
        {
            float offsetDist = (i - count / 2) * 15.f;
            float waveAngle = std::sin(t + i * 0.5f) * (20.f * 3.14159f / 180.f);
            float rad = baseAngle + waveAngle;

            Maths::Vector2f spawnPos = owner->GetPosition() + Maths::Vector2f(
                perpX * offsetDist,
                perpY * offsetDist
            );

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                spawnPos,
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }

        t += 0.1f;
    }

    // Laser dans la direction du joueur
    inline void ShootLaser(GameObject* owner)
    {
        const float rad = GetAngleToPlayer(owner);
        constexpr int count = 10;
        constexpr float speed = 120.f;

        for (int i = 0; i < count; i++)
        {
            Maths::Vector2f pos = owner->GetPosition() + Maths::Vector2f(
                std::cos(rad) * i * 10.f,
                std::sin(rad) * i * 10.f
            );

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                pos,
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }
    }

    // Éventail centré sur le joueur
    inline void ShootAtPlayer(GameObject* owner)
    {
        const float baseAngle = GetAngleToPlayer(owner);
        constexpr int count = 5;
        constexpr float spread = 15.f * 3.14159f / 180.f;
        constexpr float speed = 120.f;

        for (int i = 0; i < count; i++)
        {
            float rad = baseAngle + (i - count / 2) * spread;

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }
    }

    // Burst radial tourné vers le joueur
    inline void ShootRadialBurst(GameObject* owner, int bulletCount = 72)
    {
        const float baseAngle = GetAngleToPlayer(owner);
        const float step = 2.f * 3.14159f / bulletCount;
        constexpr float speed = 120.f;

        for (int i = 0; i < bulletCount; i++)
        {
            float rad = baseAngle + i * step;

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }
    }

    // Spirale radiale tournée vers le joueur
    inline void ShootRadialBurstSpiral(GameObject* owner)
    {
        static float spiralOffset = 0.f;

        const float baseAngle = GetAngleToPlayer(owner) + spiralOffset;
        constexpr int bulletCount = 72;
        const float step = 2.f * 3.14159f / bulletCount;
        constexpr float speed = 120.f;

        for (int i = 0; i < bulletCount; i++)
        {
            float rad = baseAngle + i * step;

            Bullet* b = hBulletPool.GetBullet();
            if (!b) return;

            b->Activate(
                owner->GetPosition(),
                Maths::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed)
            );
        }

        spiralOffset += 0.05f;
    }
}