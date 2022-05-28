#pragma once
#include <SDL.h>
#include "Color.h"
#include "Types.h"
#include <vector>
#include "Coordinate.h"

using namespace std;

class Piece {
public:
	Piece(int m_row, int m_col, int m_color, SDL_Texture* m_texture) {
		row = m_row;
		col = m_col;
		color = m_color;
		texture = m_texture;
		alive = true;
		dragPositionX = NULL;
		dragPositionY = NULL;
		canPromote = false;
	};
	int row;
	int col;
	int color;
	int dragPositionX;
	int dragPositionY;
	bool alive;
	bool canPromote;
	SDL_Texture* texture;
	virtual vector<Coordinate> getPossibleMoves(vector<Piece*> pieces);
private:
	
};