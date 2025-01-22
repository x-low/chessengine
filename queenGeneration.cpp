#include "constants.hpp"
#include <array>
#include <vector>

static std::array<uint64_t, BOARD_SIZE> queenAttacks;

void  precomputeQueenAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t sq_bit = 1ULL << square;
    uint64_t attacks = 0ULL;

    // from rook moves
    for (int N_shift = 8; square + N_shift < BOARD_SIZE; N_shift += 8)
      attacks |= (sq_bit << N_shift);
    for (int S_shift = 8; square - S_shift >= 0; S_shift += 8)
      attacks |= (sq_bit >> S_shift);
    for (int W_shift = 1; (square % 8) - W_shift >= 0; W_shift++)
      attacks |= (sq_bit >> W_shift);
    for (int E_shift = 1; (square % 8) + E_shift <= 7; E_shift++)
      attacks |= (sq_bit << E_shift);

    // from bishop moves
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

    queenAttacks[square] = attacks;
  }
}

std::vector<Move> generateQueenMoves(
    uint64_t queens,
    uint64_t ownPieces,
    uint64_t opponentPieces
) {
  while (queens) {
    int square = __builtin_ctzll(queens); // get LSB
    uint64_t attacks = queenAttacks[square];
    while (attacks) {
