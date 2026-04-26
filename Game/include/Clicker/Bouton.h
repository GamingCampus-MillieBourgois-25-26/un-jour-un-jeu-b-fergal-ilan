#pragma once
#include "Core/Scene.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "GameState.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include <iostream>

class ClickerButton : public Component
{
public:
    void Update(float _dt) override
    {
        // Auto : accumule des fractions de point, independant du pointsPerClick
        if (gGameState.autoClickRate > 0.f)
        {
            gGameState.autoAccumulator += gGameState.autoClickRate * _dt;

            if (gGameState.autoAccumulator >= 1.f)
            {
                int earned = static_cast<int>(gGameState.autoAccumulator);
                gGameState.points += earned;
                gGameState.autoAccumulator -= static_cast<float>(earned);
                std::cout << "Auto : +" << earned
                    << " | Total : " << gGameState.points << "\n";
            }
        }

        // Clic manuel
        if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
            return;

        Maths::Vector2f mouse = {
            (float)InputModule::GetMousePosition().x,
            (float)InputModule::GetMousePosition().y
        };

        Maths::Vector2f pos = GetOwner()->GetPosition();
        if (mouse.x >= pos.x && mouse.x <= pos.x + w &&
            mouse.y >= pos.y && mouse.y <= pos.y + h)
        {
            AddPoints();
        }
    }

private:
    float w = 100.f;
    float h = 50.f;
    float autoTimer = 0.f;

    void AddPoints()
    {
        gGameState.points += gGameState.pointsPerClick;
        std::cout << "Points : " << gGameState.points
            << " (x" << gGameState.pointsPerClick << "/clic"
            << ", auto: " << gGameState.autoClickRate << "/s)\n";
    }
};