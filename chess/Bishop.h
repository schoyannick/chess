#pragma once
#include "Piece.h"
#include <iostream>
#include <vector>
#include "Coordinate.h"

class Bishop : public Piece {
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};
		vector<Coordinate> directs = {
			{ -1, -1 },
			{ 1, -1 },
			{ 1, 1 },
			{ -1, 1 }
		};

		for (auto& direct : directs) {
			Coordinate newCoord = {};
			newCoord.row = direct.row + row;
			newCoord.col = direct.col + col;

			while (newCoord.col >= 0 && newCoord.col < 8 && newCoord.row >= 0 && newCoord.row < 8) {
				bool found = false;

				for (auto& piece : pieces) {
					if (piece->col == newCoord.col && piece->row == newCoord.row) {
						found = true;
						if (piece->color != color) {
							coordinates.push_back(newCoord);
						}
						break;
					}
				}

				if (found) {
					break;
				}

				coordinates.push_back(newCoord);

				newCoord.row += direct.row;
				newCoord.col += direct.col;
			}
		}

		return coordinates;
	}
};