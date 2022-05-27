#include "Application.h"
#include <iostream>
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "CreatePieces.h"

Application::Application() {
    m_isRunning = true;
    m_window = nullptr;
    m_renderer = nullptr;
    width = 800;
    height = 800;
    m_playerTurn = WHITE;
    m_draggingPiece = nullptr;
    m_possibleMoves = {};
}

Application::~Application() {

}

void Application::init(const char* title, int x, int y)
{
    std::cout << "Init" << std::endl;

    m_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_RESIZABLE);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    SDL_SetRenderDrawColor(m_renderer, 238, 238, 210, 255);

    m_pieces = createPieces(m_renderer);
}

void Application::handleMouseDownEvent(SDL_Event sdlEvent)
{
    int x = sdlEvent.button.x;
    int y = sdlEvent.button.y;

    int row = y / (height / 8);
    int col = x / (width / 8);

    bool found = false;

    for (auto piece : m_pieces) {
        if (piece->color == m_playerTurn && piece->row == row && piece->col == col) {
            m_draggingPiece = piece;
            found = true;
            break;
        }
    }

    if (!found) {
        m_draggingPiece = nullptr;
    }
}

void Application::handleEvents() {
    SDL_Event sdlEvent;

    SDL_WaitEvent(&sdlEvent);

    switch (sdlEvent.type)
    {
        case SDL_QUIT:
            m_isRunning = false;
        break;
        case SDL_MOUSEBUTTONDOWN:
            handleMouseDownEvent(sdlEvent);
            break;
        case SDL_MOUSEBUTTONUP:
            if (m_draggingPiece) {
                dropPiece();

                m_draggingPiece->dragPositionX = NULL;
                m_draggingPiece->dragPositionY = NULL;
                m_draggingPiece = nullptr;
            }
            m_possibleMoves = {};
            break;
        case SDL_MOUSEMOTION:
            if (m_draggingPiece) {
                m_draggingPiece->dragPositionX = sdlEvent.motion.x;
                m_draggingPiece->dragPositionY = sdlEvent.motion.y;
            }
            break;
    default:
        break;
    }
}

void Application::update() {
    if (m_draggingPiece) {
        m_possibleMoves = m_draggingPiece->getPossibleMoves(m_pieces);
    }
}

void draw_circle(SDL_Point center, int radius, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

void Application::drawPossibleMoves()
{
    for (auto& move : m_possibleMoves) {
        SDL_Point point = { (move.col * width / 8) + (width / 16), (move.row * height / 8) + (height / 16) };
        SDL_Color color = { 255, 0, 0 };
        draw_circle(point, 20, color, m_renderer);
    }
}

void Application::dropPiece()
{
    if (m_draggingPiece && m_draggingPiece->dragPositionX != NULL && m_draggingPiece->dragPositionY != NULL) {
        std::cout << m_draggingPiece->dragPositionY << " " << m_draggingPiece->dragPositionX << std::endl;
        int row = m_draggingPiece->dragPositionY / (height / 8);
        int col = m_draggingPiece->dragPositionX / (width / 8);

        std::cout << row << " " << col << std::endl;

        bool canDrop = false;

        for (auto& move : m_possibleMoves) {
            if (move.col == col && move.row == row) {
                canDrop = true;
                break;
            }
        }

        if (canDrop) {
            m_draggingPiece->row = row;
            m_draggingPiece->col = col;

            if (m_playerTurn == WHITE) {
                m_playerTurn = BLACK;
            }
            else {
                m_playerTurn = WHITE;
            }
        }
    }
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

void drawPieces(SDL_Renderer* renderer, std::vector<Piece*> pieces, int width, int height) {
    for (auto piece : pieces) {
        if (piece->texture) {
            SDL_Rect rect{};
            rect.w = width / 8;
            rect.h = height / 8;
            if (piece->dragPositionX != NULL && piece->dragPositionY != NULL) {
                rect.x = piece->dragPositionX - width / 16;
                rect.y = piece->dragPositionY - height / 16;
            }
            else {
                rect.x = piece->col * width / 8;
                rect.y = piece->row * height / 8;
            }
           
            SDL_RenderCopy(renderer, piece->texture, NULL, &rect);
        }
    }
}

void Application::render() {
    SDL_RenderClear(m_renderer);

    // Draw the board
    drawBoard(m_renderer, width, height);

    // Draw possible moves
    drawPossibleMoves();

    // Draw the pieces
    drawPieces(m_renderer, m_pieces, width, height);

    SDL_RenderPresent(m_renderer);
}

bool Application::running() {
    return m_isRunning;
}

void Application::clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}
