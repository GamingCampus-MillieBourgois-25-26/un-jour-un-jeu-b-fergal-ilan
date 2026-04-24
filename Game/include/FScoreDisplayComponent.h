#pragma once
#include "Core/Component.h"
#include "Components/TextRenderer.h"
#include <string>

class ScoreDisplayComponent : public Component
{
public:
    int* score = nullptr;
    TextRenderer* text = nullptr;

    ScoreDisplayComponent(int* _score) : score(_score) {}

    void Start() override
    {
        text = GetOwner()->GetComponent<TextRenderer>();
    }

    void Update(float dt) override
    {
        if (!score || !text) return;

        text->SetText("score : " + std::to_string(*score));
    }
};