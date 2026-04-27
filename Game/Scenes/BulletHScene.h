#pragma once

#include "BulletH/Bullet.h"
#include "BulletH/BulletPool.h"
#include "BulletH/Player.h"
#include "BulletH/Enemy.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"


class Bullet;
class Enemy;
class BulletHScene final : public Scene
{
public:
	BulletHScene() : Scene("BulletHScene")
	{
		hBulletPool.Init(this, 1000);
		GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Red);
		player->CreateComponent<Player>();

		srand(time(NULL));
		SpawnSide side = static_cast<SpawnSide>(rand() % 4);
		GameObject* enemy = CreateDummyGameObject("Enemy", 400.f, sf::Color::Blue);
		enemy->CreateComponent<Enemy>(side);

		side = static_cast<SpawnSide>(rand() % 4);
		GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);
		enemy2->CreateComponent<Enemy>(side);

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	}

	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, _position));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(200.f);
		square_collider->SetHeight(200.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(20.f, 20.f));

		return game_object;
	}
};
