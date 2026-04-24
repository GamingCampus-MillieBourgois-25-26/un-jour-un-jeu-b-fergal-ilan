#include "BulletPool.h"

#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"

BulletPool gBulletPool;

void BulletPool::Init(Scene* scene, int count)
{
    for (int i = 0; i < count; i++)
    {
        GameObject* obj = scene->CreateGameObject("Bullet");

        auto b = obj->CreateComponent<Bullet>();

        b->active = false;

        obj->SetPosition({ -1000.f, -1000.f });

        bullets.push_back(b);
    }
}