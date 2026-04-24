#pragma once
#include "Core/Component.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class ShopComponent : public Component
{
public:
    int* score = nullptr;
    int* clickPower = nullptr;
    int* cost = nullptr;

    bool wasPressed = false;

    ShopComponent(int* s, int* p, int* c)
        : score(s), clickPower(p), cost(c)
    {
    }

    void Update(float dt) override
    {
        if (!score || !clickPower || !cost)
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
            std::cout << " Cost: " << *cost << std::endl;
            if (*score >= *cost)
            {
                *score -= *cost;
                (*clickPower)++;
                *cost *= 2;

                std::cout << "Upgrade! Power: " << *clickPower
                    << " Cost: " << *cost << std::endl;
            }
        }

        wasPressed = isPressed;
    }
};