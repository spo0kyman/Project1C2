#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>

Player player;

std::list<Enemy*> sceneActors;
	
nc::Transform transform{ {400, 300}, 4, 0 };

nc::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;

float speed = 300.0f;

nc::Vector2 velocity;
float thrust = 100.0f;

float frameTime;
float roundTime = 0;
bool gameOver{ false };

float t{ 0 };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 5) gameOver = true;

	t = t + (dt * 5.0f);

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//PLAYER
	player.Update(dt);

	//ENEMY
	//enemy.Update(dt);
	/*nc::Vector2 direction = player.GetTransform().position - enemy.GetTransform().position;
	direction.Normalize();
	nc::Vector2 enemyVelocity = direction * 100.0f;
	enemy.GetTransform().position = enemy.GetTransform().position + (enemyVelocity * dt);
	enemy.GetTransform().angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);*/

	for (Enemy* e : sceneActors) {
		e->Update(dt);
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	player.Draw(graphics);
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	//nc::Color c = nc::Lerp(nc::Color{ 1,0,0 }, nc::Color{ 0,1,0 }, v);
	//graphics.SetColor(c);
	//nc::Vector2 p = nc::Lerp(nc::Vector2{ 200,200 }, nc::Vector2{ 600, 200 }, v);
	//graphics.DrawString(p.x, p.y, "Last Starfighter");

	for (Enemy* e : sceneActors) {
		e->Draw(graphics);
	}

}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 << std::endl;

	player.Load("player.txt");

	for (size_t i = 0; i < 10; i++) {

		Enemy* e = new Enemy;
		e->Load("enemy.txt");
		e->SetTarget(&player);
		e->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		sceneActors.push_back(e);

	}
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
