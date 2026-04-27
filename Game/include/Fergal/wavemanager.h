#pragma once
#pragma once
#include "Core/Component.h"
#include "Fergal/EnemyWave.h"
#include "Fergal/FEnemyMovement.h"
#include <vector>
#include <algorithm>
#include <iostream>

class WaveManager : public Component
{
public:
    void Start() override
    {
        m_wave = EnemyWave(5, 0.5f);
    }

    void Update(float dt) override
    {
        m_wave.Update(dt);

        if (m_wave.CanSpawn())
        {
            SpawnEnemy();
            m_wave.ConsumeSpawn();
        }

        m_enemies.erase(
            std::remove_if(m_enemies.begin(), m_enemies.end(),
                [](GameObject* e)
                {
                    return e == nullptr || e->IsMarkedForDeletion();
                }),
            m_enemies.end()
        );

        if (m_wave.IsFinished() && m_enemies.empty())
        {
            NextWave();
        }
    }

private:
    EnemyWave m_wave;
    std::vector<GameObject*> m_enemies;
    int m_currentWave = 0;

    std::vector<Maths::Vector2f> path = {
        {0.f, 100.f},
        {300.f, 100.f},
        {300.f, 300.f},
        {600.f, 300.f}
    };

    void SpawnEnemy()
    {
        GameObject* enemy = GetOwner()->GetScene()->CreateGameObject("Enemy");

        enemy->SetPosition(path[0]);

        // AJOUT VISUEL
        auto* renderer = enemy->CreateComponent<RectangleShapeRenderer>();
        renderer->SetColor(sf::Color::Blue);
        renderer->SetSize(Maths::Vector2f(40.f, 40.f));

        auto* collider = enemy->CreateComponent<SquareCollider>();
        collider->SetWidth(10.f);
        collider->SetHeight(10.f);

        auto* move = enemy->CreateComponent<EnemyMovement>();
        move->SetPath(path);

        m_enemies.push_back(enemy);

        std::cout << "Spawn enemy\n";
    }

    void NextWave()
    {
        m_currentWave++;

        int enemyCount = 5 + m_currentWave * 2;
        m_wave.Reset(enemyCount);

        std::cout << "Next wave: " << m_currentWave << "\n";
    }
};