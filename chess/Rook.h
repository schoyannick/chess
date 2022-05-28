#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Piece.h" 
#include "Coordinate.h"
#include "GetAllCoordinates.h"

class Rook : public Piece {
	using Piece::Piece;

	vector<Coordinate> getPossibleMoves(vector<Piece*> pieces) {
		vector<Coordinate> coordinates = {};
		vector<Coordinate> directs = {
			{ 1, 0 },
			{ -1, 0},
			{ 0, 1 },
			{ 0, - 1 }
		};

		vector<CoordPiece> allCords = getAllCoordinates(pieces);

		for (auto& direct : directs) {
			Coordinate newCoord = {};
			newCoord.col = direct.col + col;
			newCoord.row = direct.row + row;

			while (newCoord.col >= 0 && newCoord.col < 8 && newCoord.row >= 0 && newCoord.row < 8) {
				bool find = false;
				for (auto& coordPiece : allCords) {
					if (coordPiece.cord.row == newCoord.row && coordPiece.cord.col == newCoord.col) {
						if (coordPiece.piece->color == color) {
							find = true;
							break;
						}
						else {
							find = true;
							coordinates.push_back(newCoord);
							break;
						}
					}
				}
				
				if (find) {
					newCoord.row = 100;
					continue;
				}

				coordinates.push_back(newCoord);
				if (direct.row > 0) {
					newCoord.row++;
				}
				else if (direct.row < 0) {
					newCoord.row--;
				}
				else if (direct.col > 0) {
					newCoord.col++;
				}
				else {
					newCoord.col--;
				}
			}
		}

		return coordinates;
	}
};