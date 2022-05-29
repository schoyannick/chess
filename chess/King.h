#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>
#include "Coordinate.h"

class King : public Piece
{
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};
		vector<Coordinate> directs = {
			{ -1, -1 },
			{ 0, -1 },
			{ 1, -1 },
			{ 1, 0 },
			{ 1, 1 },
			{ 0, 1 },
			{ -1, 0 },
			{ -1, 1 }
		};

		for (auto& direct : directs) {
			Coordinate newCoord = { direct.col + col, direct.row + row };

			bool foundFriendly = false;

			for (auto& piece : pieces) {
				if (piece->col == newCoord.col && piece->row == newCoord.row && piece->color == color) {
					foundFriendly = true;
					break;
				}
			}

			if (!foundFriendly) {
				coordinates.push_back(newCoord);
			}
		}

		return coordinates;
	}
};