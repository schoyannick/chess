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

		// Move 1 or 2 up/down
		Coordinate c1 = {};
		Coordinate c2 = { -100, -100 };

		// Enemy
		Coordinate Enemey1 = {};
		Coordinate Enemey2 = {};

		if (color == WHITE) {
			// One up
			c1 = { 0, -1 };

			// Two up
			if (row == 6) {
				c2 = { 0, -2 };
			}

			Enemey1 = { -1, -1 };
			Enemey2 = { 1, -1 };
		}
		else {
			// One down
			c1 = { 0, 1 };

			// Two down
			if (row == 1) {
				c2 = { 0, 2 };
			}

			Enemey1 = { -1, 1 };
			Enemey2 = { 1, 1 };
		}

		bool addC1 = true;
		bool addC2 = true;

		// Check for enemies
		for (auto& piece : pieces) {
			if (!piece->alive) {
				continue;
			}

			if (piece->color != color && row + Enemey1.row == piece->row && col + Enemey1.col == piece->col) {
				directs.push_back(Enemey1);
			}
			else if (piece->color != color && row + Enemey2.row == piece->row  && col + Enemey2.col == piece->col) {
				directs.push_back(Enemey2);
			}

			if (row + c1.row == piece->row && col + c1.col == piece->col) {
				addC1 = false;
			}

			if (row + c2.row == piece->row&& col + c2.col == piece->col) {
				addC2 = false;
			}
		}

		if (addC1) {
			directs.push_back(c1);
		}

		if (addC2) {
			directs.push_back(c2);
		}

		for (auto& direct : directs) {
			Coordinate cord = { col + direct.col, row + direct.row };
			if (cord.row >= 0 && cord.row < 8 && cord.col >= 0 && cord.col < 8) {
				coordinates.push_back(cord);
			}
		}

		return coordinates;
	}
};