#include "core.h"
#include "Game.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <time.h>

Game game;

bool Update(float dt)
{
	bool quit = game.Update(dt);

	g_particleSystem.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
	g_particleSystem.Draw(graphics);
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	g_audioSystem.Startup();
	g_particleSystem.Startup();

	game.Initialize();

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
	g_audioSystem.Shutdown();
}
