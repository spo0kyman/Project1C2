#include "Game.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Random.h"
#include <list>

void Game::Initialize()
{
	m_scene.Startup();
	g_particleSystem.Startup();

	Player* player = new Player;
	player->Load("player.txt");
	m_scene.AddActor(player);

	for (size_t i = 0; i < 10; i++) {

		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		Enemy* enemy = dynamic_cast<Enemy*>(actor);

		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(50, 100));
		actor->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		m_scene.AddActor(actor);
	}
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	m_spawnTimer += dt;
	if (m_spawnTimer >= 3.0f) {
		m_spawnTimer = 0;

		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(m_scene.GetActor<Player>());
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		m_scene.AddActor(enemy);

	}

	int x, y;
	Core::Input::GetMousePos(x, y);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		nc::Color colors[] = { {1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create({ x,y }, 0, 180, 30, 1, color, 100, 200);
	}

	g_particleSystem.Update(dt);
	m_scene.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	g_particleSystem.Draw(graphics);
	m_scene.Draw(graphics);
}
