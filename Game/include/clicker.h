#pragma once

#include "Core/Component.h"
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <iostream>
class ClickableComponent : public Component
{
private:
    bool wasPressed = false;

public:
    std::function<void(GameObject*)> onClick;
    int gridX;
    int gridY;

    void Update(float dt) override
    {
        auto windowModule = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<WindowModule>();

        sf::RenderWindow* window = windowModule->GetWindow();

        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        auto pos = GetOwner()->GetPosition();
        float size = 40.f;

        bool inside =
            mousePos.x >= pos.x && mousePos.x <= pos.x + size &&
            mousePos.y >= pos.y && mousePos.y <= pos.y + size;

        if (isPressed && !wasPressed && inside)
        {
            std::cout << "clicker" << std::endl;
            if (onClick)
                onClick(GetOwner());
        }

        wasPressed = isPressed;
    }
};