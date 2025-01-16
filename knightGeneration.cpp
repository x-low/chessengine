#include "constants.hpp"
#include <cstdint>
#include <array>

/*
2 UP 1 LEFT no 7, 8, a  << 17
2 UP 1 RIGHT no 7, 8, h << 15
2 DOWN 1 LEFT no 1, 2, a >> 15
2 DOWN 1 RIGHT no 1, 2, h >> 17
2 LEFT 1 UP no 8, a, b << 10
2 LEFT 1 DOWN no 1, a, b >> 6
2 RIGHT 1 UP no 8, g, h << 6
2 RIGHT 1 DOWN no 1, g, h >> 10
*/

static std::array<uint64_t, BOARD_SIZE> knightAttacks;

void  precomputeKnightAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t  sq_bit = 1 << square;
    uint64_t  attacks = 0;

    if (!(sq_bit & RANK_7 || sq_bit & RANK_8)) {
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit << 17);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit << 15);
    }
    if (!(sq_bit & RANK_1 || sq_bit & RANK_2)) {
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit >> 15);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit >> 17);
    }
    if (!(sq_bit & FILE_A || sq_bit & FILE_B)) {
      if (!(sq_bit & RANK_8))
        attacks |= (sq_bit << 10);
      if (!(sq_bit & RANK_1))
        attacks |= (sq_bit >> 6);
    }
    if (!(sq_bit & FILE_G || sq_bit & FILE_H)) {
      if (!(sq_bit & RANK_8))
        attacks |= (sq_bit << 6);
      if (!(sq_bit & RANK_1))
        attacks |= (sq_bit >> 10);
    }
    knightAttacks[square] = attacks;
  }
}
