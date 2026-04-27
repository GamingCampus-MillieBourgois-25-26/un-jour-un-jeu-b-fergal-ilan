// TowerDef/Tenemy.h
#pragma once
#include <vector>
#include <cmath>
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"

class EnemyMovement : public Component
{
public:
    EnemyMovement(std::vector<Maths::Vector2f>* _path, int _hp = 3)
        : path(_path), hp(_hp), maxHp(_hp) {
    }

    void Start() override
    {
        currentPoint = 0;
        if (path && !path->empty())
            GetOwner()->SetPosition((*path)[0]);
    }

    void Update(float _dt) override
    {
        if (IsDead()) return;

        // Déplacement
        if (!path || currentPoint >= path->size()) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Maths::Vector2f target = (*path)[currentPoint];
        Maths::Vector2f dir = target - pos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length < 5.f)
        {
            currentPoint++;
            // Arrivé au bout du chemin → mort (a atteint la base)
            if (currentPoint >= path->size())
            {
                Kill();
                return;
            }
            return;
        }

        dir.x /= length;
        dir.y /= length;
        pos.x += dir.x * speed * _dt;
        pos.y += dir.y * speed * _dt;
        GetOwner()->SetPosition(pos);

        // Couleur selon PV restants
        UpdateColor();
    }

    void TakeDamage(int _dmg = 1)
    {
        if (IsDead()) return;
        hp -= _dmg;
        if (hp <= 0)
            Kill();
    }

    bool IsDead() const { return dead; }

private:
    std::vector<Maths::Vector2f>* path = nullptr;
    size_t currentPoint = 0;
    float speed = 100.f;

    int hp;
    int maxHp;
    bool dead = false;

    void Kill()
    {
        dead = true;
        GetOwner()->MarkForDeletion();
    }

    void UpdateColor()
    {
        auto* r = GetOwner()->GetComponent<RectangleShapeRenderer>();
        if (!r) return;

        // Vert → Orange → Rouge selon PV
        if (hp >= maxHp)         r->SetColor(sf::Color::Red);
        else if (hp == maxHp - 1) r->SetColor({ 255, 140, 0 }); // orange
        else                      r->SetColor({ 180, 0, 0 });    // rouge foncé
    }
};