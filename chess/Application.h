#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <set>
#include "Piece.h"
#include <vector>
#include "Coordinate.h"

using namespace std;

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

	void handleMouseDownEvent(SDL_Event sdlEvent);
	void drawPossibleMoves();
	void dropPiece();

	int width;
	int height;

private:
	vector<Piece*> m_pieces;
	Piece* m_draggingPiece;
	vector<Coordinate> m_possibleMoves;
	color m_playerTurn;
	bool m_isRunning;
	SDL_Window *m_window;
	SDL_Renderer* m_renderer;
};