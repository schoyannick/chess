#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>
#include "Coordinate.h"

class Queen : public Piece {
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves() {
		vector<Coordinate> coordinates = {};

		return coordinates;
	}
};