#pragma once
#include <iostream>
#include <vector>
#include "Piece.h" 
#include "Coordinate.h"

class Rook : public Piece
{
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};
		vector<Coordinate> directs = {
			{ 1, 0 },
			{ -1, 0 },
			{ 0, 1 },
			{ 0, -1 }
		};

		for (auto& direct : directs) {
			Coordinate newCoord = {};
			newCoord.col = direct.col + col;
			newCoord.row = direct.row + row;

			while (newCoord.col >= 0 && newCoord.col < 8 && newCoord.row >= 0 && newCoord.row < 8) {
				bool found = false;
				for (auto& piece : pieces) {
					if (piece->row == newCoord.row && piece->col == newCoord.col) {
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