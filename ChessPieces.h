/*ChessPieces.h*/#pragma once
#include "Debugtools/Log.h"
#include "PosVec.h"
#include "Colors.h"
#include "Board.h"


struct Piece {
	Pos2 pos;
	Color color; //white=true, black=false
	Board* myBoard; //piece needs to know which board it is on in order to see... for example... which other pieces it can capture

	void put_this_in_board(Board* boardptr);
	void put_this_in_board();

 /*private*/public: //private so that no one just randomly constructs a piece for no reason, cause the constructor does a lot
	Piece() = delete;

	Piece(Pos2 initialpos, Color color);
	Piece(unsigned char inital_x, unsigned char initial_y, Color color);
	Piece(Board* boardptr, Pos2 initialpos, Color color);
	Piece(Board* boardptr, unsigned char inital_x, unsigned char initial_y, Color color);
	friend void populateRowWithPawns(Board* boardptr, Pos2 i, Color color);
	friend void populateBoard(Board* boardptr);
 public:
	void getCaptured();

	void move(Pos2 location);
	void move(Vec2 delta);
};