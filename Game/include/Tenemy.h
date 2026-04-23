#pragma once
#include "InputModule.h"

#include <vector>
#include <cmath>

#include "Component.h"
#include "GameObject.h"

class EnemyMovement : public Component
{
public:
    EnemyMovement(std::vector<Maths::Vector2f>* path)
        : path(path) {
    }

    void Start() override
    {
        currentPoint = 0;

        if (path && !path->empty())
        {
            GetOwner()->SetPosition((*path)[0]);
        }
    }

    void Update(float dt) override
    {
        if (!path || currentPoint >= path->size())
            return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Maths::Vector2f target = (*path)[currentPoint];

        Maths::Vector2f dir = target - pos;

        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        // Si on est proche du point → passer au suivant
        if (length < 5.f)
        {
            currentPoint++;
            return;
        }

        // Normalisation
        dir.x /= length;
        dir.y /= length;

        // Déplacement
        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;

        GetOwner()->SetPosition(pos);
    }

private:
    std::vector<Maths::Vector2f>* path = nullptr;
    size_t currentPoint = 0;
    float speed = 100.f;
};