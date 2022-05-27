#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>
#include "Coordinate.h"

using namespace std;

class Pawn : public Piece {
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};

		vector<Coordinate> directs = {};
		vector<Coordinate> enemies = {};

		if (color == WHITE) {
			// One up
			Coordinate c = { 0, -1 };
			directs.push_back(c);

			// Two up
			if (row == 6) {
				Coordinate c = { 0, -2 };
				directs.push_back(c);
			}

			// Check for enemies
		}
		else {
			// One down
			Coordinate c = { 0, 1 };
			directs.push_back(c);

			// Two down
			if (row == 1) {
				Coordinate c = { 0, 2 };
				directs.push_back(c);
			}
		}

		for (auto& direct : directs) {
			Coordinate cord = { col + direct.col, row + direct.row };
			coordinates.push_back(cord);
		}

		return coordinates;
	}
};