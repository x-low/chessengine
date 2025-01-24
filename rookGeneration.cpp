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
    uint64_t allPieces
) {
  std::vector<Move> moves;
  int blocker;
  int square;
  uint64_t attacks;
  uint64_t blockerSquare;
  while (rooks) {
    square = __builtin_ctzll(rooks); // get LSB
    attacks = rookAttacks[square];

    while (attacks) {
      uint64_t upRay = attacks & 0xFFFFFFFFFFFFFF00ULL << square; // mask for squares above rook
      blocker = upRay & allPieces;
      if (blocker) {
        blockerSquare = __builtin_ctzll(blocker);
        attacks &= ~(rookAttacks[blockerSquare] & upRay); // ray stops at contact with blocker
      }

      uint64_t downRay = attacks & 0x00FFFFFFFFFFFFFFULL >> (63 - square); // mask for squares below rook
      blocker = downRay & allPieces;
      if (blocker) {
        blockerSquare = 63 - __builtin_clzll(blocker);
        attacks &= ~(rookAttacks[blockerSquare] & downRay);
      }

      // mask for rook's file and all files to the right, -1 to set all bits to the left of rook's file
      uint64_t leftRay = attacks & ((0x0101010101010101ULL << (square % 8)) - 1);
      blocker = leftRay & allPieces;
      if (blocker) {
        blockerSquare = 63 - __builtin_clzll(blocker);
        attacks &= ~(rookAttacks[blockerSquare] & leftRay);
      }

      // similar to leftRay but starting one file to the right of the rook
      uint64_t rightRay = attacks & ~((0x0202020202020202ULL << (square % 8)) - 1);
      blocker = rightRay & allPieces;
      if (blocker) {
        blockerSquare = __builtin_ctzll(blocker);
        attacks &= ~(rookAttacks[blockerSquare] & rightRay);
      }

      // friendly pieces are not captured
      //attacks &= ~ownPieces;
