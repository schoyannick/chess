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
	m_promotionPiece = nullptr;
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
	if (!m_promotionPiece) {
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
		int row = m_draggingPiece->dragPositionY / (height / 8);
		int col = m_draggingPiece->dragPositionX / (width / 8);

		bool canDrop = false;

		for (auto& move : m_possibleMoves) {
			if (move.col == col && move.row == row) {
				canDrop = true;
				break;
			}
		}

		if (canDrop) {
			int deleteIndex = -1;
			for (std::size_t i = 0; i < m_pieces.size(); ++i) {
				if (m_pieces[i]->color != m_draggingPiece->color && m_pieces[i]->row == row && m_pieces[i]->col == col) {
					deleteIndex = i;
				}
			}

			if (deleteIndex > -1) {
				m_pieces.erase(m_pieces.begin() + deleteIndex);
			}

			// Check for promotion
			if (m_draggingPiece->canPromote && ((row == 0 && m_draggingPiece->color == WHITE) || row == 7 && m_draggingPiece->color == BLACK)) {
				m_promotionPiece = m_draggingPiece;
			}

			// Check for castling
			if (m_draggingPiece->type == KING && !m_draggingPiece->wasMoved && abs(col - m_draggingPiece->col) > 1) {
				if (col == 2) {
					Piece* rook = GetPieceAtPosition(m_draggingPiece->row, 0, m_pieces);
					if (rook && !rook->wasMoved && rook->color == m_draggingPiece->color) {
						rook->col = 3;
						rook->wasMoved = true;
					}
				}
				else if (col == 6) {
					Piece* rook = GetPieceAtPosition(m_draggingPiece->row, 7, m_pieces);
					if (rook && !rook->wasMoved && rook->color == m_draggingPiece->color) {
						rook->col = 5;
						rook->wasMoved = true;
					}
				}
			}

			m_draggingPiece->row = row;
			m_draggingPiece->col = col;
			m_draggingPiece->wasMoved = true;

			m_playerTurn = m_playerTurn == WHITE ? BLACK : WHITE;
		}
	}
}

void Application::drawBoard() {
	bool white = false;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			SDL_Rect rect{};
			rect.x = col * width / 8;
			rect.y = row * height / 8;
			rect.w = width / 8;
			rect.h = height / 8;

			if (white)
			{
				SDL_SetRenderDrawColor(m_renderer, 186, 202, 68, 255);
			}
			else {
				SDL_SetRenderDrawColor(m_renderer, 118, 150, 86, 255);
			}
			SDL_RenderFillRect(m_renderer, &rect);

			if (m_draggingPiece) {
				int draggingRow = m_draggingPiece->dragPositionY / (height / 8);
				int draggingCol = m_draggingPiece->dragPositionX / (width / 8);
				if (draggingRow == row && draggingCol == col) {
					SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
					SDL_RenderDrawRect(m_renderer, &rect);
				}
			}

			white = !white;
		}
		white = !white;
	}
}

void Application::drawPieces() {
	for (auto piece : m_pieces) {
		// Skip dragging piece to draw it on top
		if (piece == m_draggingPiece) {
			continue;
		}
		SDL_Rect rect{};
		rect.w = width / 8;
		rect.h = height / 8;
		rect.x = piece->col * width / 8;
		rect.y = piece->row * height / 8;
		SDL_RenderCopy(m_renderer, piece->texture, NULL, &rect);
	}

	// Draw dragging piece
	if (m_draggingPiece) {
		SDL_Rect rect{};
		rect.w = width / 8;
		rect.h = height / 8;
		if (m_draggingPiece->dragPositionX != NULL) {
			rect.x = m_draggingPiece->dragPositionX - width / 16;
			rect.y = m_draggingPiece->dragPositionY - height / 16;
		}
		else {
			rect.x = m_draggingPiece->col * width / 8;
			rect.y = m_draggingPiece->row * height / 8;
		}

		SDL_RenderCopy(m_renderer, m_draggingPiece->texture, NULL, &rect);
	}
}

void Application::drawPromotion()
{
	if (m_promotionPiece) {
		SDL_Rect rect = {};
		rect.w = width / 2 + 20;
		rect.h = height / 8 + 10;
		rect.x = 100;
		if (m_promotionPiece->row == 0) {
			rect.y = height / 8 + 10;
		}
		else {
			rect.y = height / 8 * 7 - 10;
		}
		SDL_RenderFillRect(m_renderer, &rect);
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(m_renderer, &rect);
	}
}

void Application::render() {
	SDL_RenderClear(m_renderer);

	// Draw the board
	drawBoard();

	// Draw the pieces
	drawPieces();

	// Draw possible moves
	drawPossibleMoves();

	// Draw promotion
	drawPromotion();

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
