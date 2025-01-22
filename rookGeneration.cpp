#include "constants.hpp"
#include <array>
#include <vector>

static std::array<uint64_t, BOARD_SIZE> rookAttacks;

void  precomputeRookAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t sq_bit = 1ULL << square;
    uint64_t attacks = 0ULL;

    for (int up_shift = 8; square + up_shift < BOARD_SIZE; up_shift += 8)
      attacks |= (sq_bit << up_shift);
    for (int down_shift = 8; square - down_shift >= 0; down_shift += 8)
      attacks |= (sq_bit >> down_shift);
    for (int left_shift = 1; (square % 8) - left_shift >= 0; left_shift++)
      attacks |= (sq_bit >> left_shift);
    for (int right_shift = 1; (square % 8) + right_shift <= 7; right_shift++)
      attacks |= (sq_bit << right_shift);

    rookAttacks[square] = attacks;
  }
}

std::vector<Move> generateRookMoves(
    uint64_t rooks,
    uint64_t ownPieces,
    uint64_t opponentPieces
) {
  while (rooks) {
    int square = __builtin_ctzll(rooks); // get LSB
    uint64_t attacks = rookAttacks[square];
    while (attacks) {
