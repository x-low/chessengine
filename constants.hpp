#pragma once

#include <cstdint>

const uint64_t  FILE_A = 0x0101010101010101;
const uint64_t  FILE_H = 0x8080808080808080;
const uint64_t  RANK_1 = 0x00000000000000FF;
const uint64_t  RANK_2 = 0x000000000000FF00;
const uint64_t  RANK_7 = 0x00FF000000000000;
const uint64_t  RANK_8 = 0xFF00000000000000;

const int       BOARD_SIZE = 64;

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
