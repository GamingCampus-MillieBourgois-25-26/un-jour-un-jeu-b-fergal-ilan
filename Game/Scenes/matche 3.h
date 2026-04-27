#pragma once

#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/TextRenderer.h"
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
		case 100: return sf::Color::Cyan; // not sure
		case 200: return sf::Color::White;// not sure
		default: return sf::Color::White;
		}
	}
	/*void ResolveBoard()
	{
		bool again = true;

		while (again)
		{
			again = HasMatch();

			if (again)
			{
				RemoveMatches();
				ApplyGravity();
				UpdateVisuals();
			}
		}
	}*/
	void SwapTiles(GameObject* a, GameObject* b)
	{
		auto ca = GetClickable(a);
		auto cb = GetClickable(b);

		int x1 = ca->gridX;
		int y1 = ca->gridY;

		int x2 = cb->gridX;
		int y2 = cb->gridY;

		// swap GRID ONLY
		std::swap(grid[y1][x1], grid[y2][x2]);

		// swap positions logiques
		std::swap(ca->gridX, cb->gridX);
		std::swap(ca->gridY, cb->gridY);

		// swap visual
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
	bool HasMatch()
	{
		// horizontal
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH - 2; x++)
			{
				int v = grid[y][x];
				if (v == grid[y][x + 1] && v == grid[y][x + 2])
					return true;
			}
		}

		// vertical
		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = 0; y < HEIGHT - 2; y++)
			{
				int v = grid[y][x];
				if (v == grid[y + 1][x] && v == grid[y + 2][x])
					return true;
			}
		}
		UpdateVisuals();
		return false;
	}
	void HandleMatch(int y, int x, int count, bool horizontal)
	{
		if (count < 3)
			return;

		// supprimer
		for (int i = 0; i < count; i++)
		{
			if (horizontal)
				grid[y][x + i] = -1;
			else
				grid[y + i][x] = -1;
		}

		// BONUS
		if (count == 4)
		{
			// bonus ligne
			if (horizontal)
				grid[y][x] = 100;
			else
				grid[y][x] = 100;
		}
		else if (count >= 5)
		{
			// super bonus
			if (horizontal)
				grid[y][x] = 200;
			else
				grid[y][x] = 200;
		}
		UpdateVisuals();
	}
	void RemoveMatches()
	{
		// horizontal
		for (int y = 0; y < HEIGHT; y++)
		{
			int count = 1;

			for (int x = 1; x < WIDTH; x++)
			{
				if (grid[y][x] == grid[y][x - 1])
				{
					count++;
				}
				else
				{
					HandleMatch(y, x - count, count, true);
					count = 1;
				}
			}

			HandleMatch(y, WIDTH - count, count, true);
		}

		// vertical
		for (int x = 0; x < WIDTH; x++)
		{
			int count = 1;

			for (int y = 1; y < HEIGHT; y++)
			{
				if (grid[y][x] == grid[y - 1][x])
				{
					count++;
				}
				else
				{
					HandleMatch(y - count, x, count, false);
					count = 1;
				}
			}

			HandleMatch(HEIGHT - count, x, count, false);
		}
		UpdateVisuals();
	}
	void ApplyGravity()
	{
		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = HEIGHT - 1; y >= 0; y--)
			{
				if (grid[y][x] == -1)
				{
					for (int k = y; k > 0; k--)
					{
						std::swap(grid[k][x], grid[k - 1][x]);
					}

					grid[0][x] = rand() % 5;
				}
			}
		}
	}
	void RebuildGridReferences()
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				auto c = GetClickable(tiles[y][x]);
				c->gridX = x;
				c->gridY = y;
			}
		}
	}
	void ResolveBoard()
	{
		bool again = true;

		while (again)
		{
			again = HasMatch();

			if (again)
			{
				RemoveMatches();
				ApplyGravity();

				RebuildGridReferences(); // IMPORTANT FIX

				UpdateVisuals();
			}
		}
	}
	void UpdateVisuals()
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				auto renderer = tiles[y][x]->GetComponent<RectangleShapeRenderer>();
				renderer->SetColor(GetColorFromType(grid[y][x]));
			}
		}
	}
	void ApplyBonus(int x, int y, int type)
	{
		if (type == 100)
		{
			// explosion ligne
			for (int i = 0; i < WIDTH; i++)
				grid[y][i] = -1;
		}
		else if (type == 200)
		{
			// explosion colonne + ligne (cross)
			for (int i = 0; i < WIDTH; i++)
				grid[y][i] = -1;

			for (int i = 0; i < HEIGHT; i++)
				grid[i][x] = -1;
		}
	}
	void OnTileClicked(GameObject* tile)
	{
		auto renderer = tile->GetComponent<RectangleShapeRenderer>();

		if (!firstSelected)
		{
			firstSelected = tile;

			// highlight
			renderer->SetColor(sf::Color::White);
			return;
		}

		// remettre la bonne couleur à la première case
		auto firstRenderer = firstSelected->GetComponent<RectangleShapeRenderer>();

		auto firstClickable = GetClickable(firstSelected);
		int type = grid[firstClickable->gridY][firstClickable->gridX];

		firstRenderer->SetColor(GetColorFromType(type));

		if (AreAdjacent(firstSelected, tile))
		{
			SwapTiles(firstSelected, tile);

			if (!HasMatch())
			{
				// revert
				SwapTiles(firstSelected, tile);
			}
			else
			{
				RemoveMatches();
				ApplyGravity();
				UpdateVisuals();
			}
		}

		firstSelected = nullptr;
		UpdateVisuals();
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