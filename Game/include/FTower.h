#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "FProjectile.h"
#include <vector>
#include <cmath>
class FTowerDef;
class Tower : public Component
{
public:
    Tower(float range = 150.f, float fireRate = 1.f)
        : m_range(range), m_fireRate(fireRate)
    {
    }

    void Update(float dt) override
    {
        m_timer += dt;

        if (m_timer < m_fireRate)
            return;

        GameObject* target = FindTarget();

        if (target)
        {
            Shoot(target);
            m_timer = 0.f;
        }
    }


private:
    float m_range;
    float m_fireRate;
    float m_timer = 0.f;

    GameObject* FindTarget()
    {
        GameObject* owner = GetOwner();
        Maths::Vector2f pos = owner->GetPosition();

        const auto& objects = owner->GetScene()->GetGameObjects();

        for (const auto& objPtr : objects)
        {
            GameObject* obj = objPtr.get();

            if (!obj || obj->IsMarkedForDeletion())
                continue;

           
            if (obj->GetName().find("Enemy") == std::string::npos)
                continue;

            Maths::Vector2f dir = obj->GetPosition() - pos;
            float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

            if (dist <= m_range)
                return obj;
        }

        return nullptr;
    }

    void Shoot(GameObject* target)
    {
        GameObject* owner = GetOwner();

        GameObject* projectile = owner->GetScene()->CreateGameObject("Projectile");
        projectile->SetPosition(owner->GetPosition());

        auto* projComp = projectile->CreateComponent<Projectile>();
        projComp->SetTarget(target);
    }
};