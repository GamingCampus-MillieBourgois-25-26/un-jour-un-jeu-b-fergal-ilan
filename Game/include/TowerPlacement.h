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
    bool m_keyPressed = false;
    void Update(float dt) override
    {
        HandleInput();

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
        {
            if (!m_keyPressed)
            {
                StartPreview();
                m_keyPressed = true;
            }
        }
        else
        {
            m_keyPressed = false;
        }

        if (m_preview)
        {
            UpdatePreviewPosition();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (m_canClick)
                {
                    PlaceTower();
                    m_canClick = false;
                }
            }
            else
            {
                m_canClick = true;
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
        renderer->SetColor(sf::Color::Green);

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

        auto* renderer = tower->CreateComponent<RectangleShapeRenderer>();
        renderer->SetSize({ 40.f, 40.f });
        renderer->SetColor(sf::Color::Red);

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
        return Maths::Vector2f((float)mouse.x, (float)mouse.y);
    }
};