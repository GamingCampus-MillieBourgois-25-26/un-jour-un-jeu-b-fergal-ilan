// Match3/BoardResolver.h
#pragma once
#include "Core/Component.h"
#include "Components/RectangleShapeRenderer.h"
#include <functional>
#include <vector>

// Etats de la resolution
enum class ResolveState
{
    Idle,
    FlashMatches,   // faire clignoter les cases matchees
    RemoveMatches,  // supprimer et appliquer la gravite
    ApplyGravity,
    UpdateVisuals,
    CheckAgain,     // verifier si nouveaux matchs
};

class BoardResolver : public Component
{
public:
    // Pointeurs vers les donnees de la scene
    int (*grid)[8] = nullptr;
    GameObject* (*tiles)[8] = nullptr;
    int width = 8;
    int height = 8;

    // Callback appelee quand tout est resolu
    std::function<void()> onResolveDone;

    // Lance la resolution
    void StartResolve()
    {
        if (state != ResolveState::Idle) return;
        state = ResolveState::FlashMatches;
        stateTimer = 0.f;
        flashOn = true;
    }

    bool IsResolving() const { return state != ResolveState::Idle; }

    void Update(float _dt) override
    {
        switch (state)
        {
        case ResolveState::Idle: break;

        case ResolveState::FlashMatches:
            stateTimer += _dt;
            // Clignotement : alterner blanc/couleur toutes les 0.1s
            if (stateTimer < 0.4f)
            {
                bool newFlash = (static_cast<int>(stateTimer / 0.1f) % 2 == 0);
                if (newFlash != flashOn)
                {
                    flashOn = newFlash;
                    HighlightMatches(flashOn);
                }
            }
            else
            {
                // Fin du flash -> supprimer
                state = ResolveState::RemoveMatches;
                stateTimer = 0.f;
            }
            break;

        case ResolveState::RemoveMatches:
            DoRemoveMatches();
            state = ResolveState::ApplyGravity;
            stateTimer = 0.f;
            break;

        case ResolveState::ApplyGravity:
            // Petite pause visuelle avant la gravite
            stateTimer += _dt;
            if (stateTimer >= 0.15f)
            {
                DoApplyGravity();
                state = ResolveState::UpdateVisuals;
                stateTimer = 0.f;
            }
            break;

        case ResolveState::UpdateVisuals:
            DoUpdateVisuals();
            // Pause avant de verifier les nouveaux matchs
            state = ResolveState::CheckAgain;
            stateTimer = 0.f;
            break;

        case ResolveState::CheckAgain:
            stateTimer += _dt;
            if (stateTimer >= 0.2f)
            {
                if (HasMatch())
                {
                    // Nouvelle chaine !
                    state = ResolveState::FlashMatches;
                    stateTimer = 0.f;
                    flashOn = true;
                }
                else
                {
                    // Termine
                    state = ResolveState::Idle;
                    if (onResolveDone) onResolveDone();
                }
            }
            break;
        }
    }

    // Utilitaires publics pour la scene
    bool HasMatch() const
    {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width - 2; x++)
            {
                int v = grid[y][x];
                if (v >= 0 && v == grid[y][x + 1] && v == grid[y][x + 2])
                    return true;
            }

        for (int x = 0; x < width; x++)
            for (int y = 0; y < height - 2; y++)
            {
                int v = grid[y][x];
                if (v >= 0 && v == grid[y + 1][x] && v == grid[y + 2][x])
                    return true;
            }

        return false;
    }

    sf::Color GetColorFromType(int type) const
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
        default:  return { 50, 50, 50 }; // case vide = gris fonce
        }
    }

private:
    ResolveState state = ResolveState::Idle;
    float        stateTimer = 0.f;
    bool         flashOn = true;

    // Marque en blanc les cases qui matchent
    void HighlightMatches(bool _white)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width - 2; x++)
            {
                int v = grid[y][x];
                if (v >= 0 && v == grid[y][x + 1] && v == grid[y][x + 2])
                {
                    for (int i = 0; i < 3; i++)
                        SetTileColor(y, x + i, _white
                            ? sf::Color::White
                            : GetColorFromType(grid[y][x + i]));
                    // etendre le match si plus de 3
                    int k = x + 3;
                    while (k < width && grid[y][k] == v)
                    {
                        SetTileColor(y, k, _white
                            ? sf::Color::White
                            : GetColorFromType(grid[y][k]));
                        k++;
                    }
                }
            }
        }

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height - 2; y++)
            {
                int v = grid[y][x];
                if (v >= 0 && v == grid[y + 1][x] && v == grid[y + 2][x])
                {
                    for (int i = 0; i < 3; i++)
                        SetTileColor(y + i, x, _white
                            ? sf::Color::White
                            : GetColorFromType(grid[y + i][x]));
                    int k = y + 3;
                    while (k < height && grid[k][x] == v)
                    {
                        SetTileColor(k, x, _white
                            ? sf::Color::White
                            : GetColorFromType(grid[k][x]));
                        k++;
                    }
                }
            }
        }
    }

    void DoRemoveMatches()
    {
        for (int y = 0; y < height; y++)
        {
            int count = 1;
            for (int x = 1; x < width; x++)
            {
                // Horizontal
                if (grid[y][x] >= 0 && grid[y][x] == grid[y][x - 1])
                {
                    count++;
                }
                else
                {
                    if (count >= 3)
                        MarkMatch(y, x - count, count, true);
                    count = 1;
                }
            }
            if (count >= 3)
                MarkMatch(y, width - count, count, true);
        }

        for (int x = 0; x < width; x++)
        {
            int count = 1;
            for (int y = 1; y < height; y++)
            {
                // Vertical
                if (grid[y][x] >= 0 && grid[y][x] == grid[y - 1][x])
                {
                    count++;
                }
                else
                {
                    if (count >= 3)
                        MarkMatch(y - count, x, count, false);
                    count = 1;
                }
            }
            if (count >= 3)
                MarkMatch(height - count, x, count, false);
        }
    }

    void MarkMatch(int y, int x, int count, bool horizontal)
    {
        for (int i = 0; i < count; i++)
        {
            if (horizontal) grid[y][x + i] = -1;
            else            grid[y + i][x] = -1;
        }

        if (count == 4)
        {
            if (horizontal) grid[y][x] = 100;
            else            grid[y][x] = 100;
        }
        else if (count >= 5)
        {
            if (horizontal) grid[y][x] = 200;
            else            grid[y][x] = 200;
        }
    }

    void DoApplyGravity()
    {
        bool moved = true;
        while (moved)
        {
            moved = false;
            for (int x = 0; x < width; x++)
            {
                for (int y = height - 1; y > 0; y--)
                {
                    if (grid[y][x] == -1 && grid[y - 1][x] != -1)
                    {
                        std::swap(grid[y][x], grid[y - 1][x]);
                        moved = true;
                    }
                }
            }
        }

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (grid[y][x] == -1)
                    grid[y][x] = rand() % 5;
            }
        }
    }

    void DoUpdateVisuals()
    {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                SetTileColor(y, x, GetColorFromType(grid[y][x]));
    }

    void SetTileColor(int y, int x, const sf::Color& color)
    {
        auto* r = tiles[y][x]->GetComponent<RectangleShapeRenderer>();
        if (r) r->SetColor(color);
    }
};