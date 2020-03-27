/*Board.cpp*/
#include "Board.h"
#include "PosVec.h"
#include "Debugtools/Log.h"
#include "Utils.h"

Board* Board::mainInstance = nullptr;

void populateBoard(Board* boardptr);

Board::Board()
{
    populateBoard(this);
    mainInstance = this;
}

void populateRowWithPieces(Board* boardptr, Pos2 i, Pieces piece)
{
	i.x.x = 0;
	for (i; i.x.x < 8; i.x.x++)
	{
		boardptr->mypieces[i.index] = piece;
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
	populateRowWithPieces(boardptr, Pos2(0, 1), whitePawn);
	populateRowWithPieces(boardptr, Pos2(0, 6), blackPawn);
	//also put all the other pieces in place if you're not lazy like me
	Log(info, "populated board");
}

void Board::forceMove(Pos2 piece, Pos2 to)
{
	if (!to.errored)
	{
		if (mypieces[to.index] == 0)
		{
			mypieces[to.index] = mypieces[piece.index]; //copy to new location, overwriting the empty space
			mypieces[piece.index] = empty; //remove old spot
		}
		else
		{	
			if(!matchingSigns(mypieces[piece.index], mypieces[to.index]))
			{
				addToCappedList(mypieces[to.index]); //capture
				mypieces[to.index] = mypieces[piece.index]; //copy to captured piece, overwriting it
				mypieces[piece.index] = empty; //remove old spot
			}
			else
			{
				LogWarning("can't forceMove there, there's a piece of my color already there");
			}
		}
	}
	else
	{
		LogWarning("can't forceMove there, `to` errored!");
	}
}


static void moveRook(Board* board, Pos2 rook, Pos2 to)
{

}
static void moveKnight(Board* board, Pos2 knight, Pos2 to)
{
	if (((abs(knight.x.x - to.x.x) == 2) && (abs(knight.y.x - to.y.x) == 1))
		||
		((abs(knight.x.x - to.x.x) == 1) && (abs(knight.y.x - to.y.x) == 2)))
	{
		board->forceMove(knight, to);
	}
	else
	{
		LogWarning("invalid move for Knight");
	}
}
static void moveBishop(Board* board, Pos2 bishop, Pos2 to)
{

}
static void moveQueen(Board* board, Pos2 queen, Pos2 to)
{

}
static void moveKing(Board* board, Pos2 king, Pos2 to)
{

}
void Board::move(Pos2 piece, Pos2 to)
{
	switch (mypieces[piece.index])
	{
	case empty:
		LogWarning("can't move nothing");
		break;
	case blackPawn:
		break;
	case blackRook:
		moveRook(this, piece, to);
		break;
	case blackKnight:
		moveKnight(this, piece, to);
		break;
	case blackBishop:
		moveBishop(this, piece, to);
		break;
	case blackQueen:
		moveQueen(this, piece, to);
		break;
	case blackKing:
		moveKing(this, piece, to);
		break;
	case whitePawn:
		break;
	case whiteRook:
		moveRook(this, piece, to);
		break;
	case whiteKnight:
		moveKnight(this, piece, to);
		break;
	case whiteBishop:
		moveBishop(this, piece, to);
		break;
	case whiteQueen:
		moveQueen(this, piece, to);
		break;
	case whiteKing:
		moveKing(this, piece, to);
		break;
	}
}

void Board::move(Pos2 piece, Vec2 delta)
{
	move(piece, piece + delta);
}
