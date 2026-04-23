#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"

class EnemyWave
{
public:
    EnemyWave(int enemyCount = 5, float spawnDelay = 0.5f)
        : m_enemyCount(enemyCount), m_spawnDelay(spawnDelay)
    {
    }

    void Reset(int enemyCount)
    {
        m_enemyCount = enemyCount;
        m_spawned = 0;
        m_timer = 0.f;
        m_finished = false;
    }

    void Update(float dt)
    {
        if (m_finished)
            return;

        m_timer += dt;

        if (m_timer >= m_spawnDelay)
        {
            m_timer = 0.f;
            m_spawned++;
        }

        if (m_spawned >= m_enemyCount)
        {
            m_finished = true;
        }
    }

    bool CanSpawn() const
    {
        return !m_finished && m_timer == 0.f && m_spawned < m_enemyCount;
    }

    bool IsFinished() const
    {
        return m_finished;
    }

    void OnEnemySpawned()
    {
        m_spawned++;
    }

    int GetRemaining() const
    {
        return m_enemyCount - m_spawned;
    }

private:
    int m_enemyCount = 0;
    int m_spawned = 0;

    float m_spawnDelay = 0.5f;
    float m_timer = 0.f;

    bool m_finished = false;
};