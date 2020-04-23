/*Board.h*/#pragma once
#include "ChessPieces.h"
#include "PosVec.h"

struct Board 
{
	static Board* mainInstance;
    Board();
	Pieces mypieces[8 * 8] =                                     //   A B C D E F G H 
    { empty, empty, empty, empty, empty, empty, empty, empty,	 // 8   ██  ██  ██  ██ black side
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 7 ██  ██  ██  ██   black side
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 6   ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 5 ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 4   ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 3 ██  ██  ██  ██
      empty, empty, empty, empty, empty, empty, empty, empty,	 // 2   ██  ██  ██  ██ white side
      empty, empty, empty, empty, empty, empty, empty, empty };  // 1 ██  ██  ██  ██   white side
   
    bool forceMove(Pos2 piece, Pos2 to);
    void move(Pos2 piece, Pos2 to);
    void move(Pos2 piece, Vec2 delta);
    void addToCappedList(Pieces piece);
};
