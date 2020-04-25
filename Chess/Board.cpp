/*Board.cpp*/
#include "Board.h"
#include "PosVec.h"
#include "../Debugtools/Log.h"
#include "Utils.h"

Board* Board::mainInstance = nullptr;

void populateBoard(Board* boardptr);

//constructor also populates the board
Board::Board()
{
	populateBoard(this);
	mainInstance = this;
}

//fill a row with pieces
void populateRowWithPieces(Board* boardptr, Pos2 i, Pieces whichkind)
{
	i.x.x = 0;
	for (i; i.x.x < 8; i.x.x++)
	{
		/**(
			(Pieces*)(
				boardptr
				+ sizeof(Board*)
				+ multiply((int)(i.index()) , (int)sizeof(Pieces))
			)
		) = whichkind;*/
		(boardptr->mypieces)[i.index()] = whichkind;
	}
}

//put pieces on the board
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

	//putting all the pieces where they need to go
	populateRowWithPieces(boardptr, Pos2(0, 1), whitePawn);
	(boardptr->mypieces)[Pos2(0, 0).index()] = whiteRook;
	(boardptr->mypieces)[Pos2(1, 0).index()] = whiteKnight;
	(boardptr->mypieces)[Pos2(2, 0).index()] = whiteBishop;
	(boardptr->mypieces)[Pos2(3, 0).index()] = whiteKing;
	(boardptr->mypieces)[Pos2(4, 0).index()] = whiteQueen;
	(boardptr->mypieces)[Pos2(5, 0).index()] = whiteBishop;
	(boardptr->mypieces)[Pos2(6, 0).index()] = whiteKnight;
	(boardptr->mypieces)[Pos2(7, 0).index()] = whiteRook;

	populateRowWithPieces(boardptr, Pos2(0, 6), blackPawn);
	(boardptr->mypieces)[Pos2(0, 7).index()] = blackRook;
	(boardptr->mypieces)[Pos2(1, 7).index()] = blackKnight;
	(boardptr->mypieces)[Pos2(2, 7).index()] = blackBishop;
	(boardptr->mypieces)[Pos2(3, 7).index()] = blackKing;
	(boardptr->mypieces)[Pos2(4, 7).index()] = blackQueen;
	(boardptr->mypieces)[Pos2(5, 7).index()] = blackBishop;
	(boardptr->mypieces)[Pos2(6, 7).index()] = blackKnight;
	(boardptr->mypieces)[Pos2(7, 7).index()] = blackRook;
	//irl, these are done one at a time, so I don't see a problem with the program doing the same thing

	//also put all the other pieces in place if you're not lazy like me
	Log(info, "populated board");
}

//does logic to move a piece whereever, while obeying other chess rules like capturing and staying on the board
bool Board::forceMove(Pos2 piece, Pos2 to)
{
	if (!to.errored)
	{
		if (mypieces[to.index()] == 0)
		{
			mypieces[to.index()] = mypieces[piece.index()]; //copy to new location, overwriting the empty space
			mypieces[piece.index()] = empty; //remove old spot
			return(true);
		}
		else

		{
			if (!matchingSigns(mypieces[piece.index()], mypieces[to.index()]))
			{
				addToCappedList(mypieces[to.index()]); //capture
				mypieces[to.index()] = mypieces[piece.index()]; //copy to captured piece, overwriting it
				mypieces[piece.index()] = empty; //remove old spot
				return(true);
			}
			else
			{
				LogWarning("can't forceMove there, there's a piece of my color already there");
				return(false);
			}
		}
	}
	else
	{
		LogWarning("can't forceMove there, `to` errored (you probably tried to move off of the board)!");
		return(false);
	}
}


