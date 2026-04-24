#pragma once

#include "TowerDef/Tenemy.h"
#include "TowerDef/Map.h"
#include "TowerDef/TowerPlacer.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"

class TowerDefScene final : public Scene
{
public:
	TowerDefScene() : Scene("TowerDefScene")
	{
		// 1. Générer la map visuellement
		SpawnMap(this);

		roadPath = MapComponent::BuildRoadPath();

		GameObject* placer = CreateGameObject("TowerPlacer");
		placer->CreateComponent<TowerPlacer>();

		GameObject* enemy = CreateGameObject("Enemy");

		RectangleShapeRenderer* r = enemy->CreateComponent<RectangleShapeRenderer>();
		r->SetSize({ TILE_SIZE, TILE_SIZE });
		r->SetColor(sf::Color::Red);

		enemy->CreateComponent<EnemyMovement>(&roadPath);

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		
	}

private:
	std::vector<Maths::Vector2f> roadPath;
};

