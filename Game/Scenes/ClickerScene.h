// Scenes/ClickerScene.h
#pragma once
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Clicker/Bouton.h"
#include "Clicker/ShopButton.h"

class ClickerScene final : public Scene
{
public:
    ClickerScene() : Scene("ClickerScene")
    {
        GameObject* btn = CreateGameObject("ClickButton");
        btn->SetPosition({ 250.f, 260.f });

        RectangleShapeRenderer* rb = btn->CreateComponent<RectangleShapeRenderer>();
        rb->SetColor(sf::Color{ 60, 120, 220 });
        rb->SetSize({ 100.f, 50.f });

        btn->CreateComponent<ClickerButton>();

        GameObject* btnMulti = CreateGameObject("ShopMultiplier");
        btnMulti->SetPosition({ 50.f, 370.f });

        RectangleShapeRenderer* rm = btnMulti->CreateComponent<RectangleShapeRenderer>();
        rm->SetColor(sf::Color{ 80, 180, 80 });
        rm->SetSize({ 160.f, 50.f });

        btnMulti->CreateComponent<ShopButton>(
        50, 2.5f,
        "Multiplicateur x2",
        []() { gGameState.pointsPerClick *= 2; }
        );

        GameObject* btnAuto = CreateGameObject("ShopAuto");
        btnAuto->SetPosition({ 50.f, 440.f });

        RectangleShapeRenderer* ra = btnAuto->CreateComponent<RectangleShapeRenderer>();
        ra->SetColor(sf::Color{ 80, 180, 80 });
        ra->SetSize({ 160.f, 50.f });
        
        btnAuto->CreateComponent<ShopButton>(
            30, 2.2f,
            "Auto-clicker +1/s",
            []() { gGameState.autoClickRate += 1.f; }
        );
    }
};




