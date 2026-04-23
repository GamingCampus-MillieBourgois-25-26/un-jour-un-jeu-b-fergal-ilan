#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "FTower.h"
#include <SFML/Window/Mouse.hpp>
#include "Components/RectangleShapeRenderer.h"
#include <SFML/Window/Keyboard.hpp>

class TowerPlacement : public Component
{
public:
    void Update(float dt) override
    {
        HandleInput();

        if (m_preview)
        {
            UpdatePreviewPosition();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                PlaceTower();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                CancelPreview();
            }
        }
    }

    void StartPreview()
    {
        std::cout << "CREATE PREVIEW" << std::endl;
        if (m_preview)
            return;

        Scene* scene = GetOwner()->GetScene();

        m_preview = scene->CreateGameObject("TowerPreview");

        auto* renderer = m_preview->CreateComponent<RectangleShapeRenderer>();
        renderer->SetSize({ 40.f, 40.f });
        renderer->SetColor(sf::Color(0, 255, 0, 120));

        m_preview->SetPosition(GetMouseWorldPos());
    }

    void UpdatePreviewPosition()
    {
        if (!m_preview) return;

        m_preview->SetPosition(GetMouseWorldPos());
    }

    void PlaceTower()
    {
        if (!m_preview || !m_canClick)
            return;

        m_canClick = false;

        Scene* scene = GetOwner()->GetScene();

        GameObject* tower = scene->CreateGameObject("Tower");
        tower->SetPosition(m_preview->GetPosition());

        tower->CreateComponent<Tower>();

        CancelPreview();
    }

    void CancelPreview()
    {
        if (m_preview)
        {
            m_preview->MarkForDeletion();
            m_preview = nullptr;
        }
    }

private:
    GameObject* m_preview = nullptr;
    bool m_canClick = true;

    void HandleInput()
    {
        // empêche double click
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            m_canClick = true;
    }


    Maths::Vector2f GetMouseWorldPos()
    {
        sf::Vector2i mouse = sf::Mouse::getPosition();

        return Maths::Vector2f(
            (float)mouse.x,
            (float)mouse.y
        );

    }
};