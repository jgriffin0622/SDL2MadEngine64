
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include "src/Core/Engine.h"
#include "src/Timer/Timer.h"

int main(int argc, char* argv[]) {

	Engine::GetInstance()->Init();

	while (Engine::GetInstance()->IsRunning()) {
	
		Engine::GetInstance()->Events();

		Engine::GetInstance()->Update();

		Engine::GetInstance()->Render();
		Timer::GetInstance()->Tick();
	}
	Engine::GetInstance()->Cleanup();
	Engine::GetInstance()->Quit();

	return 0;
}