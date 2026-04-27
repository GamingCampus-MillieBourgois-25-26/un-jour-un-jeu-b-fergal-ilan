#pragma once
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "clicker.h"
#include "BoardResolver.h"
#include "ScoreDisplayComponent.h"

class Match3 final : public Scene
{
public:
    static const int WIDTH = 8;
    static const int HEIGHT = 8;
    static const int TILE_SIZE = 50;

    int         score = 0;  // score du match3
    int         grid[HEIGHT][WIDTH];
    GameObject* tiles[HEIGHT][WIDTH];
    BoardResolver* resolver = nullptr;

    int selectedCol = -1;
    int selectedRow = -1;

    Match3() : Scene("Match3Scene")
    {
        srand(static_cast<unsigned int>(time(NULL)));
        InitGrid();

        // Affichage du score en haut a gauche
        GameObject* scoreGO = CreateGameObject("ScoreText");
        scoreGO->SetPosition({ 10.f, 10.f });
        TextRenderer* txt = scoreGO->CreateComponent<TextRenderer>("Score : 0");
        txt->SetColor(sf::Color::White);
        scoreGO->CreateComponent<ScoreDisplayComponent>(&score);

        // Tiles fixes
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                GameObject* tile = CreateGameObject(
                    "Tile_" + std::to_string(x) + "_" + std::to_string(y));

                tile->SetPosition({
                    (float)(x * TILE_SIZE + 50), // +50 pour laisser place au texte
                    (float)(y * TILE_SIZE + 50)
                    });

                SquareCollider* col = tile->CreateComponent<SquareCollider>();
                col->SetWidth(40.f);
                col->SetHeight(40.f);

                RectangleShapeRenderer* r = tile->CreateComponent<RectangleShapeRenderer>();
                r->SetColor(GetColorFromType(grid[y][x]));
                r->SetSize({ 40.f, 40.f });

                ClickableComponent* clickable = tile->CreateComponent<ClickableComponent>();
                clickable->gridX = x;
                clickable->gridY = y;
                clickable->onClick = [this](int col, int row)
                    {
                        OnTileClicked(col, row);
                    };

                tiles[y][x] = tile;
            }
        }

        // BoardResolver
        GameObject* resolverGO = CreateGameObject("BoardResolver");
        resolver = resolverGO->CreateComponent<BoardResolver>();
        resolver->grid = grid;
        resolver->tiles = tiles;
        resolver->width = WIDTH;
        resolver->height = HEIGHT;
        resolver->score = &score; // brancher le score
    }

    void OnTileClicked(int col, int row)
    {
        if (resolver && resolver->IsResolving()) return;

        // Rien de selectionne encore
        if (selectedCol == -1)
        {
            selectedCol = col;
            selectedRow = row;
            // Highlight
            tiles[row][col]->GetComponent<RectangleShapeRenderer>()
                ->SetColor(sf::Color::White);
            return;
        }

        // Restaurer couleur de la selection precedente
        tiles[selectedRow][selectedCol]->GetComponent<RectangleShapeRenderer>()
            ->SetColor(GetColorFromType(grid[selectedRow][selectedCol]));

        // Verifier adjacence
        int dx = abs(col - selectedCol);
        int dy = abs(row - selectedRow);
        bool adjacent = (dx + dy == 1);

        if (adjacent)
        {
            // Swap uniquement dans grid, pas de mouvement de GameObject
            std::swap(grid[selectedRow][selectedCol], grid[row][col]);
            UpdateVisuals();

            if (!resolver->HasMatch())
            {
                // Revert
                std::swap(grid[selectedRow][selectedCol], grid[row][col]);
                UpdateVisuals();
            }
            else
            {
                resolver->StartResolve();
            }
        }

        selectedCol = -1;
        selectedRow = -1;
    }

private:
    sf::Color GetColorFromType(int type)
    {
        switch (type)
        {
        case 0:   return sf::Color::Red;
        case 1:   return sf::Color::Green;
        case 2:   return sf::Color::Blue;
        case 3:   return sf::Color::Yellow;
        case 4:   return sf::Color::Magenta;
        case 100: return sf::Color::Cyan;
        case 200: return sf::Color::White;
        default:  return { 50, 50, 50 };
        }
    }

    void InitGrid()
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int val;
                do {
                    val = rand() % 5;
                } while (
                    (x >= 2 && grid[y][x - 1] == val && grid[y][x - 2] == val) ||
                    (y >= 2 && grid[y - 1][x] == val && grid[y - 2][x] == val)
                    );
                grid[y][x] = val;
            }
        }
    }

    void UpdateVisuals()
    {
        for (int y = 0; y < HEIGHT; y++)
            for (int x = 0; x < WIDTH; x++)
            {
                auto* r = tiles[y][x]->GetComponent<RectangleShapeRenderer>();
                if (r) r->SetColor(GetColorFromType(grid[y][x]));
            }
    }
};