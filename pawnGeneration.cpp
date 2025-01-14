#include "using.hpp"
#include <cstdint>

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
    promotions = singlePush & 0xFF00000000000000; // Promotion squares
    singlePush &= ~0xFF00000000000000; // Non-promotion squares


    // Double push
    doublePush = ((pawns & 0x000000000000FF00) << 8) & emptySquares;
    doublePush = (doublePush << 8) & emptySquares;

    // Captures
    capturesLeft = (pawns << 7) & opponentPieces & ~0x8080808080808080; // prevents wrapping
    capturesRight = (pawns << 9) & opponentPieces & ~0x0101010101010101; // e.g left captures to right edge
    promotions |= (capturesLeft | capturesRight) & 0xFF00000000000000; // promotion captures
    capturesLeft &= ~0xFF00000000000000; // non promotion captures
    capturesRight &= ~0xFF00000000000000;

    // En passant
    capturesLeft |= (pawns << 7) & enPassantTarget & ~0x8080808080808080;
    capturesRight |= (pawns << 9) & enPassantTarget & ~0x0101010101010101;
  }
  else {
    // Single push
    singlePush = (pawns >> 8) & emptySquares;
    promotions = singlePush & 0x00000000000000FF; // promotion squares
    singlePush &= ~0x00000000000000FF; // non promotion squares

    // Double push
    doublePush = ((pawns & 0x00FF000000000000) >> 8) & emptySquares;
    doublePush = (doublePush >> 8) & emptySquares;

    // Captures
    capturesLeft = (pawns >> 9) & opponentPieces & ~0x8080808080808080; // prevents wrapping
    capturesRight = (pawns >> 7) & opponentPieces & ~0x0101010101010101;
    promotions |= (capturesLeft | capturesRight) & 0x00000000000000FF; // promotion captures
    capturesLeft &= ~0x00000000000000FF;
    capturesRight &= ~0x00000000000000FF;

    // En passant
    capturesLeft |= (pawns >> 9) & enPassantTarget & ~0x8080808080808080;
    capturesRight |= (pawns >> 7) & enPassantTarget & ~0x0101010101010101;
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
