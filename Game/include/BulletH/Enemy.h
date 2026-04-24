#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Bullet.h"
#include "Pattern.h"

enum class SpawnSide
{
    Top,
    Bottom,
    Left,
    Right
};


class Enemy : public Component
{
public:
    Enemy(SpawnSide side) : spawnSide(side) {}
    Enemy() = default;
    ~Enemy() override = default;

    int phase = 0;
    float timer = 0.f;

    void Start() override
    {
        const float offset = 60.f; // distance hors écran
        const float speedValue = 150.f;
        Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

        switch (spawnSide)
        {
        case SpawnSide::Top:
            GetOwner()->SetPosition({Rand(0, window_size.x), -offset});
            velocity = Maths::Vector2f{ 100.f, speedValue };
            break;

        case SpawnSide::Bottom:
            GetOwner()->SetPosition({ Rand(0, window_size.x), window_size.y + offset });
            velocity = Maths::Vector2f{ 100.f, -speedValue };
            break;

        case SpawnSide::Left:
            GetOwner()->SetPosition({ -offset, Rand(0, window_size.y) });
            velocity = Maths::Vector2f{ speedValue, 100.f };
            break;

        case SpawnSide::Right:
            GetOwner()->SetPosition({ window_size.x + offset, Rand(0, window_size.y) });
            velocity = Maths::Vector2f{ -speedValue, 100.f };
            break;
        }
    }


    void Update(const float _delta_time) override
    {
        Maths::Vector2<float> position = GetOwner()->GetPosition();

        // Déplacement
        position.x += velocity.x * _delta_time;
        position.y += velocity.y * _delta_time;

        Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

        timer += _delta_time;

        if (timer > 1.f + (phase * 0.2f))
        {
            if (phase == 0)
                Patterns::ShootCircle(GetOwner());
            else if (phase == 1)
                Patterns::ShootSpiral(GetOwner());
            else if (phase == 2)
                Patterns::ShootWave(GetOwner());
            else
                Patterns::ShootLaser(GetOwner());

            timer = 0.f;
            phase = (phase + 1) % 4;
        }

        // Taille de l'objet 
        const float size = 20.f;

        if (position.x < 0.f) position.x = 0.f;
        if (position.x + size > window_size.x) position.x = window_size.x - size;

        if (position.y < 0.f) position.y = 0.f;
        if (position.y + size > window_size.y) position.y = window_size.y - size;

        if (position.x <= 0.f || position.x + size >= window_size.x)
        {
            velocity.x *= -1.f;
        }

        if (position.y <= 0.f || position.y + size >= window_size.y)
        {
            velocity.y *= -1.f;
        }

        GetOwner()->SetPosition(position);
    }

private:
    SpawnSide spawnSide;
    Maths::Vector2f velocity;

    float Rand(float min, float max)
    {
        return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
    }
};