#include "GetPieceAtPosition.h"

Piece* GetPieceAtPosition(int row, int col, vector<Piece*> pieces)
{
	for (auto& piece : pieces) {
		if (piece->row == row && piece->col == col) {
			return piece;
		}
	}

	return nullptr;
}
