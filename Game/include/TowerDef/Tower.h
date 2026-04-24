#pragma once
#include <cmath>
#include <vector>
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/SceneModule.h"
#include "TowerBullet.h"

class Tower : public Component
{
public:
    Tower(float _range = 100.f, float _fireRate = 1.f)
        : range(_range), fireRate(_fireRate) {
    }

    void Start() override
    {
        scene = Engine::GetInstance()->GetModuleManager()
            ->GetModule<SceneModule>()->GetSceneByName("TowerDefScene");
    }

    void Update(float _dt) override
    {
        fireTimer += _dt;
        if (fireTimer >= fireRate)
        {
            fireTimer = 0.f;
            TryShoot();
        }

        CleanDeadBullets();
    }

private:
    float range;
    float fireRate;
    float fireTimer = 0.f;

    Scene* scene = nullptr;
    std::vector<GameObject*> bullets;

    static int bulletId;

    GameObject* FindClosestEnemy()
    {
        if (!scene) return nullptr;

        const Maths::Vector2f origin = GetOwner()->GetPosition();
        GameObject* closest = nullptr;
        float closestDist = range;

        for (const auto& go : scene->GetGameObjects())
        {
            // On identifie les ennemis par leur nom (préfixe "Enemy")
            if (go->GetName().rfind("Enemy", 0) != 0)
                continue;

            const Maths::Vector2f ePos = go->GetPosition();
            const float dx = ePos.x - origin.x;
            const float dy = ePos.y - origin.y;
            const float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < closestDist)
            {
                closestDist = dist;
                closest = go.get();
            }
        }

        return closest;
    }

    void TryShoot()
    {
        GameObject* target = FindClosestEnemy();
        if (!target) return;

        const Maths::Vector2f origin = GetOwner()->GetPosition();
        const Maths::Vector2f ePos = target->GetPosition();

        float dx = ePos.x - origin.x;
        float dy = ePos.y - origin.y;
        const float len = std::sqrt(dx * dx + dy * dy);
        if (len == 0.f) return;
        dx /= len;
        dy /= len;

        GameObject* bulletGO = scene->CreateGameObject("TowerBullet_" + std::to_string(bulletId++));
        bulletGO->SetPosition(origin);

        RectangleShapeRenderer* r = bulletGO->CreateComponent<RectangleShapeRenderer>();
        r->SetColor(sf::Color::White);
        r->SetSize({ 5.f, 5.f });

        bulletGO->CreateComponent<TowerBullet>(Maths::Vector2f{ dx, dy }, 400.f);

        bullets.push_back(bulletGO);
    }

    void CleanDeadBullets()
    {
        if (!scene) return;

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [this](GameObject* go)
                {
                    TowerBullet* b = go->GetComponent<TowerBullet>();
                    if (b && !b->IsAlive())
                    {
                        scene->DestroyGameObject(go);
                        return true;
                    }
                    return false;
                }),
            bullets.end()
        );
    }
};

inline int Tower::bulletId = 0;