
#pragma once
#include "Core/Component.h"
#include "BulletH/Player.h"
#include "Core/Scene.h"      
#include "Core/GameObject.h" 
#include <cmath>

class Bullet : public Component
{
public:
    Maths::Vector2f velocity;
    bool active = false;

    void Activate(const Maths::Vector2f& _pos, const Maths::Vector2f& _vel)
    {
        active = true;
        velocity = _vel;
        GetOwner()->SetPosition(_pos);
        GetOwner()->Enable();
    }

    void Deactivate()
    {
        active = false;
        GetOwner()->SetPosition({ -2000.f, -2000.f });
        GetOwner()->Disable(); 
    }

    void Update(float _dt) override
    {
        if (!active) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += velocity.x * _dt;
        pos.y += velocity.y * _dt;
        GetOwner()->SetPosition(pos);

        // Collision player via GetScene() qui existe maintenant
        Scene* scene = GetOwner()->GetScene();
        if (!scene) return;

        for (const auto& go : scene->GetGameObjects())
        {
            if (go->GetName() != "Player") continue;

            Player* p = go->GetComponent<Player>();
            if (!p) continue;

            Maths::Vector2f diff = pos - p->GetPosition();
            float dist2 = diff.x * diff.x + diff.y * diff.y;
            constexpr float r = 15.f + 3.f;

            if (dist2 < r * r)
            {
                p->TakeDamage();
                Deactivate();
                return;
            }
        }

        // Hors écran
        if (pos.x < -50.f || pos.x > 650.f || pos.y < -50.f || pos.y > 650.f)
            Deactivate();
    }
};