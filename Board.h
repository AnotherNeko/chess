/*Board.h*/#pragma once
#include "Colors.h"
#include "ChessPieces.h"

struct Board 
{
	static Board* mainInstance;
    Board();
	Piece* pieces[8 * 8] = /*I want 64 piece pointers, not every one of them will be valid*/
    { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 //   ██  ██  ██  ██ black side
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 // ██  ██  ██  ██   black side
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 //   ██  ██  ██  ██
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 // ██  ██  ██  ██
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 //   ██  ██  ██  ██
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 // ██  ██  ██  ██
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,	 //   ██  ██  ██  ██ white side
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };  // ██  ██  ██  ██   white side
};
