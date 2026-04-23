#pragma once

#include "FPlayer.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "FEnemyMovement.h"
#include "FTower.h"
#include "EnemyWave.h"
#include "TowerPlacement.h"
#include <iostream>
#include <algorithm>

class FTowerDef final : public Scene
{
public:
	int m_currentWave = 0;
	FTowerDef() : Scene("F_TowerDefScene")
	{
		
		/*GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Cyan);
		player->CreateComponent<FPlayer>();*/
		GameObject* tower = CreateDummyGameObject("Tower", 300.f, sf::Color::Red);
		tower->CreateComponent<Tower>();
		SpawnEnemy();

		/*GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Yellow);*/
		GameObject* manager = CreateGameObject("TowerPlacement");
		manager->CreateComponent<TowerPlacement>();

		m_wave = EnemyWave(5, 0.5f);  
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
	void NextWave()
	{
		m_currentWave++;

		int enemyCount = 5 + m_currentWave * 2;

		m_wave.Reset(enemyCount);
	}

	std::vector<GameObject*>& GetEnemies()
	{
		return m_enemies;
	}
	// ne marche pas 
	void Update(float _delta_time)
	{
		Scene::Update(_delta_time);
		
		m_wave.Update(_delta_time);

		if (m_wave.CanSpawn())
		{
			std::cout << "CAN SPAWN" << std::endl;
			SpawnEnemy();
			m_wave.ConsumeSpawn();
		}

		if (m_wave.IsFinished() && m_enemies.size() == 0)
		{
			NextWave();
		}

		m_enemies.erase(
			std::remove_if(m_enemies.begin(), m_enemies.end(),
				[](GameObject* e)
				{
					std::cout << "ERASE CHECK" << std::endl;
					return e == nullptr || e->IsMarkedForDeletion();
				}),
			m_enemies.end()
		);
	}
	void SpawnEnemy()
	{
		GameObject* enemy = CreateDummyGameObject("Enemy", 0.f, sf::Color::Blue);

		enemy->SetPosition(path[0]);

		auto* move = enemy->CreateComponent<EnemyMovement>();
		move->SetPath(path);

		m_enemies.push_back(enemy);
	}
	const std::vector<GameObject*>& GetEnemies() const { return m_enemies; }
	std::vector<Maths::Vector2f> path = {
	{0.f, 100.f},
	{300.f, 100.f},
	{300.f, 300.f},
	{600.f, 300.f}
	};
private:
	std::vector<GameObject*> m_enemies;
	EnemyWave m_wave;
};
 /* idee
	money system
	HP ennemis
	targeting intelligent
	placement de tours
	boss waves*/