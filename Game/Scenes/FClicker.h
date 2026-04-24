#pragma once
#include "FPlayer.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/TextRenderer.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include <SFML/Graphics.hpp>
#include "FClickableComponent.h"
#include "ShopComponent.h"
#include "FScoreDisplayComponent.h"

class FClick final : public Scene
{
public:
	int score = 0;
	int clickPower = 1;
	int upgradeCost = 10;
	

	FClick() : Scene("FClickScene")
	{
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* shopass = assets_module->LoadAsset<Texture>("fergal/clicker/shop.png");

		/*GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Cyan);
		player->CreateComponent<FPlayer>();*/
		// text
		GameObject* terxt = CreateGameObject("score");

		TextRenderer* text = terxt->CreateComponent<TextRenderer>("score : 0");
		text->SetColor(sf::Color::White);

		//  AJOUT IMPORTANT
		terxt->CreateComponent<ScoreDisplayComponent>(&score);
		/*GameObject* terxt = CreateGameObject("score");
		TextRenderer* text = terxt->CreateComponent<TextRenderer>("score : ");
		text->SetColor(sf::Color::White);*/
		GameObject* enemy = CreateDummyGameObject("Enemy", 250.f, sf::Color::Blue);
		enemy->CreateComponent<ClickableComponent>(&score, &clickPower);

		GameObject* shop = CreateDummyGameObject("Shop", 400.f, sf::Color::Green);
		shop->CreateComponent<ShopComponent>(&score, &clickPower, &upgradeCost);
		shop->CreateComponent<SpriteRenderer>(shopass);
		
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
		//shape_renderer->SetPivot({ 32.f, 32.f }); // centre

		return game_object;
	}
};