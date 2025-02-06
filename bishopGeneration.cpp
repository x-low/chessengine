#include "constants.hpp"
#include <array>
#include <vector>
#include "bitboard.hpp"

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
    uint64_t allPieces
) {
  std::vector<Move> moves;
  int square;
  uint64_t attacks;
  uint64_t blocker;
  uint64_t blockerSquare;

  while (bishops) {
    square = __builtin_ctzll(bishops); // get LSB
    attacks = bishopAttacks[square];

    uint64_t neRay = attacks & (0x8040201008040201ULL << square);
    blocker = neRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      neRay &= ~(0xFFFFFFFFFFFFFFFFULL << blockerSquare);
      attacks &= ~neRay;
    }

    uint64_t nwRay = attacks & (0x0102040810204080ULL << square);
    blocker = nwRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      nwRay &= ~(0xFFFFFFFFFFFFFFFFULL << blockerSquare);
      attacks &= ~nwRay;
    }

    uint64_t seRay = attacks & (0x8040201008040201ULL >> (63 - square));
    blocker = seRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      seRay &= (1ULL << (blockerSquare + 1)) -1;
      attacks &= ~seRay;
    }

    uint64_t swRay = attacks & (0x0102040810204080ULL >> (63 - square));
    blocker = swRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      swRay &= (1ULL << (blockerSquare + 1)) - 1;
      attacks &= ~swRay;
    }

    attacks &= ~ownPieces;

    while (attacks) {
      moves.push_back({square, __builtin_ctzll(attacks), '\0'});
      attacks &= attacks - 1;
    }
    bishops &= bishops - 1;
  }
  return (moves);
}

#include "bitboard.hpp"
int main(int, char**argv) {
  precomputeBishopAttacks();

  int bishopSquare = stringToSquare(argv[1]);
  int allySquare = stringToSquare(argv[2]);
  int oppSquare = stringToSquare(argv[3]);
  std::cout << "Square: " << bishopSquare << std::endl;
  std::cout << "Ally: " << allySquare << std::endl;
  std::cout << "Opp: " << oppSquare << std::endl;
  uint64_t bishopBoard = 1ULL << bishopSquare;
  uint64_t ownPieces = 1ULL << allySquare;
  uint64_t opponentPieces = 1ULL << oppSquare;
  uint64_t allPieces = ownPieces | opponentPieces;

  std::vector<Move> moves = generateBishopMoves(bishopBoard, ownPieces, allPieces);

  std::cout << "Bishop moves from " << squareToString (bishopSquare) << std::endl;
  std::cout << "Ally blocking on " << squareToString (std::atoi(argv[2])) << std::endl;
  for (Move move: moves)
    std::cout << squareToString(move.toSquare) << std::endl;
  return (0);
}
