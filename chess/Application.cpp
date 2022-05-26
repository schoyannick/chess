#include "Application.h"
#include <iostream>

SDL_Texture* texture;
SDL_Rect destR;

Application::Application() {
    isRunning = true;
    window = nullptr;
    renderer = nullptr;
    width = 800;
    height = 800;
}

Application::~Application() {

}

void Application::init(const char* title, int x, int y)
{
    std::cout << "Init" << std::endl;

    window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);

    texture = IMG_LoadTexture(renderer, "assets/Chess_bdt60.png");
}

void Application::handleEvents() {
    SDL_Event sdlEvent;

    SDL_WaitEvent(&sdlEvent);

    switch (sdlEvent.type)
    {
        case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

void Application::update() {
    destR.h = 100;
    destR.w = 100;
}

void drawBoard(SDL_Renderer* renderer, int width, int height) {
    bool white = false;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            SDL_Rect r{};
            r.x = col * width / 8;
            r.y = row * height / 8;
            r.w = width / 8;
            r.h = height / 8;

            if (white)
            {
                SDL_SetRenderDrawColor(renderer, 186, 202, 68, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
            }
            SDL_RenderFillRect(renderer, &r);
            white = !white;
        }
        white = !white;
    }
}

void Application::render() {
    SDL_RenderClear(renderer);

    // Draw the board
    drawBoard(renderer, width, height);

    // Draw the pieces
    SDL_RenderCopy(renderer, texture, NULL, &destR);

    SDL_RenderPresent(renderer);
}

bool Application::running() {
    return isRunning;
}

void Application::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
