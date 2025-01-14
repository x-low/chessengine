#pragma once

#include <cstdint>
#include "using.hpp"
#include "constants.hpp"

// Square conversion functions

std::string squareToString(Square square);
Square  stringToSquare(const std::string& str);

struct Bitboard {
  uint64_t	pawns = 0;
  uint64_t	knights = 0;
  uint64_t	bishops = 0;
  uint64_t	rooks = 0;
  uint64_t	queens = 0;
  uint64_t	kings = 0;
  uint64_t	whitePieces = 0;
  uint64_t	blackPieces = 0;
};

Bitboard	setStartingPosition();
void		printBitboard(uint64_t bitboard);

void  		setBit(uint64_t &bitboard, int square); // Place piece
void  		clearBit(uint64_t &bitboard, int square); // Remove piece
void  		toggleBit(uint64_t &bitboard, int square); // Places/removes if absent/present
bool  		isBitSet(uint64_t bitboard, int square); // Check occupancy
int  		countBits(uint64_t bitboard); // Count pieces
int  		getLSBIndex(uint64_t bitboard); // Least significant bit
int  		getMSBIndex(uint64_t bitboard); // Most significant bit
