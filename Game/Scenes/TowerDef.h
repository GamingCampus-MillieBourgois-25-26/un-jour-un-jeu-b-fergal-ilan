#pragma once

#include "Tenemy.h"
#include "Player.h"
#include "Map.h"
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

		GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Red);
		player->CreateComponent<Player>();

		GameObject* enemy = CreateGameObject("Enemy");

		RectangleShapeRenderer* r = enemy->CreateComponent<RectangleShapeRenderer>();
		r->SetSize({ TILE_SIZE, TILE_SIZE });
		r->SetColor(sf::Color::Red);

		enemy->CreateComponent<EnemyMovement>(&roadPath);

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		
	}

	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, _position));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(20.f);
		square_collider->SetHeight(20.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(50.f, 50.f));

		return game_object;
	}

private:
	std::vector<Maths::Vector2f> roadPath;
};

