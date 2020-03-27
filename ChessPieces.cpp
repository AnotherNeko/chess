/*ChessPieces.cpp*/#include "ChessPieces.h"
#include "Colors.h"

void Piece::put_this_in_board(Board* boardptr)
{
	if (boardptr->pieces[pos.index()] == nullptr)
	{
		boardptr->pieces[pos.index()] = this;
		myBoard = boardptr;
	}
	else {
		LogWarning("undefined behavior: tried to place a piece on the board not onto a nullptr spot");
	}
}
void Piece::put_this_in_board()
{
	//default for if board is not specified)
	put_this_in_board(Board::mainInstance);
}

//constructors:
Piece::Piece(Pos2 initialpos, Color color)
	: pos(initialpos), color(color)
{
	put_this_in_board();
}
Piece::Piece(unsigned char inital_x, unsigned char initial_y, Color color)
	: pos(Pos2(inital_x, initial_y)), color(color)
{
	put_this_in_board();
}
Piece::Piece(Board* boardptr, Pos2 initialpos, Color color)
	: pos(initialpos), color(color)
{
	put_this_in_board(boardptr);
}
Piece::Piece(Board* boardptr, unsigned char inital_x, unsigned char initial_y, Color color)
	: pos(Pos2(inital_x, initial_y)), color(color)
{
	put_this_in_board(boardptr);
}


void Piece::getCaptured()
{
	//note: when captured, this should be deconstructed and a point should be added to a list for a captured enemy unit.


}

void Piece::move(Pos2 location)
{
	if (!location.errored)
	{
		if (myBoard->pieces[location.index].color != color)
		{
			myBoard->pieces[pos.index] = nullptr;
			pos = location;
			myBoard->pieces[location.index].getCaptured();
		}
		else
		{
			LogWarning("can't move there, there's a piece of my color already there");
		}
	}
	else
	{
		LogWarning("can't move there, location errored!");
	}
}
void Piece::move(Vec2 delta)
{
	move(pos + delta);
}
