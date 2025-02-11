#include "constants.hpp"
#include <array>
#include <vector>

// YET TO IMPLEMENT CASTLING/CHECKS

/*
N << 8
NE << 9
E << 1
NW << 7
SE >> 7
S >> 8
SW >> 9
W >> 1

*/

static std::array<uint64_t, BOARD_SIZE> kingAttacks;

void  precomputeKingAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t sq_bit = 1ULL << square;
    uint64_t attacks = 0ULL;

    if (!(sq_bit & RANK_8)) {
      attacks |= (sq_bit << 8);
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit << 7);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit << 9);
    }
    if (!(sq_bit & RANK_1)) {
      attacks |= (sq_bit >> 8);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit >> 7);
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit >> 9);
    }
    if (!(sq_bit & FILE_A))
      attacks |= (sq_bit >> 1);
    if (!(sq_bit & FILE_H))
      attacks |= (sq_bit << 1);

    kingAttacks[square] = attacks;
  }
}

std::vector<Move> generateKingMoves(
    uint64_t kings,
    uint64_t ownPieces
) {
  std::vector<Move> moves;
  while (kings) {
    int square = __builtin_ctzll(kings); // get king pos
    uint64_t attacks = kingAttacks[square];
    while (attacks) {
      if ((1ULL << __builtin_ctzll(attacks)) & ~ownPieces) // valid if not on own piece
        moves.push_back({square, __builtin_ctzll(attacks), '\0'});
      attacks &= attacks - 1; // remove LSB
    }
    kings &= kings - 1;
  }
  return (moves);
}

/*
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
*/
