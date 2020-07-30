#include "Game.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Random.h"
#include <list>


void Game::Initialize()
{
	g_audioSystem.AddAudio("playerDeath", "playerdeath.wav");
	g_audioSystem.AddAudio("enemyDeath", "enemydeath.wav");
	g_audioSystem.AddAudio("shoot", "shoot.wav");
	m_scene.Startup();
	m_scene.SetGame(this);
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	g_audioSystem.Update(dt);

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE)) {
			m_state = eState::INIT_GAME;
		}
		break;
	case Game::eState::INIT_GAME:
		m_score = 0;
		m_lives = 3;
		m_state = GAME_START;
		break;
	case Game::eState::GAME_START:
	{
		
		Player* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);
		
		Locator* locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ 2, 2 };
		player->AddChild(locator);

		locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ -2, 2 };
		player->AddChild(locator);

		for (size_t i = 0; i < 10; i++) {

			nc::Actor* actor = new Enemy;
			actor->Load("enemy.txt");
			Enemy* enemy = dynamic_cast<Enemy*>(actor);
			float distance = nc::random(300, 200);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate({ 0.0f,distance }, angle);

			enemy->SetTarget(player);
			enemy->SetSpeed(nc::random(50, 100));
			actor->GetTransform().position = nc::Vector2{400, 300 } + position;
			m_scene.AddActor(actor);

		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		if (m_spawnTimer >= 3.0f) {
			m_spawnTimer = 0;

			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			
			float distance = nc::random(300, 200);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate({ 0.0f,distance }, angle);
			enemy->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;
			m_scene.AddActor(enemy);

		}
		if (m_score > m_highScore) m_highScore = m_score;
		
		break;
	case Game::eState::PLAYER_DEAD:
		m_lives--;
		m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3;
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene.RemoveAllActors();
			m_state = eState::GAME_START;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		m_scene.RemoveAllActors();
		if (m_stateTimer <= 0) {
			m_state = eState::TITLE;
		}
			break;
		default:
			break;
	}
		m_scene.Update(dt);

	//int x, y;
	//Core::Input::GetMousePos(x, y);

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
	//	nc::Color colors[] = { {1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
	//	nc::Color color = colors[rand() % 4];
	//	g_particleSystem.Create({ x,y }, 0, 180, 30, 1, color, 100, 200);
	//}

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	switch (m_state)
	{
	case Game::eState::TITLE:
		graphics.DrawString(400, 300, "Bruh");
		break;
	case Game::eState::GAME_START:
		break;
	case Game::eState::GAME: {
		
		
	}
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
	m_scene.Draw(graphics);
	graphics.SetColor(nc::Color{ 1,1,1 });
	std::string score = "Score: " + std::to_string(m_score);
	graphics.DrawString(700, 10, score.c_str());
	std::string lives = "Lives: " + std::to_string(m_lives);
	graphics.DrawString(700, 25, lives.c_str());
	score = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(350, 10, score.c_str());
	m_scene.Draw(graphics);

}
