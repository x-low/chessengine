#include "constants.hpp"
#include <array>
#include <vector>

static std::array<uint64_t, BOARD_SIZE> bishopAttacks;

void  precomputeBishopAttacks() {
  int rank;
  int file;
  uint64_t attacks = 0ULL;

  for (int square = 0; square < BOARD_SIZE; square++) {
    attacks = 0ULL;
    rank = square / 8;
    file = square % 8;

    // Northeast
    for (int r = rank + 1, f = file + 1; r < 8 && f < 8; r++, f++)
      attacks |= (1ULL << (r * 8 + f));

    // Northwest
    for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; r++, f--)
      attacks |= (1ULL << (r * 8 + f));

    // Southeast
    for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; r--, f++)
      attacks |= (1ULL << (r * 8 + f));

    // Southwest
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--)
      attacks |= (1ULL << (r * 8 + f));

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
      neRay = bishopAttacks[blockerSquare] & (0x8040201008040201ULL << blockerSquare);
      attacks &= ~neRay;
    }

    uint64_t nwRay = attacks & (0x0102040810204080ULL << square);
    blocker = nwRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      nwRay = bishopAttacks[blockerSquare] & (0x0102040810204080ULL << blockerSquare);
      attacks &= ~nwRay;
    }

    uint64_t swRay = attacks & (0x8040201008040201ULL >> (63 - square));
    blocker = swRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      swRay = bishopAttacks[blockerSquare] & (0x8040201008040201ULL >> (63 - blockerSquare));
      attacks &= ~swRay;
    }

    uint64_t seRay = attacks & (0x0102040810204080ULL >> (63 - square));
    blocker = seRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      seRay = bishopAttacks[blockerSquare] & (0x0102040810204080ULL >> (63 - blockerSquare));
      attacks &= ~seRay;
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
/*
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
  std::cout << "Ally blocking on " << squareToString (allySquare) << std::endl;
  std::cout << "Opp blocking on " << squareToString (oppSquare) << std::endl;
  uint64_t finalAttacks = 0ULL;
  for (Move move: moves)
    finalAttacks |= (1ULL << move.toSquare);
  printBitboard(finalAttacks);
  return (0);
}
*/
