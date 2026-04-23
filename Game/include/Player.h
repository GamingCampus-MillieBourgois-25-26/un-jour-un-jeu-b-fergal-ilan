#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "WindowModule.h"

class Player : public Component
{
private:
	int lives = 3;
	float invincibleTimer = 0.f;
	bool invincible = false;
	float blinkTimer = 0.f;
	bool visible = true;

public:
    float radius = 15.f;
	void Update(const float _delta_time) override
	{

        if (invincible)
        {
            invincibleTimer -= _delta_time;

            blinkTimer += _delta_time;

            if (blinkTimer > 0.1f)
            {
                visible = !visible;
                blinkTimer = 0.f;
            }

            if (invincibleTimer <= 0.f)
            {
                invincible = false;
                visible = true; // reset visibility
            }
        }
        auto renderer = GetOwner()->GetComponent<RectangleShapeRenderer>();

        if (renderer)
        {
            renderer->SetColor(visible ? sf::Color::Cyan : sf::Color::Transparent);
        }

        Maths::Vector2<float> position = GetOwner()->GetPosition();
		Maths::Vector2u window_size = GetModule<WindowModule>()->GetSize();

		if (position.x > window_size.x)
			position.x -= speed * _delta_time;
		if (position.x < window_size.x - window_size.x)
			position.x += speed * _delta_time;
		if (position.y > window_size.y)
			position.y -= speed * _delta_time;
		if (position.y < window_size.y - window_size.y)
			position.y += speed * _delta_time;
		
			if (InputModule::GetKey(sf::Keyboard::Key::D))
			{
				position.x += speed * _delta_time;
			}
			if (InputModule::GetKey(sf::Keyboard::Key::Q))
			{
				position.x -= speed * _delta_time;
			}

			if (InputModule::GetKey(sf::Keyboard::Key::Z))
			{
				position.y -= speed * _delta_time;
			}
			if (InputModule::GetKey(sf::Keyboard::Key::S))
			{
				position.y += speed * _delta_time;
			}

		GetOwner()->SetPosition(position);

		if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
		{
			Engine::GetInstance()->RequestQuit();
		}
	}

	Maths::Vector2f GetPosition() const
	{
		return GetOwner()->GetPosition();
	}

	void TakeDamage()
	{
		if (invincible)
			return; // ignore les hits

		lives--;

		invincible = true;
		invincibleTimer = 0.5f; // 0.5 secondes d’immunité

		if (lives <= 0)
		{
			Engine::GetInstance()->RequestQuit();
		}
	}

	float speed = 500.0f;
};