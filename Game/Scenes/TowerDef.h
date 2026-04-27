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
        SpawnMap(this);

        roadPath = MapComponent::BuildRoadPath();

        GameObject* placer = CreateGameObject("TowerPlacer");
        placer->CreateComponent<TowerPlacer>();

        GameObject* waveManagerGO = CreateGameObject("WaveManager");
        waveManagerGO->CreateComponent<WaveMan>(&roadPath, 10.f);
    }

private:
    std::vector<Maths::Vector2f> roadPath;
};
