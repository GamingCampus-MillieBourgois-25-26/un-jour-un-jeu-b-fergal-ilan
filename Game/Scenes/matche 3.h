#pragma once

#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "clicker.h"
class Match3 final : public Scene
{
public:
	static const int WIDTH = 8;
	static const int HEIGHT = 8;
	GameObject* firstSelected = nullptr;

	int grid[HEIGHT][WIDTH];
	GameObject* tiles[HEIGHT][WIDTH];
	Match3() : Scene("Match3Scene")
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				grid[y][x] = rand() % 5;

				GameObject* tile = CreateDummyGameObject(
					"Tile",
					0.f,
					GetColorFromType(grid[y][x])
				);

				tile->SetPosition(Maths::Vector2f(x * 50.f, y * 50.f));
				tiles[y][x] = tile;

				ClickableComponent* clickable = tile->CreateComponent<ClickableComponent>();

				clickable->gridX = x;
				clickable->gridY = y;

				clickable->onClick = [this](GameObject* clicked)
					{
						OnTileClicked(clicked);
					};
			}
		}
	}
	ClickableComponent* GetClickable(GameObject* obj)
	{
		return obj->GetComponent<ClickableComponent>();
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
	void SwapTiles(GameObject* a, GameObject* b)
	{
		auto ca = GetClickable(a);
		auto cb = GetClickable(b);

		int x1 = ca->gridX;
		int y1 = ca->gridY;

		int x2 = cb->gridX;
		int y2 = cb->gridY;

		// swap logique
		std::swap(grid[y1][x1], grid[y2][x2]);
		std::swap(tiles[y1][x1], tiles[y2][x2]);

		// swap coordonnées
		std::swap(ca->gridX, cb->gridX);
		std::swap(ca->gridY, cb->gridY);

		// swap positions visuelles
		auto posA = a->GetPosition();
		auto posB = b->GetPosition();

		a->SetPosition(posB);
		b->SetPosition(posA);
	}
	bool AreAdjacent(GameObject* a, GameObject* b)
	{
		auto ca = GetClickable(a);
		auto cb = GetClickable(b);

		int dx = abs(ca->gridX - cb->gridX);
		int dy = abs(ca->gridY - cb->gridY);

		return (dx + dy == 1);
	}
	void OnTileClicked(GameObject* tile)
	{
		if (!firstSelected)
		{
			firstSelected = tile;
			return;
		}

		if (AreAdjacent(firstSelected, tile))
		{
			SwapTiles(firstSelected, tile);
		}

		firstSelected = nullptr;
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