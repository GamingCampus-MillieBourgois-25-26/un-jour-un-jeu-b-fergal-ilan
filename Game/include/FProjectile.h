#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include <cmath>

class Projectile : public Component
{
public:
    void SetTarget(GameObject* target)
    {
        m_target = target;
    }

    void Update(float dt) override
    {
        if (!m_target)
        {
            GetOwner()->MarkForDeletion();
            return;
        }

        auto* owner = GetOwner();

        Maths::Vector2f pos = owner->GetPosition();
        Maths::Vector2f targetPos = m_target->GetPosition();

        Maths::Vector2f dir = targetPos - pos;

        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length < 5.f)
        {
            // impact
            m_target->MarkForDeletion();
            owner->MarkForDeletion();
            return;
        }

        dir = dir / length;

        owner->SetPosition(pos + dir * m_speed * dt);
    }


private:
    GameObject* m_target = nullptr;
    float m_speed = 300.f;
};