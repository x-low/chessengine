#include "bitboard.hpp"

std::string squareToString(Square square) {
  if (square < 0 || square > NO_SQUARE)
    return ("Invalid");

  char file = 'a' + (square % 8);
  char Rank = '1' + (square / 8);

  return (std::string(1, file) + Rank);
}

Square  stringToSquare(const std::string& str) {
  if (str.size() != 2)
    return (NO_SQUARE);

  char file = str[0];
  char Rank = str[1];

  if (file < 'a' || file > 'h' || Rank < '1' || Rank > '8')
    return (NO_SQUARE);

  return (static_cast<Square>((file - 'a') + (Rank - '1') * 8));
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

void	printBitboard(uint64_t bitboard) {
  for (int Rank = 7; Rank >= 0; Rank--) {
	for (int file = 0; file < 8; file++) {
	  int square = Rank * 8 + file;
	  cout << ((bitboard & (1ULL << square)) ? '1' : '0') << ' ';
	}
	cout << endl;
  }
  cout << endl;
}

void  setBit(uint64_t &bitboard, int square) { // Place piece
  bitboard |= (1ULL << square);
}

void  clearBit(uint64_t &bitboard, int square) { // Remove piece
  bitboard &= ~(1ULL << square);
}

void  toggleBit(uint64_t &bitboard, int square) { // Places/removes if absent/existing
  bitboard ^= (1ULL << square);
}

bool  isBitSet(uint64_t bitboard, int square) { // Check occupancy
  return (bitboard & (1ULL << square));
}

int   countBits(uint64_t bitboard) {
  int count = 0;
  while (bitboard) {
    bitboard &= (bitboard - 1);
    count++;
  }
  return (count);
}

int   getLSBIndex(uint64_t bitboard) {
  return (__builtin_ctzll(bitboard));
}

int   getMSBIndex(uint64_t bitboard) {
  return (63 - __builtin_ctzll(bitboard));
}

int main() {
  Bitboard  board = setStartingPosition();
  printBitboard(board.whitePieces);
  return (0);
}
