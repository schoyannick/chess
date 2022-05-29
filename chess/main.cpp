#include "SDL.h"
#include "Application.h"
#undef main

int main() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Application* app = new Application();

	app->init("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	while (app->running()) {
		frameStart = SDL_GetTicks();

		app->handleEvents();
		app->update();
		app->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	app->clean();

	return 0;
}