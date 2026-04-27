#pragma once
#include <vector>
#include "Bullet.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
class FBulletPool
{
public:
    std::vector<FBullet*> bullets;

    void Init(Scene* scene, int count)
    {
        for (int i = 0; i < count; i++)
        {
            GameObject* obj = scene->CreateGameObject("Bullet");

            auto b = obj->CreateComponent<FBullet>();

            //AJOUT VISUEL (IMPORTANT)
            auto renderer = obj->CreateComponent<RectangleShapeRenderer>();
            renderer->SetSize(Maths::Vector2f(5.f, 5.f));
            renderer->SetColor(sf::Color::Red);

            b->active = false;
            obj->SetPosition(Maths::Vector2f(-1000.f, -1000.f));

            bullets.push_back(b);
        }
    }

    FBullet* GetBullet()
    {
        for (auto b : bullets)
        {
            if (!b->active)
                return b;
        }

        return nullptr; // pool plein
    }
};

extern FBulletPool gBulletPool;