#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>
#include "Coordinate.h"

class Knight : public Piece {
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};

		vector<Coordinate> directs = {
			{ -2, -1 },
			{ -1, -2 },
			{ 1, -2 },
			{ 2, -1 },
			{ 2, 1 },
			{ 1, 2 },
			{ -1, 2 },
			{ -2, 1 }
		};

		for (auto& direct : directs) {
			Coordinate newCoord = {};
			newCoord.col = direct.col + col;
			newCoord.row = direct.row + row;

			if (newCoord.row >= 0 && newCoord.row < 8 && newCoord.col >= 0 && newCoord.col < 8) {
				bool foundFriendlyPiece = false;
				for (auto& piece : pieces) {
					if (piece->color == color && piece->row == newCoord.row && piece->col == newCoord.col) {
						foundFriendlyPiece = true;
					}
				}

				if (!foundFriendlyPiece) {
					coordinates.push_back(newCoord);
				}
			}
		}

		return coordinates;
	}
};