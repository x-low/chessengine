#pragma once

#include <cstdint>
#include "using.hpp"

enum Square {
    a1 = 0, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    NO_SQUARE = 64 // Invalid square or error
};

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
