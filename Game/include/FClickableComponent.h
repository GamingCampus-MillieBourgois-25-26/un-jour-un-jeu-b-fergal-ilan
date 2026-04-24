#pragma once
#include "Core/Component.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class ClickableComponent : public Component
{
private:
    bool wasPressed = false;

public:
    int* score = nullptr;
    ClickableComponent(int* _score)
        : score(_score)
    {
    }

    void Update(float dt) override
    {
        if (!score)
            return;

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
            (*score)++;
            std::cout << "Score: " << *score << std::endl;
        }

        wasPressed = isPressed;

    }
};