/*Board.h*/#pragma once
#include "ChessPieces.h"
#include "PosVec.h"

struct Board 
{
	static Board* mainInstance;
    Board();
	Pieces mypieces[8 * 8] = 
    { empty, empty, empty, empty, empty, empty, empty, empty,	 //   ██  ██  ██  ██ black side
      empty, empty, empty, empty, empty, empty, empty, empty,	 // ██  ██  ██  ██   black side
      empty, empty, empty, empty, empty, empty, empty, empty,	 //   ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 //   ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 //   ██  ██  ██  ██ white side
      empty, empty, empty, empty, empty, empty, empty, empty };  // ██  ██  ██  ██   white side
   
    void forceMove(Pos2 piece, Pos2 to);
    void move(Pos2 piece, Pos2 to);
    void move(Pos2 piece, Vec2 delta);
    void addToCappedList(Pieces piece);
};
