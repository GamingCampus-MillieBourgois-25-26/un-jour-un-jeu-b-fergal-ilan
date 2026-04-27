#pragma once

#include "Core/Component.h"
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <iostream>

class ClickableComponent : public Component
{
public:
    std::function<void(int, int)> onClick; // passe col, row directement
    int gridX = 0;
    int gridY = 0;

private:
    bool wasPressed = false;

public:
    void Update(float _dt) override
    {
        sf::RenderWindow* window = Engine::GetInstance()
            ->GetModuleManager()->GetModule<WindowModule>()->GetWindow();

        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        Maths::Vector2f pos = GetOwner()->GetPosition();
        float size = 40.f;

        bool inside =
            mousePos.x >= pos.x && mousePos.x <= pos.x + size &&
            mousePos.y >= pos.y && mousePos.y <= pos.y + size;

        if (isPressed && !wasPressed && inside)
        {
            if (onClick) onClick(gridX, gridY);
        }

        wasPressed = isPressed;
    }
};