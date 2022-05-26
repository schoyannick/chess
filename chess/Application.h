#include <SDL.h>
#include <SDL_image.h>

class Application {
public:
	Application();
	~Application();

	void init(const char* title, int x, int y);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	int width;
	int height;

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer* renderer;
};