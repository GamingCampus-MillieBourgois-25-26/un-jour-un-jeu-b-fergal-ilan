#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"

class EnemyWave
{
public:
    EnemyWave(int count = 5, float delay = 0.5f)
        : m_enemyCount(count), m_spawnDelay(delay)
    {
    }

    void Reset(int count)
    {
        m_enemyCount = count;
        m_spawned = 0;
        m_timer = 0.f;
        m_finished = false;
    }

    void Update(float dt)
    {
        
        if (m_finished)
            return;

        m_timer += dt;
    }

    bool CanSpawn() const
    {
        return !m_finished &&
            m_spawned < m_enemyCount &&
            m_timer >= m_spawnDelay;
    }

    void ConsumeSpawn()
    {
        m_timer -= m_spawnDelay; // IMPORTANT (pas reset)
        m_spawned++;

        if (m_spawned >= m_enemyCount)
            m_finished = true;
    }

    bool IsFinished() const
    {
        return m_finished;
    }

private:
    int m_enemyCount = 0;
    int m_spawned = 0;

    float m_spawnDelay = 0.5f;
    float m_timer = 0.f;

    bool m_finished = false;
};