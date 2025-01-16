#include "constants.hpp"
#include <cstdint>
#include <vector>

using std::vector;

struct pawnMove {
  int   fromSquare;
  int   toSquare;
  char  promotion;
};

std::vector<pawnMove> generatePawnMoves(
    uint64_t pawns,
    uint64_t emptySquares,
    uint64_t opponentPieces,
    uint64_t enPassantTarget,
    bool isWhite
) {
  vector<pawnMove> moves;
  uint64_t singlePush, doublePush, capturesLeft, capturesRight, promotions;

  if (isWhite) {
    // Single push
    singlePush = (pawns << 8) & emptySquares;
    promotions = singlePush & RANK_8; // Promotion squares
    singlePush &= ~RANK_8; // Non-promotion squares


    // Double push
    doublePush = ((pawns & RANK_2) << 8) & emptySquares;
    doublePush = (doublePush << 8) & emptySquares;

    // Captures
    capturesLeft = (pawns << 7) & opponentPieces & ~FILE_H; // prevents wrapping
    capturesRight = (pawns << 9) & opponentPieces & ~FILE_A; // e.g left captures to right edge
    promotions |= (capturesLeft | capturesRight) & RANK_8; // promotion captures
    capturesLeft &= ~RANK_8; // non promotion captures
    capturesRight &= ~RANK_8;

    // En passant
    capturesLeft |= (pawns << 7) & enPassantTarget & FILE_H;
    capturesRight |= (pawns << 9) & enPassantTarget & ~FILE_A;
  }
  else {
    // Single push
    singlePush = (pawns >> 8) & emptySquares;
    promotions = singlePush & RANK_1; // promotion squares
    singlePush &= ~RANK_1; // non promotion squares

    // Double push
    doublePush = ((pawns & RANK_7) >> 8) & emptySquares;
    doublePush = (doublePush >> 8) & emptySquares;

    // Captures
    capturesLeft = (pawns >> 9) & opponentPieces & ~FILE_H; // prevents wrapping
    capturesRight = (pawns >> 7) & opponentPieces & ~FILE_A;
    promotions |= (capturesLeft | capturesRight) & RANK_1; // promotion captures
    capturesLeft &= ~RANK_1;
    capturesRight &= ~RANK_1;

    // En passant
    capturesLeft |= (pawns >> 9) & enPassantTarget & ~FILE_H;
    capturesRight |= (pawns >> 7) & enPassantTarget & ~FILE_A;
  }

  while (singlePush) {
    int toSquare = __builtin_ctzll(singlePush); // zeroes to lsb/square idx of lsb
    int fromSquare = toSquare + (isWhite ? -8 : 8);
    moves.push_back({fromSquare, toSquare, '\0'});
    singlePush &= singlePush - 1; // remove lsb
  }

  while (doublePush) {
    int toSquare = __builtin_ctzll(doublePush);
    int fromSquare = toSquare + (isWhite ? -16 : 16);
    moves.push_back({fromSquare, toSquare, '\0'});
    doublePush&= doublePush - 1;
  }

  uint64_t  captures = capturesLeft | capturesRight;
  while (captures) {
    int toSquare = __builtin_ctzll(captures);
    int fromSquare = toSquare + (isWhite ? -7 : 7);
    moves.push_back({fromSquare, toSquare, '\0'});
    captures &= captures - 1;
  }

  while (promotions) {
    int toSquare = __builtin_ctzll(promotions);
    int fromSquare = toSquare + (isWhite ? -8 : 8);
    moves.push_back({fromSquare, toSquare, 'q'});
    moves.push_back({fromSquare, toSquare, 'r'});
    moves.push_back({fromSquare, toSquare, 'b'});
    moves.push_back({fromSquare, toSquare, 'n'});
    promotions &= promotions - 1;
  }

  return (moves);
}
