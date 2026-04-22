#pragma once
#include "Core/Component.h"
#include "InputModule.h"

class Player : public Component
{
public:
	void Update(const float _delta_time) override
	{
		Maths::Vector2<float> position = GetOwner()->GetPosition();
		Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

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

	float speed = 500.0f;
};
