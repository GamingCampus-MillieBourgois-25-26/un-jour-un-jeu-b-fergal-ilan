#pragma once
#include "Core/Component.h"
#include "InputModule.h"

class Enemy : public Component
{
public:
	void Update(const float _delta_time) override
	{
		Maths::Vector2<float> position = GetOwner()->GetPosition();
		Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

		if (!Isturnedx) {
			position.x += speed * _delta_time;
			if (position.x > window_size.x) {
				Isturnedx = true;
			}
		}
		else if (Isturnedx) {
			position.x -= speed * _delta_time;
			if (position.x < window_size.x - window_size.x) {
				Isturnedx = false;
			}
		}
		if (!Isturnedy) {
			position.y += speed * _delta_time;
			if (position.y > window_size.y) {
				Isturnedy = true;
			}
		}
		else if (Isturnedy) {
			position.y -= speed * _delta_time;
			if (position.y < window_size.y - window_size.y) {
				Isturnedy = false;
			}
		}
		GetOwner()->SetPosition(position);
	}

	bool Isturnedx = true;
	bool Isturnedy = true;

	float speed = 100.0f;
};
