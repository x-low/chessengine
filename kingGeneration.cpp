#include "constants.hpp"
#include <array>
#include <vector>

// YET TO IMPLEMENT CASTLING/CHECKS

/*
N << 8
NE << 9
E << 1
SE >> 7
S >> 8
SW >> 9
W >> 1
NW << 7
*/

static std::array<uint64_t, BOARD_SIZE> kingAttacks;

void  precomputeKingAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t sq_bit = 1ULL << square;
    uint64_t attacks = 0;

    attacks |= (sq_bit << 8);
    attacks |= (sq_bit << 9);
    attacks |= (sq_bit << 1);
    attacks |= (sq_bit >> 7);
    attacks |= (sq_bit >> 8);
    attacks |= (sq_bit >> 9);
    attacks |= (sq_bit >> 1);
    attacks |= (sq_bit << 7);

    kingAttacks[square] = attacks;
  }
}

std::vector<Move> generateKingMoves(
    uint64_t king,
    uint64_t ownPieces
) {
  std::vector<Move> moves;
  int square = __builtin_ctzll(king); // get king pos
  uint64_t attacks = kingAttacks[square];
  while (attacks) {
    if ((1ULL << __builtin_ctzll(attacks)) & ~ownPieces) // valid if not on own piece
      moves.push_back({square, __builtin_ctzll(attacks), '\0'});
    attacks &= attacks - 1; // remove LSB
  }
  return (moves);
}

#include <iostream>
#include "bitboard.hpp"
int main(int, char **argv) {
  precomputeKingAttacks();

  int kingSquare = stringToSquare(argv[1]);
  std::cout << "Square: " << kingSquare << std::endl;
  if (kingSquare == NO_SQUARE)
    return (1);
  uint64_t  kingBoard = 1ULL << kingSquare;
  uint64_t  ownPieces = 0ULL;

  std::vector<Move> kingMoves = generateKingMoves(kingBoard, ownPieces);

  std::cout << "King moves from " << squareToString(kingSquare) << std::endl;
  for (Move move: kingMoves)
    std::cout << squareToString(move.toSquare) << std::endl;
  return (0);
}
