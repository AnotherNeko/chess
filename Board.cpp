/*Board.cpp*/#include "Board.h"
#include "PosVec.h"
#include "Debugtools/Log.h"

static void wrapToNextRow_Pos2(Pos2& pos)
{
	pos.x.x = 0;
	pos.y.x++;
}

Board* Board::mainInstance = nullptr;

void populateBoard(Board* boardptr);

Board::Board()
{
    populateBoard(this);
    mainInstance = this;
}

void populateRowWithPawns(Board* boardptr, Pos2 i, Color color)
{
	i.x.x = 0;
	for (i; i.x.x < 8; i.x.x++)
	{
		new Pawn(boardptr, i, white); //create a new piece on the heap and allow its constructor to put its pointer in the spot on the board
	}
}


void populateBoard(Board* boardptr)
{
	/*
	  A0B1C2D3E4F5G6H7     pairs are for (irl pencil value, signed char value)
	87  ██  ██  ██  ██ black side
	76██  ██  ██  ██   black side
	65  ██  ██  ██  ██
	54██  ██  ██  ██
	43  ██  ██  ██  ██
	32██  ██  ██  ██
	21  ██  ██  ██  ██ white side
	10██  ██  ██  ██   white side
	*/
	populateRowWithPawns(boardptr, Pos2(0, 1), white);
	populateRowWithPawns(boardptr, Pos2(0, 6), black);
	Log(info, "populated board");
}
