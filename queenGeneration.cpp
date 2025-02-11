#include "moveGeneration.hpp"

static std::array<uint64_t, BOARD_SIZE> queenAttacks;

void  precomputeQueenAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++)
    queenAttacks[square] = rookAttacks[square] | bishopAttacks[square];
}
