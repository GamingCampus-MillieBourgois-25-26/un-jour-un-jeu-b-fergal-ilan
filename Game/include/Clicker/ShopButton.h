#pragma once
#include "Core/Component.h"
#include "Components/RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include "GameState.h"
#include <functional>
#include <iostream>
#include <string>

class ShopButton : public Component
{
public:
    ShopButton(int _baseCost, float _costScale,
        const std::string& _label,
        std::function<void()> _onBuy)
        : baseCost(_baseCost), costScale(_costScale),
        label(_label), onBuy(_onBuy) {
    }

    void Start() override
    {
        UpdateColor();
    }

    void Update(float _dt) override
    {
        UpdateColor();

        if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
            return;

        Maths::Vector2f mouse = {
            (float)InputModule::GetMousePosition().x,
            (float)InputModule::GetMousePosition().y
        };

        Maths::Vector2f pos = GetOwner()->GetPosition();
        if (mouse.x < pos.x || mouse.x > pos.x + w ||
            mouse.y < pos.y || mouse.y > pos.y + h)
            return;

        int cost = CurrentCost();

        if (gGameState.points < cost)
        {
            std::cout << "[Shop] Pas assez de points ! ("
                << gGameState.points << "/" << cost << ")\n";
            return;
        }

        gGameState.points -= cost;
        purchaseCount++;
        onBuy();

        std::cout << "[Shop] " << label << " achete ! (niveau " << purchaseCount
            << ") - Prochain prix : " << CurrentCost() << " pts\n";
    }

    int CurrentCost() const
    {
        // Prix = baseCost * costScale^purchaseCount
        float cost = static_cast<float>(baseCost);
        for (int i = 0; i < purchaseCount; i++)
            cost *= costScale * 0.8f;
        return static_cast<int>(cost);
    }

    int GetPurchaseCount() const { return purchaseCount; }

private:
    float w = 160.f;
    float h = 50.f;

    int baseCost;
    float costScale;
    std::string label;
    std::function<void()> onBuy;
    int purchaseCount = 0;

    void UpdateColor()
    {
        auto* r = GetOwner()->GetComponent<RectangleShapeRenderer>();
        if (!r) return;

        // Vert si achetable, rouge sinon
        r->SetColor(gGameState.points >= CurrentCost()
            ? sf::Color{ 80, 180, 80 }
        : sf::Color{ 180, 60, 60 });
    }
};