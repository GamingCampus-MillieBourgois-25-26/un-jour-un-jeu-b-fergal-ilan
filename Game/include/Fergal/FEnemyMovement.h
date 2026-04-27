#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include <cmath>
#include <vector>

class EnemyMovement : public Component
{
public:
    EnemyMovement(float speed = 100.f)
        : m_speed(speed)
    {
    }
    void SetPath(const std::vector<Maths::Vector2f>& path)
    {
        m_path = path;
        m_currentIndex = 0;
    }

    void Update(float dt) override
    {
        if (m_path.empty() || m_currentIndex >= m_path.size())
            return;

        GameObject* owner = GetOwner();

        Maths::Vector2f currentPos = owner->GetPosition();
        Maths::Vector2f target = m_path[m_currentIndex];

        Maths::Vector2f direction = target - currentPos;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length < 5.f)
        {
            m_currentIndex++;
            return;
        }

        direction = direction / length;

        owner->SetPosition(currentPos + direction * m_speed * dt);
    }

private:
    std::vector<Maths::Vector2f> m_path;
    size_t m_currentIndex = 0;
    float m_speed;
};