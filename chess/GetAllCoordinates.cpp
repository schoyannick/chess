#include "GetAllCoordinates.h"
#include <iostream>
#include <vector>

vector<CoordPiece> getAllCoordinates(vector<Piece*> pieces)
{
	vector<CoordPiece> coords = {};

	for (auto& piece : pieces) {
		if (piece->alive) {
			CoordPiece c = {};
			c.cord.col = piece->col;
			c.cord.row = piece->row;
			c.piece = piece;
			coords.push_back(c);
		}
	}

	return coords;
}
