#include "bitboard.hpp"
#include "moveGeneration.hpp"

int main(int, char **argv) {
  precomputeRookAttacks();
  precomputeBishopAttacks();
  precomputeQueenAttacks();

  int queenSquare = stringToSquare(argv[1]);
  int allySquare = stringToSquare(argv[2]);
  int oppSquare = stringToSquare(argv[3]);

  cout << "Queen moves from " << squareToString(queenSquare) << endl;
  cout << "Ally blocking on " << squareToString(allySquare) << endl;
  cout << "Opp blocking on " << squareToString(oppSquare) << endl;

  uint64_t queenBoard = 1ULL << queenSquare;
  uint64_t ownPieces = 1ULL << allySquare;
  uint64_t oppPieces = 1ULL << oppSquare;
  uint64_t allPieces = ownPieces | oppPieces;

  std::vector<Move> moves = generateQueenMoves(queenBoard, ownPieces, allPieces);

  uint64_t attacks = 0;
  for (Move move: moves)
    attacks |= (1ULL << move.toSquare);

  printBitboard(attacks);

  return (0);
}
