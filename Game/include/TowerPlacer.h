#pragma once
#include <unordered_set>
#include <string>
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include "Modules/SceneModule.h"
#include "Map.h"
#include "Tower.h"

class TowerPlacer : public Component
{
public:
    void Start() override
    {
        scene = Engine::GetInstance()->GetModuleManager()
            ->GetModule<SceneModule>()->GetSceneByName("TowerDefScene");
    }

    void Update(float _dt) override
    {
        if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
            return;

        const Maths::Vector2i mousePos = InputModule::GetMousePosition();
        const Maths::Vector2f worldPos = { (float)mousePos.x, (float)mousePos.y };

        // Tile cliquée
        const int col = static_cast<int>(worldPos.x / TILE_SIZE);
        const int row = static_cast<int>(worldPos.y / TILE_SIZE);

        if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS)
            return;

        if (MapComponent::GetTileAt(worldPos) != TileType::Buildable)
            return;

        // Clé unique pour éviter deux tours sur la même tile
        const std::string key = std::to_string(col) + "_" + std::to_string(row);
        if (occupiedTiles.count(key))
            return;

        occupiedTiles.insert(key);

        // Spawner la tour au centre de la tile
        const Maths::Vector2f center = MapComponent::TileCenter(col, row);

        static int towerId = 0;
        GameObject* towerGO = scene->CreateGameObject("Tower_" + std::to_string(towerId++));
        towerGO->SetPosition(center);

        RectangleShapeRenderer* r = towerGO->CreateComponent<RectangleShapeRenderer>();
        r->SetColor(sf::Color::Cyan);
        r->SetSize({ TILE_SIZE, TILE_SIZE });

        towerGO->CreateComponent<Tower>(100.f, 1.f); // rayon 100px, 1 tir/sec
    }

private:
    Scene* scene = nullptr;
    std::unordered_set<std::string> occupiedTiles;
};