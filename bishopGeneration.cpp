#include "constants.hpp"
#include <array>
#include <vector>

static std::array<uint64_t, BOARD_SIZE> bishopAttacks;

void  precomputeBishopAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t sq_bit = 1ULL << square;
    uint64_t attacks = 0ULL;

    for (int NW_shift = 7;
        (square + NW_shift) % 7 && square + NW_shift < BOARD_SIZE; // doesn't end up on H
        NW_shift += 7)
      attacks |= (sq_bit << NW_shift);
    for (int NE_shift = 9;
        (square + NE_shift) % 8 && square + NE_shift < BOARD_SIZE; // doesn't end up on A
        NE_shift += 9)
      attacks |= (sq_bit << NE_shift);
    for (int SW_shift = 9;
        (square - SW_shift) % 7 && square - SW_shift >= 0; // doesn't end up on H
        SW_shift += 9)
      attacks |= (sq_bit >> SW_shift);
    for (int SE_shift = 7;
        (square - SE_shift) % 8 && square - SE_shift >= 0; // doesn't end up on A
        SE_shift += 7)
      attacks |= (sq_bit >> SE_shift);
    bishopAttacks[square] = attacks;
  }
}

std::vector<Move> generateBishopMoves(
    uint64_t bishops,
    uint64_t ownPieces,
    uint64_t opponentPieces
) {
  while (bishops) {
    int square = __builtin_ctzll(bishops); // get LSB
    uint64_t attacks = bishopAttacks[square];
    while (attacks) {
