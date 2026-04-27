#pragma once
#include "Core/Component.h"
#include "Components/TextRenderer.h"
#include <string>

class CostDisplayComponent : public Component
{
public:
    int* cost = nullptr;
    TextRenderer* text = nullptr;

    CostDisplayComponent(int* _cost) : cost(_cost) {}

    void Start() override
    {
        text = GetOwner()->GetComponent<TextRenderer>();
    }

    void Update(float dt) override
    {
        if (!cost || !text) return;

        text->SetText("Cost : " + std::to_string(*cost));
    }
};