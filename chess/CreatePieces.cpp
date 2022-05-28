#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "CreatePieces.h"
#include <SDL.h>
#include <SDL_image.h>

std::vector<Piece*> createPieces(SDL_Renderer* renderer) {
    // Load textures
    SDL_Texture* textures[12]{};
    textures[0] = IMG_LoadTexture(renderer, "assets/Rook_b.png");
    textures[1] = IMG_LoadTexture(renderer, "assets/Knight_b.png");
    textures[2] = IMG_LoadTexture(renderer, "assets/Bishop_b.png");
    textures[3] = IMG_LoadTexture(renderer, "assets/Queen_b.png");
    textures[4] = IMG_LoadTexture(renderer, "assets/King_b.png");
    textures[5] = IMG_LoadTexture(renderer, "assets/Pawn_b.png");

    textures[6] = IMG_LoadTexture(renderer, "assets/Rook_w.png");
    textures[7] = IMG_LoadTexture(renderer, "assets/Knight_w.png");
    textures[8] = IMG_LoadTexture(renderer, "assets/Bishop_w.png");
    textures[9] = IMG_LoadTexture(renderer, "assets/Queen_w.png");
    textures[10] = IMG_LoadTexture(renderer, "assets/King_w.png");
    textures[11] = IMG_LoadTexture(renderer, "assets/Pawn_w.png");

    // Add pieces
    std::vector<Piece*> pieces={};
    // Black
    Rook* rookBlack1 = new Rook(0, 0, BLACK, textures[0]);
    pieces.push_back(rookBlack1);

    Knight* knightBlack1 = new Knight(0, 1, BLACK, textures[1]);
    pieces.push_back(knightBlack1);

    Bishop* bishopBlack1 = new Bishop(0, 2, BLACK, textures[2]);
    pieces.push_back(bishopBlack1);

    Queen* queenBlack = new Queen(0, 3, BLACK, textures[3]);
    pieces.push_back(queenBlack);

    King* kingBlack = new King(0, 4, BLACK, textures[4]);
    pieces.push_back(kingBlack);

    Bishop* bishopBlack2 = new Bishop(0, 5, BLACK, textures[2]);
    pieces.push_back(bishopBlack2);

    Knight* knightBlack2 = new Knight(0, 6, BLACK, textures[1]);
    pieces.push_back(knightBlack2);

    Rook* rookBlack2 = new Rook(0, 7, BLACK, textures[0]);
    pieces.push_back(rookBlack2);

    for (size_t i = 0; i < 8; i++)
    {
        Pawn* pawn = new Pawn(1, i, BLACK, textures[5]);
        pawn->canPromote = true;
        pieces.push_back(pawn);
    }


    // White
    for (size_t i = 0; i < 8; i++)
    {
        Pawn* pawn = new Pawn(6, i, WHITE, textures[11]);
        pawn->canPromote = true;
        pieces.push_back(pawn);
    }

    Rook* rookWhite1 = new Rook(7, 0, WHITE, textures[6]);
    pieces.push_back(rookWhite1);

    Knight* knightWhte1 = new Knight(7, 1, WHITE, textures[7]);
    pieces.push_back(knightWhte1);

    Bishop* bishopWhite1 = new Bishop(7, 2, WHITE, textures[8]);
    pieces.push_back(bishopWhite1);

    Queen* queenWhite = new Queen(7, 3, WHITE, textures[9]);
    pieces.push_back(queenWhite);

    King* kingWhite = new King(7, 4, WHITE, textures[10]);
    pieces.push_back(kingWhite);

    Bishop* bishopWhite2 = new Bishop(7, 5, WHITE, textures[8]);
    pieces.push_back(bishopWhite2);

    Knight* knightWhte2 = new Knight(7, 6, WHITE, textures[7]);
    pieces.push_back(knightWhte2);

    Rook* rookWhite2 = new Rook(7, 7, WHITE, textures[6]);
    pieces.push_back(rookWhite2);

    return pieces;
};