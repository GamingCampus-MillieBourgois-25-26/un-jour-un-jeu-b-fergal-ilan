#pragma once
#include "FPlayer.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "FClickableComponent.h"

class FClick final : public Scene
{
public:
	int score = 0;
	int clickPower = 1;
	int upgradeCost = 10;
	FClick() : Scene("FClickScene")
	{
		/*GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Cyan);
		player->CreateComponent<FPlayer>();*/

		GameObject* enemy = CreateDummyGameObject("Enemy", 250.f, sf::Color::Blue);
		enemy->CreateComponent<ClickableComponent>(&score);

		/*GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Yellow);*/

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		/*Texture* texture = assets_module->LoadAsset<Texture>("logo.png");

		player->CreateComponent<SpriteRenderer>(texture);*/
	}
	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, 250.f));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(40.f);
		square_collider->SetHeight(40.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(40.f, 40.f));

		return game_object;
	}
};