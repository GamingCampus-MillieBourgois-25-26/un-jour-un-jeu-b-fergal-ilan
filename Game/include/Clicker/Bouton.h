#pragma once
#include "Core/Scene.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include <iostream>

class ClickerButton : public Component
{
public:
    void Update(float _dt) override
    {
        if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
            return;

        const Maths::Vector2f mousePos = {
            (float)InputModule::GetMousePosition().x,
            (float)InputModule::GetMousePosition().y
        };

        const Maths::Vector2f pos = GetOwner()->GetPosition();
        const Maths::Vector2f size = { buttonW, buttonH };

        // AABB : est-ce que la souris est dans le bouton ?
        if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
            mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
        {
            count++;
            std::cout << "Clicks : " << count << "\n";
        }
    }

private:
    int count = 0;
    float buttonW = 100.f;
    float buttonH = 50.f;
};