static inline void moveRook(Board* board, Pos2 rook, Pos2 to)
{
	if ((rook.x == to.x) xor (rook.y == to.y)) //can go NESW
	{
		Vec2 norm;
		if (to.x.x > rook.x.x)
		{
			norm = Vec2(1, 0);
		}
		if (to.x.x < rook.x.x)
		{
			norm = Vec2(-1, 0);
		}
		if (to.y.x > rook.y.x)
		{
			norm = Vec2(0, 1);
		}
		if (to.y.x < rook.y.x)
		{
			norm = Vec2(0, -1);
		}
		for (Pos2 i = rook + norm; i != to; i += norm)
		{
			if (board->mypieces[i.index()] != empty)
			{
				LogWarning("There's a piece (" + Piece_to_string(board->mypieces[i.index()]) + " at " + operator$(i) + ") in the way");
				return;
			}
		}
		board->forceMove(rook, to);
	}
	else
	{
		LogWarning("invalid move for Rook");
		return;
	}
}
static inline void moveKnight(Board* board, Pos2 knight, Pos2 to)
{
	Vec2 temp = to - knight;
	if (   temp == Vec2(+2, +1)	 //  ██  ██
		|| temp == Vec2(+2, -1)	 //██      ██
		|| temp == Vec2(+1, +2)	 //    []
		|| temp == Vec2(+1, -2)	 //██      ██
		|| temp == Vec2(-2, +1)	 //  ██  ██
		|| temp == Vec2(-2, -1)
		|| temp == Vec2(-1, +2)
		|| temp == Vec2(-1, -2))
	{
		board->forceMove(knight, to);
	}
	else
	{
		LogWarning("invalid move for Knight");
	}
}
static inline void moveBishop(Board* board, Pos2 bishop, Pos2 to)
{
	Vec2 temp = to - bishop;
	if (abs(temp.x.x) == abs(temp.y.x) && temp != Vec2(/*going nowhere*/)) //can go diagonally
	{
		Vec2 norm;
		if (to.x.x > bishop.x.x && to.y.x > bishop.y.x) //change in x and change in y are positive
		{
			norm = Vec2(1, 1);
		}
		if (to.x.x < bishop.x.x && to.y.x < bishop.y.x) //change in x and change in y are negative
		{
			norm = Vec2(-1, -1);
		}
		if (to.x.x > bishop.x.x && to.y.x < bishop.y.x)
		{
			norm = Vec2(1, -1);
		}
		if (to.x.x < bishop.x.x && to.y.x > bishop.y.x)
		{
			norm = Vec2(-1, 1);
		}
		for (Pos2 i = bishop + norm; i != to; i += norm)
		{
			if (board->mypieces[i.index()] != empty)
			{
				LogWarning("There's a piece (" + Piece_to_string(board->mypieces[i.index()]) + " at " + operator$(i) + ") in the way");
				return;
			}
		}
		board->forceMove(bishop, to);
	}
	else
	{
		LogWarning("invalid move for Bishop");
		return;
	}
}
static inline void moveQueen(Board* board, Pos2 queen, Pos2 to)
{
	//can go straight in N, NE, E, SE, S, SW, W, NW
	Vec2 temp = to - queen;
	if (abs(temp.x.x) == abs(temp.y.x) && temp != Vec2(/*going nowhere*/)) //if going diagonally
	{
		Vec2 norm;
		if (to.x.x > queen.x.x && to.y.x > queen.y.x) //change in x and change in y are positive
		{
			norm = Vec2(1, 1);
		}
		if (to.x.x < queen.x.x && to.y.x < queen.y.x) //change in x and change in y are negative
		{
			norm = Vec2(-1, -1);
		}
		if (to.x.x > queen.x.x && to.y.x < queen.y.x)
		{
			norm = Vec2(1, -1);
		}
		if (to.x.x < queen.x.x && to.y.x > queen.y.x)
		{
			norm = Vec2(-1, 1);
		}
		for (Pos2 i = queen + norm; i != to; i += norm)
		{
			if (board->mypieces[i.index()] != empty)
			{
				LogWarning("There's a piece (" + Piece_to_string(board->mypieces[i.index()]) + " at " + operator$(i) + ") in the way");
				return;
			}
		}
		board->forceMove(queen, to);
		return;
	}
	if ((queen.x == to.x) xor (queen.y == to.y)) //if going NESW
	{
		Vec2 norm;
		if (to.x.x > queen.x.x)
		{
			norm = Vec2(1, 0);
		}
		if (to.x.x < queen.x.x)
		{
			norm = Vec2(-1, 0);
		}
		if (to.y.x > queen.y.x)
		{
			norm = Vec2(0, 1);
		}
		if (to.y.x < queen.y.x)
		{
			norm = Vec2(0, -1);
		}
		for (Pos2 i = queen + norm; i != to; i += norm)
		{
			if (board->mypieces[i.index()] != empty)
			{
				LogWarning("There's a piece (" + Piece_to_string(board->mypieces[i.index()]) + " at " + operator$(i) + ") in the way");
				return;
			}
		}
		board->forceMove(queen, to);
		return;
	}
	LogWarning("invalid move for Queen");

}
static inline void moveKing(Board* board, Pos2 king, Pos2 to)
{
	Vec2 temp = to - king;
	if (abs(temp.x.x) == 1 || abs(temp.y.x) == 1) //can go 1 or 1.21 in any direction
	{
		board->forceMove(king, to);
	}
	else
	{
		LogWarning("invalid move for King");
	}

}

