#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Piece.h"
#include "Coordinate.h"

class CoordPiece {
public:
	Coordinate cord;
	Piece* piece;
};

vector<CoordPiece> getAllCoordinates(vector<Piece*> pieces);