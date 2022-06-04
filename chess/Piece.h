#pragma once
#include <SDL.h>
#include "Color.h"
#include "Types.h"
#include <vector>
#include "Coordinate.h"

using namespace std;

class Piece
{
public:
	Piece(int m_row, int m_col, int m_color, SDL_Texture* m_texture, int m_type) {
		row = m_row;
		col = m_col;
		color = m_color;
		texture = m_texture;
		dragPositionX = NULL;
		dragPositionY = NULL;
		canPromote = false;
		wasMoved = false;
		type = m_type;
	};
	int row;
	int col;
	int color;
	int dragPositionX;
	int dragPositionY;
	bool canPromote;
	bool wasMoved;
	int type;
	SDL_Texture* texture;
	virtual vector<Coordinate> getPossibleMoves(vector<Piece*> pieces);
};