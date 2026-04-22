#pragma once
#include "WindowModule.h"
#include "SceneModule.h"
#include "Core/Component.h"
#include "InputModule.h"

class Enemy : public Component
{
public:
	void Update(const float _delta_time) override
	{
		Maths::Vector2<float> position = GetOwner()->GetPosition();
		
		position.x += speed * _delta_time;

		GetOwner()->SetPosition(position);
	}

	
	float speed = 100.0f;
};
