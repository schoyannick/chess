#pragma once
#include <iostream>
#include <vector>

#include "Piece.h"
#include "Coordinate.h"
#include "Types.h"
#include "GetPieceAtPosition.h"

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

		// Check for castle
		for (auto& piece : pieces) {
			if (piece->type == ROOK && !wasMoved && piece->color == color && !piece->wasMoved) {
				// Queen side long castle
				if (
					piece->col == 0 &&
					!GetPieceAtPosition(piece->row, piece->col + 1, pieces)
					&& !GetPieceAtPosition(piece->row, piece->col + 2, pieces)
					&& !GetPieceAtPosition(piece->row, piece->col + 3, pieces)
					) {
					coordinates.push_back({ 2, piece->row });
				}
				// King side short castle
				else if (
					piece->col == 7 &&
					!GetPieceAtPosition(piece->row, piece->col - 1, pieces)
					&& !GetPieceAtPosition(piece->row, piece->col - 2, pieces)
					) {
					coordinates.push_back({ 6, piece->row });
				}
			}
		}

		return coordinates;
	}
};