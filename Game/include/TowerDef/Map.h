#pragma once
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Maths/Vector2.h"
#include <vector>
#include <array>

enum class TileType : int
{
    Empty = 0,  // inutilisable (herbe, décor)
    Road = 1,  // chemin des ennemis
    Buildable = 2,  // zone où poser des tours
};

// Couleurs par type de tile
static sf::Color TileColor(TileType t)
{
    switch (t)
    {
    case TileType::Road:      return { 180, 140,  80 }; // sable/route
    case TileType::Buildable: return { 60, 120,  60 }; // herbe constructible
    default:                  return { 30,  30,  30 }; // fond sombre inutilisable
    }
}

constexpr int MAP_COLS = 30;
constexpr int MAP_ROWS = 30;
constexpr float TILE_SIZE = 20.f;

static constexpr std::array<std::array<int, MAP_COLS>, MAP_ROWS> MAP_DATA =
{ {
        // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 0
        {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 1
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 2
        {  0, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 3
        {  0, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 4
        {  0, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 5
        {  0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0 }, // 6
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0 }, // 7
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0 }, // 8
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }, // 9
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // 10
        {  0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // 11
        {  0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0 }, // 12
        {  0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0 }, // 13
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0 }, // 14
        {  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }, // 15
        {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 16
        {  0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 17
        {  0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 18
        {  0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0 }, // 19
        {  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0 }, // 20
        {  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }, // 21
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // 22
        {  0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // 23
        {  0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // 24
        {  0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 0, 0 }, // 25
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 0, 0 }, // 26
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 0, 0 }, // 27
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // 28
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 29
    } };
// clang-format on

class MapComponent : public Component
{
public:
    // Retourne le type d'une tile à partir d'une position écran
    static TileType GetTileAt(const Maths::Vector2f& _worldPos)
    {
        const int col = static_cast<int>(_worldPos.x / TILE_SIZE);
        const int row = static_cast<int>(_worldPos.y / TILE_SIZE);

        if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS)
            return TileType::Empty;

        return static_cast<TileType>(MAP_DATA[row][col]);
    }

    // Retourne le centre monde d'une tile (col, row)
    static Maths::Vector2f TileCenter(int _col, int _row)
    {
        return {
            _col * TILE_SIZE + TILE_SIZE * 0.5f,
            _row * TILE_SIZE + TILE_SIZE * 0.5f
        };
    }

    // Génère les waypoints de la route dans l'ordre de MAP_DATA (ligne par ligne)
    // → à remplacer par une liste manuelle si tu veux un ordre précis
    static std::vector<Maths::Vector2f> BuildRoadPath()
    {
        // Chemin hardcodé correspondant aux tiles Road du tableau ci-dessus
        // Entrée col 0 row 1 → sortie col 27 row 28
        return {
            TileCenter(0,  1),
            TileCenter(9,  1),
            TileCenter(9,  5),
            TileCenter(18, 5),
            TileCenter(18, 9),
            TileCenter(25, 9),
            TileCenter(25, 15),
            TileCenter(1,  15),
            TileCenter(1,  21),
            TileCenter(27, 21),
            TileCenter(27, 28),
        };
    }
};

// Instancie un GameObject par tile dans la scène
inline void SpawnMap(Scene* _scene)
{
    static int tileId = 0;
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            const TileType type = static_cast<TileType>(MAP_DATA[row][col]);

            GameObject* tile = _scene->CreateGameObject("Tile_" + std::to_string(tileId++));
            tile->SetPosition({ col * TILE_SIZE, row * TILE_SIZE });

            RectangleShapeRenderer* r = tile->CreateComponent<RectangleShapeRenderer>();
            r->SetColor(TileColor(type));
            r->SetSize({ TILE_SIZE, TILE_SIZE });
        }
    }
}