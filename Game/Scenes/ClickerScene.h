#pragma once

#include "Clicker/Bouton.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"

class ClickerScene final : public Scene
{
public:
    ClickerScene() : Scene("ClickerScene")
    {
        // Bouton centré dans la fenêtre (600x600)
        GameObject* button = CreateGameObject("Button");
        button->SetPosition({ 250.f, 275.f }); 

        RectangleShapeRenderer* r = button->CreateComponent<RectangleShapeRenderer>();
        r->SetColor(sf::Color::Green);
        r->SetSize({ 100.f, 50.f });

        button->CreateComponent<ClickerButton>();
    }
};
