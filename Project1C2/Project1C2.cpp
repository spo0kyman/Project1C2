#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>

std::list<Enemy*> sceneActors;

float frameTime;
float spawnTimer{ 0 };

template <typename T>

T* GetActor() {
	T* actor{ nullptr };

	for (nc::Actor* a : sceneActors) {
		actor = dynamic_cast<T*>(a);
		if (actor) break;
	}

	return actor;
}

template <typename T>
std::vector<T*> GetActors() {
	std::vector<T*> actors;

	for (nc::Actor* a : sceneActors) {
		T* actor = dynamic_cast<T*>(a);
		if (actor) {
			actors.push_back(actor);
		}
	}

	return actors;
}

void RemoveActors(nc::Actor* actor) {
	auto iter = std::find(sceneActors.begin(), sceneActors.end(), actor);
	if (iter != sceneActors.end()) {
		delete* iter;
		sceneActors.erase(iter);
	}
}

bool Update(float dt)
{
	frameTime = dt;

	spawnTimer += dt;
	if (spawnTimer >= 3.0f) {
		spawnTimer = 0;

		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");

		enemy->SetTarget(GetActor<Player>());
		enemy->SetSpeed(nc::random(50, 100));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		sceneActors.push_back(enemy);

	}

	//if (Core::Input::IsPressed(VK_SPACE)) {
	//	auto enemies = GetActors<Enemy>();
	//	RemoveActors();

	//	for (Enemy* enemy : enemies) {
	//		RemoveActors(enemy);
	//	}
	//}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//PLAYER

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
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());


	for (Enemy* actor : sceneActors) {
		actor->Draw(graphics);
	}

}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 << std::endl;

	Player* player = new Player;
	player->Load("player.txt");
	//sceneActors.push_back(player);

	for (size_t i = 0; i < 10; i++) {

		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		Enemy* enemy = dynamic_cast<Enemy*>(actor);

		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(50, 100));
		actor->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		//sceneActors.push_back(actor);

	}
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
