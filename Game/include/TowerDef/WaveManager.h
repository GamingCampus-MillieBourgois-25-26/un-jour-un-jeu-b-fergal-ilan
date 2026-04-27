// TowerDef/WaveManager.h
#pragma once
#include <vector>
#include <string>
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/SceneModule.h"
#include "TowerDef/Tenemy.h"
#include <iostream>

class WaveManager : public Component
{
public:
    WaveManager(std::vector<Maths::Vector2f>* _path, float _waveCooldown = 10.f)
        : path(_path), waveCooldown(_waveCooldown) {
    }

    void Start() override
    {
        scene = Engine::GetInstance()->GetModuleManager()
            ->GetModule<SceneModule>()->GetSceneByName("TowerDefScene");

        SpawnWave();
    }

    void Update(float _dt) override
    {
        if (!scene) return;

        int aliveCount = CountAliveEnemies();
        waveTimer += _dt;

        bool timerDone = waveTimer >= waveCooldown;
        bool allDead = (aliveCount == 0 && waveSpawned);

        if (timerDone || allDead)
        {
            waveTimer = 0.f;
            currentWave++;
            pendingSpawn = true; // on note qu'il faut spawner, mais pas maintenant
        }
    }

    void Present() override
    {
        if (pendingSpawn)
        {
            pendingSpawn = false;
            SpawnWave();
        }
    }

    // Ajouter dans les membres prives :
    bool pendingSpawn = false;

    int GetCurrentWave() const { return currentWave; }

private:
    std::vector<Maths::Vector2f>* path = nullptr;
    Scene* scene = nullptr;

    int currentWave = 0;
    float waveCooldown;
    float waveTimer = 0.f;
    bool waveSpawned = false;

    static int enemyId;

    int EnemyCountForWave(int _wave) const
    {
        return 3 + (_wave - 1) * 2;
    }

    // Calcule la position de depart decalee pour l'ennemi _index
    Maths::Vector2f OffsetStart(int _index) const
    {
        if (!path || path->empty()) return { 0.f, 0.f };

        Maths::Vector2f start = (*path)[0];
        start.x -= static_cast<float>(_index) * 25.f;
        return start;
    }

    void SpawnWave()
    {
        if (!scene) return;

        int count = EnemyCountForWave(currentWave);
        std::cout << "=== Vague " << currentWave << " - " << count << " ennemis ===\n";

        for (int i = 0; i < count; i++)
        {
            GameObject* enemy = scene->CreateGameObject("Enemy_" + std::to_string(enemyId++));

            RectangleShapeRenderer* r = enemy->CreateComponent<RectangleShapeRenderer>();
            r->SetSize({ 20.f, 20.f });
            r->SetColor(sf::Color::Red);

            enemy->CreateComponent<EnemyMovement>(path, 3);

            // Espacer les ennemis au depart
            enemy->SetPosition(OffsetStart(i));
        }

        waveSpawned = true;
    }

    int CountAliveEnemies() const
    {
        int count = 0;
        for (const auto& go : scene->GetGameObjects())
        {
            if (go->GetName().rfind("Enemy_", 0) != 0) continue;
            EnemyMovement* em = go->GetComponent<EnemyMovement>();
            if (em && !em->IsDead())
                count++;
        }
        return count;
    }
};

inline int WaveManager::enemyId = 0;