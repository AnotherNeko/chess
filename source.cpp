﻿/*source.cpp*///Write an algorithm that would handle moving a knight in chess. Keep in mind the movement pattern of a knight and that there are certain moves that would be impossible.

#include <iostream>
#include "Debugtools/Log.h"
#include "PosVec.h"
#include "Board.h"
#include "ChessPieces.h"







int main() {
	Board board;
	board.move(Pos2(0, 0), Vec2(0, 6));
}