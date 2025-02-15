#include "moveGeneration.hpp"
#include "bitboard.hpp"

static std::array<uint64_t, BOARD_SIZE> queenAttacks;
extern std::array<uint64_t, BOARD_SIZE> bishopAttacks;
extern std::array<uint64_t, BOARD_SIZE> rookAttacks;

void  precomputeQueenAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++)
    queenAttacks[square] = rookAttacks[square] | bishopAttacks[square];
}

std::vector<Move> generateQueenMoves(
    uint64_t queens,
    uint64_t ownPieces,
    uint64_t allPieces
) {
  std::vector<Move> moves;
  int square;
  uint64_t attacks;
  uint64_t blocker;
  uint64_t blockerSquare;

  while (queens) {
    square = __builtin_ctzll(queens);
    attacks = queenAttacks[square];

    uint64_t upRay = attacks & 0xFFFFFFFFFFFFFF00ULL << square;
    blocker = upRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      upRay = queenAttacks[blockerSquare] & 0xFFFFFFFFFFFFFF00ULL << blockerSquare;
      attacks &= ~upRay;
    }

    uint64_t downRay = attacks & 0x00FFFFFFFFFFFFFFULL >> (63 - square);
    blocker = downRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      downRay = queenAttacks[blockerSquare] & 0x00FFFFFFFFFFFFFFULL >> (63 - blockerSquare);
      attacks &= ~downRay;
    }

    uint64_t leftRay = attacks & 0xFF00000000000000ULL >> (63 - square);
    blocker = leftRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      leftRay = queenAttacks[blockerSquare] & 0xFF00000000000000ULL >> (63 - blockerSquare);
      attacks &= ~leftRay;
    }

    uint64_t rightRay = attacks & 0x00000000000000FFULL << square;
    blocker = rightRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      rightRay = queenAttacks[blockerSquare] & 0x00000000000000FFULL << blockerSquare;
      attacks &= ~rightRay;
    }

    uint64_t neRay = attacks & (0x8040201008040201ULL << square);
    blocker = neRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      neRay = queenAttacks[blockerSquare] & (0x8040201008040201ULL << blockerSquare);
      attacks &= ~neRay;
    }

    uint64_t nwRay = attacks & (0x0102040810204080ULL << square);
    blocker = nwRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      nwRay = queenAttacks[blockerSquare] & (0x0102040810204080ULL << blockerSquare);
      attacks &= ~nwRay;
    }

    uint64_t swRay = attacks & (0x8040201008040201ULL >> (63 - square));
    blocker = swRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      swRay = queenAttacks[blockerSquare] & (0x8040201008040201ULL >> (63 - blockerSquare));
      attacks &= ~swRay;
    }

    uint64_t seRay = attacks & (0x0102040810204080ULL >> (63 - square));
    blocker = seRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      seRay = queenAttacks[blockerSquare] & (0x0102040810204080ULL >> (63 - blockerSquare));
      attacks &= ~seRay;
    }

    attacks &= ~ownPieces;

    while (attacks) {
      moves.push_back({square, __builtin_ctzll(attacks), '\0'});
      attacks &= attacks - 1;
    }
    queens &= queens - 1;
  }
  return (moves);
}
