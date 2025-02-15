#pragma once

#include "constants.hpp"
#include <array>
#include <vector>

void  precomputeKnightAttacks();
void  precomputeKingAttacks();
void  precomputeRookAttacks();
void  precomputeBishopAttacks();
void  precomputeQueenAttacks();

std::vector<Move> generatePawnMoves(uint64_t pawns, uint64_t emptySquares, uint64_t oppPieces, uint64_t enPassantTarget, bool isWhite);
std::vector<Move> generateKnightMoves(uint64_t knights, uint64_t ownPieces);
std::vector<Move> generateKingMoves(uint64_t kings, uint64_t ownPieces);
std::vector<Move> generateRookMoves(uint64_t rooks, uint64_t ownPieces, uint64_t allPieces);
std::vector<Move> generateBishopMoves(uint64_t bishops, uint64_t ownPieces, uint64_t allPieces);
std::vector<Move> generateQueenMoves(uint64_t queens, uint64_t ownPieces, uint64_t allPieces);
