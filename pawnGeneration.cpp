#include "using.hpp"
#include <cstdint>

struct pawnMove {
  int   fromSquare;
  int   toSquare;
  char  promotion;
}

std::vector<Move> generatePawnMoves(
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
    capturesLeft = (pawns << 7) & opponentPieces & ~
