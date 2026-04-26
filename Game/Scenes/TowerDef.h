#pragma once
#include "TowerDef/Tenemy.h"
#include "TowerDef/Map.h"
#include "TowerDef/TowerPlacer.h"
#include "TowerDef/WaveManager.h"
#include "Core/Scene.h"

class TowerDefScene final : public Scene
{
public:
    TowerDefScene() : Scene("TowerDefScene")
    {
        // 1. Map visuelle
        SpawnMap(this);

        // 2. Chemin
        roadPath = MapComponent::BuildRoadPath();

        // 3. Placement de tours
        GameObject* placer = CreateGameObject("TowerPlacer");
        placer->CreateComponent<TowerPlacer>();

        // 4. Gestionnaire de vagues
        // waveCooldown = 10s, ou plus tôt si tous les ennemis sont morts
        GameObject* waveManagerGO = CreateGameObject("WaveManager");
        waveManagerGO->CreateComponent<WaveManager>(&roadPath, 10.f);
    }

private:
    std::vector<Maths::Vector2f> roadPath;
};
