#pragma once
#include "Core/Component.h"
#include "Modules/WindowModule.h"
#include "Maths/Vector2.h"

class TowerBullet : public Component
{
public:
    TowerBullet(const Maths::Vector2f& _direction, float _speed = 400.f)
        : direction(_direction), speed(_speed) {
    }

    void Update(float _dt) override
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += direction.x * speed * _dt;
        pos.y += direction.y * speed * _dt;
        GetOwner()->SetPosition(pos);

        Maths::Vector2u win = Engine::GetInstance()->GetModuleManager()
            ->GetModule<WindowModule>()->GetSize();

        if (pos.x < 0.f || pos.x > win.x || pos.y < 0.f || pos.y > win.y)
        {
            GetOwner()->MarkForDeletion();
            alive = false;
        }
    }

    bool IsAlive() const { return alive; }

private:
    Maths::Vector2f direction;
    float speed;
    bool alive = true;
};