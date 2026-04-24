#pragma once

#include "FPlayer.h"
#include "Bullet.h"
#include "EnemyShooter.h"
#include "BulletPool.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "FBoss.h"
#include "Modules/AssetsModule.h"
class Bullet;
class EnemyShooter;
class FBHene final : public Scene
{
public:
	FBHene() : Scene("F_BULLET_HELLScene")
	{
		gBulletPool.Init(this, 1000);
		GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Cyan);
		player->CreateComponent<FPlayer>();

		/*GameObject* enemy = CreateDummyGameObject("Enemy", 100.f, sf::Color::Blue);
        enemy->CreateComponent<EnemyShooter>();*/
		GameObject* boss = CreateGameObject("Boss");
		boss->CreateComponent<Boss>();

		/*GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Yellow);*/

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		/*Texture* texture = assets_module->LoadAsset<Texture>("logo.png");

		player->CreateComponent<SpriteRenderer>(texture);*/
	}
	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, _position));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(10.f);
		square_collider->SetHeight(10.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(40.f, 40.f));

		return game_object;
	}
};
//idee : 
// ajouter des boss avec plusieurs phases(HP  patterns)
//faire un système de score
// ajouter un dash pour le joueur(très bullet hell)
// améliorer les patterns(spirale plus complexe, aim, random)
// optimiser les bullets(pooling pour 1000 + projectiles sans lag)
// ajouter des effets(flash hit, slow motion, screen shake)*/