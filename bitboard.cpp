#include <cstdint>
#include "using.hpp"

struct Bitboard {
  uint64_t	pawns = 0;
  uint64_t	knights = 0;
  uint64_t	bishops = 0;
  uint64_t	rooks = 0;
  uint64_t	queens = 0;
  uint64_t	kings = 0;
  uint64_t	whitePieces = 0;
  uint64_t	blackPieces = 0;
};

void	printBitboard(uint64_t bitboard) {
  for (int r = 7; r >= 0; r--) {
	for (int file = 0; file < 8; file++) {
	  int square = r * 8 + file;
	  cout << ((bitboard & (1ULL << square)) ? '1' : '0') << ' ';
	}
	cout << endl;
  }
  cout << endl;
}

Bitboard	setStartingPosition() {
  Bitboard	board;

  board.pawns = 0x00FF00000000FF00;
  board.knights = 0x4200000000000042;
  board.bishops = 0x2400000000000024;
  board.rooks = 0x8100000000000081;
  board.queens = 0x0800000000000008;
  board.kings = 0x1000000000000010;

  board.whitePieces = 0x000000000000FFFF;
  board.blackPieces = 0xFFFF000000000000;

  return (board);
}

int main() {
  Bitboard  board = setStartingPosition();

  return (0);
}
