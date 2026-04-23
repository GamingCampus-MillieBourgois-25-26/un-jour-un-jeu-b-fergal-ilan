//#pragma once
//#include "Core/Component.h"
//#include "InputModule.h"
//#include <vector>
//
//enum class TileType
//{
//    Empty,
//    Path
//};
//
//const int width = 10;
//const int height = 8;
//const float tileSize = 64.f;
//
//TileType grid[height][width] =
//{
//    {TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Path,  TileType::Path,  TileType::Path,  TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Empty, TileType::Empty, TileType::Path,  TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Empty, TileType::Empty, TileType::Path,  TileType::Path,  TileType::Path,  TileType::Path,  TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Path,  TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Path,  TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty},
//    {TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Path,  TileType::Path,  TileType::Path,  TileType::Path,  TileType::Path},
//    {TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty}
//};
//
//std::vector<Maths::Vector2f> path;