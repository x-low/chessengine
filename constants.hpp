#pragma once

#include <cstdint>

const uint64_t  FILE_A = 0x0101010101010101;
const uint64_t  FILE_B = 0x0202020202020202;
const uint64_t  FILE_C = 0x0404040404040404;
const uint64_t  FILE_D = 0x0808080808080808;
const uint64_t  FILE_E = 0x1010101010101010;
const uint64_t  FILE_F = 0x2020202020202020;
const uint64_t  FILE_G = 0x4040404040404040;
const uint64_t  FILE_H = 0x8080808080808080;
const uint64_t  RANK_1 = 0x00000000000000FF;
const uint64_t  RANK_2 = 0x000000000000FF00;
const uint64_t  RANK_3 = 0x0000000000FF0000;
const uint64_t  RANK_4 = 0x00000000FF000000;
const uint64_t  RANK_5 = 0x000000FF00000000;
const uint64_t  RANK_6 = 0x0000FF0000000000;
const uint64_t  RANK_7 = 0x00FF000000000000;
const uint64_t  RANK_8 = 0xFF00000000000000;

const int       BOARD_SIZE = 64;

enum Square {
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NO_SQUARE = 64 // Invalid square or error
};

struct Move {
    int fromSquare{};
    int toSquare{};
    int promotion{};
};
