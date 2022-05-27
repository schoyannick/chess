#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Piece.h"

std::vector<Piece*> createPieces(SDL_Renderer* renderer);