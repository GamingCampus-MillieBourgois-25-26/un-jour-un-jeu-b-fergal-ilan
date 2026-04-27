#pragma once

#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
class Match3 final : public Scene
{
public:
	static const int WIDTH = 8;
	static const int HEIGHT = 8;

	int grid[HEIGHT][WIDTH];
	GameObject* tiles[HEIGHT][WIDTH];
	Match3() : Scene("Match3Scene")
	{
		

		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				grid[y][x] = rand() % 5; // 5 types de gemmes

				GameObject* tile = CreateDummyGameObject(
					"Tile",
					0.f,
					GetColorFromType(grid[y][x])
				);

				tile->SetPosition(Maths::Vector2f(x * 50.f, y * 50.f));
				tiles[y][x] = tile;
			}
		}

		GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Cyan);

		GameObject* enemy = CreateDummyGameObject("Enemy", 100.f, sf::Color::Blue);

		/*GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Yellow);*/

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		/*Texture* texture = assets_module->LoadAsset<Texture>("logo.png");

		player->CreateComponent<SpriteRenderer>(texture);*/
	}
	sf::Color GetColorFromType(int type)
	{
		switch (type)
		{
		case 0: return sf::Color::Red;
		case 1: return sf::Color::Green;
		case 2: return sf::Color::Blue;
		case 3: return sf::Color::Yellow;
		case 4: return sf::Color::Magenta;
		default: return sf::Color::White;
		}
	}
	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, _position));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(10.f);
		square_collider->SetHeight(10.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(40.f, 40.f));

		return game_object;
	}
};