void Board::move(Pos2 piece, Pos2 to)
{
	if (to == piece)
	{
		LogWarning("must make a move/can't go nowhere");
		return;
	}
	switch (mypieces[piece.index()])
	{
	case empty:
		LogWarning("can't move nothing");
		break;
	case blackPawn:
		if (mypieces[to.index()] == empty)
		{
			//pawn: simple move forward
			if (to == piece + Vec2(0, -1)) 
			{
				forceMove(piece, to);
				break;
			}

			//pawn: "move 2 spaces" 
			if (to == piece + Vec2(0, -2) && to.y.x == 4) 
			{
				if (mypieces[(piece + Vec2(0, -1)).index()] == empty)
				{
					forceMove(piece, to);
					break;
				}
				else
				{
					LogWarning("invalid move for blackPawn: can't jump over non-empty space (" + Piece_to_string(mypieces[(piece + Vec2(0, -1)).index()]) + " at " + operator$((piece + Vec2(0, -1))) + ") when moving 2 forward");
					break;
				}
			}
		}
		else
		{
			//pawn: capture
			if (to == piece + Vec2(1, -1) || to == piece + Vec2(-1, -1))
			{
				forceMove(piece, to);
				break;
			}
			else
			{
				LogWarning("invalid move for blackPawn: can't capture that spot (" + Piece_to_string(mypieces[to.index()]) + " at " + operator$(to) + ")");
				break;
			}
		}
		LogError("Unexpected Pawnmoving Condition");
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
		if (mypieces[to.index()] == empty)
		{
			//pawn: simple move forward
			if (to == piece + Vec2(0, 1))
			{
				forceMove(piece, to);
				break;
			}

			//pawn: "move 2 spaces" 
			if (to == piece + Vec2(0, 2) && to.y.x == 3)
			{
				if (mypieces[(piece + Vec2(0, 1)).index()] == empty)
				{
					forceMove(piece, to);
					break;
				}
				else
				{
					LogWarning("invalid move for whitePawn: can't jump over non-empty space (" + Piece_to_string(mypieces[(piece + Vec2(0, 1)).index()]) + " at " + operator$((piece + Vec2(0, 1))) + ") when moving 2 forward");
					break;
				}
			}
		}
		else
		{
			//pawn: capture
			if (to == piece + Vec2(1, 1) || to == piece + Vec2(-1, 1))
			{
				forceMove(piece, to);
				break;
			}
			else
			{
				LogWarning("invalid move for whitePawn: can't capture that spot (" + Piece_to_string(mypieces[to.index()]) + " at " + operator$(to) + ")");
				break;
			}
		}
		LogError("Unexpected Pawnmoving Condition");
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

void Board::addToCappedList(Pieces piece)
{
	LogInfo("capped a piece");
}
