#pragma once
#include <vector>
#include "Bullet.h"
#include "Core/Scene.h"

class BulletPool
{
public:
    std::vector<Bullet*> bullets;

    Bullet* GetBullet()
    {
        for (auto* b : bullets)
        {
            if (!b->active)
                return b;
        }
        return nullptr;
    }

    void Init(Scene* scene, int count);
};

extern BulletPool gBulletPool;