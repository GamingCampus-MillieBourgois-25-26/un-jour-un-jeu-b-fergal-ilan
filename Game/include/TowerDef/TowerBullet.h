// TowerBullet.h
#pragma once
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Modules/WindowModule.h"
#include "TowerDef/Tenemy.h"
#include <cmath>

class TowerBullet : public Component
{
public:
    TowerBullet(const Maths::Vector2f& _direction, float _speed = 400.f)
        : direction(_direction), speed(_speed) {
    }

    void Update(float _dt) override
    {
        if (!alive) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += direction.x * speed * _dt;
        pos.y += direction.y * speed * _dt;
        GetOwner()->SetPosition(pos);

        // Hors ecran
        Maths::Vector2u win = Engine::GetInstance()->GetModuleManager()
            ->GetModule<WindowModule>()->GetSize();

        if (pos.x < 0.f || pos.x >(float)win.x ||
            pos.y < 0.f || pos.y >(float)win.y)
        {
            alive = false; // on note, on ne touche rien d'autre
            return;
        }

        // Verifier collision mais NE PAS appliquer pendant Update
        Scene* scene = GetOwner()->GetScene();
        if (!scene) return;

        for (const auto& go : scene->GetGameObjects())
        {
            if (go->GetName().rfind("Enemy_", 0) != 0) continue;
            if (go->IsMarkedForDeletion()) continue;

            EnemyMovement* em = go->GetComponent<EnemyMovement>();
            if (!em || em->IsDead()) continue;

            Maths::Vector2f ePos = go->GetPosition();
            float dx = GetOwner()->GetPosition().x - ePos.x;
            float dy = GetOwner()->GetPosition().y - ePos.y;

            constexpr float hitRadius = 14.f;
            if (dx * dx + dy * dy < hitRadius * hitRadius)
            {
                // On stocke la cible touchee, on applique dans Present()
                hitTarget = em;
                alive = false;
                return;
            }
        }
    }

    // Present() est appele apres tous les Updates -> safe
    void Present() override
    {
        if (hitTarget)
        {
            hitTarget->TakeDamage(1);
            hitTarget = nullptr;
            GetOwner()->MarkForDeletion();
        }
        else if (!alive)
        {
            GetOwner()->MarkForDeletion();
        }
    }

    bool IsAlive() const { return alive; }

private:
    Maths::Vector2f direction;
    float speed;
    bool alive = true;
    EnemyMovement* hitTarget = nullptr;
};