#include "constants.hpp"
#include <cstdint>
#include <array>
#include <vector>

/*
2 UP 1 LEFT no 7, 8, a  << 15
2 UP 1 RIGHT no 7, 8, h << 17
2 DOWN 1 LEFT no 1, 2, a >> 17
2 DOWN 1 RIGHT no 1, 2, h >> 15
2 LEFT 1 UP no 8, a, b << 6
2 LEFT 1 DOWN no 1, a, b >> 10
2 RIGHT 1 UP no 8, g, h << 10
2 RIGHT 1 DOWN no 1, g, h >> 6
*/

static std::array<uint64_t, BOARD_SIZE> knightAttacks;

void  precomputeKnightAttacks() {
  for (int square = 0; square < BOARD_SIZE; square++) {
    uint64_t  sq_bit = 1ULL << square;
    uint64_t  attacks = 0;

    if (!(sq_bit & RANK_7 || sq_bit & RANK_8)) {
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit << 15);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit << 17);
    }
    if (!(sq_bit & RANK_1 || sq_bit & RANK_2)) {
      if (!(sq_bit & FILE_A))
        attacks |= (sq_bit >> 17);
      if (!(sq_bit & FILE_H))
        attacks |= (sq_bit >> 15);
    }
    if (!(sq_bit & FILE_A || sq_bit & FILE_B)) {
      if (!(sq_bit & RANK_8))
        attacks |= (sq_bit << 6);
      if (!(sq_bit & RANK_1))
        attacks |= (sq_bit >> 10);
    }
    if (!(sq_bit & FILE_G || sq_bit & FILE_H)) {
      if (!(sq_bit & RANK_8))
        attacks |= (sq_bit << 10);
      if (!(sq_bit & RANK_1))
        attacks |= (sq_bit >> 6);
    }
    knightAttacks[square] = attacks;
  }
}

std::vector<Move> generateKnightMoves(
    uint64_t knights,
    uint64_t ownPieces
) {
  std::vector<Move>  moves;

  while (knights) {
    int square = __builtin_ctzll(knights);
    uint64_t attacks = knightAttacks[square];
    while (attacks) {
      if ((1ULL << __builtin_ctzll(attacks)) & ~ownPieces)
        moves.push_back({square, __builtin_ctzll(attacks), '\0'});
      attacks &= attacks - 1;
    }
    knights &= knights - 1;
  }
  return (moves);
}

#include <iostream>
#include "bitboard.hpp"
int main(int, char **argv) {
  precomputeKnightAttacks();

  int knightSquare = stringToSquare(argv[1]);
  std::cout << "Square: " << knightSquare << std::endl;
  if (knightSquare == NO_SQUARE)
    return (1);
  uint64_t  knightBoard = 1ULL << knightSquare;
  uint64_t  ownPieces = 0ULL;

  std::vector<Move> knightMoves = generateKnightMoves(knightBoard, ownPieces);

  std::cout << "Knights moves from " << squareToString(knightSquare) << std::endl;
  for (Move move: knightMoves) {
    std::cout << squareToString(move.toSquare) << std::endl;
  }
  return (0);
}
