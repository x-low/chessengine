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
  int square;
  uint64_t attacks;
  uint64_t blocker;
  uint64_t blockerSquare;

  while (rooks) {
    square = __builtin_ctzll(rooks);
    attacks = rookAttacks[square];

    uint64_t upRay = attacks & 0xFFFFFFFFFFFFFF00ULL << square;
    blocker = upRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      upRay = rookAttacks[blockerSquare] & 0xFFFFFFFFFFFFFF00ULL << blockerSquare;
      attacks &= ~upRay;
    }

    uint64_t downRay = attacks & 0x00FFFFFFFFFFFFFFULL >> (63 - square);
    blocker = downRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      downRay = rookAttacks[blockerSquare] & 0x00FFFFFFFFFFFFFFULL >> (63 - blockerSquare);
      attacks &= ~downRay;
    }

    uint64_t leftRay = attacks & 0xFF00000000000000ULL >> (63 - square);
    blocker = leftRay & allPieces;
    if (blocker) {
      blockerSquare = 63 - __builtin_clzll(blocker);
      leftRay = rookAttacks[blockerSquare] & 0xFF00000000000000ULL >> (63 - blockerSquare);
      attacks &= ~leftRay;
    }

    uint64_t rightRay = attacks & 0x00000000000000FFULL << square;
    blocker = rightRay & allPieces;
    if (blocker) {
      blockerSquare = __builtin_ctzll(blocker);
      rightRay = rookAttacks[blockerSquare] & 0x00000000000000FFULL << blockerSquare;
      attacks &= ~rightRay;
    }

    attacks &= ~ownPieces;

    while (attacks) {
      moves.push_back({square, __builtin_ctzll(attacks), '\0'});
      attacks &= attacks - 1;
    }
    rooks &= rooks - 1;
  }
  return (moves);
}

/*
#include "bitboard.hpp"
int main(int, char**argv) {
  precomputeRookAttacks();

  int rookSquare = stringToSquare(argv[1]);
  int allySquare = stringToSquare(argv[2]);
  int oppSquare = stringToSquare(argv[3]);
  std::cout << "Square: " << rookSquare << std::endl;
  std::cout << "Ally: " << allySquare << std::endl;
  std::cout << "Opp: " << oppSquare << std::endl;
  uint64_t rookBoard = 1ULL << rookSquare;
  uint64_t ownPieces = 1ULL << allySquare;
  uint64_t opponentPieces = 1ULL << oppSquare;
  uint64_t allPieces = ownPieces | opponentPieces;

  std::vector<Move> moves = generateRookMoves(rookBoard, ownPieces, allPieces);

  std::cout << "Rook moves from " << squareToString (rookSquare) << std::endl;
  std::cout << "Ally blocking on " << squareToString (std::atoi(argv[2])) << std::endl;
  for (Move move: moves)
    std::cout << squareToString(move.toSquare) << std::endl;
  return (0);
}
*/
