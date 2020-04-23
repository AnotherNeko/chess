#pragma once

#include "ChessPieces.h"
#include <string>
void inline Print(const char* const output) { std::cout << output; }

std::string Pos2_to_string(Pieces piece)
{
    switch (piece)
    {
    case         empty:
        return ("empty");
    case         blackPawn:
        return ("blackPawn");
    case         blackRook:
        return ("blackRook");
    case         blackKnight:
        return ("blackKnight");
    case         blackBishop:
        return ("blackBishop");
    case         blackQueen:
        return ("blackQueen");
    case         blackKing:
        return ("blackKing");
    case         whitePawn:
        return ("whitePawn");
    case         whiteRook:
        return ("whiteRook");
    case         whiteKnight:
        return ("whiteKnight");
    case         whiteBishop:
        return ("whiteBishop");
    case         whiteQueen:
        return ("whiteQueen");
    case         whiteKing:
        return ("whiteKing");
    default:
        return ("[eRrOr}");
    }
}

/*
https://www.newgrounds.com/bbs/topic/1332041
Diki
Member since: Jan. 31, 2004
Offline.

    Send Private Message
    Browse All Posts (3,527)
    Block

Moderator
Level 13 Programmer

Response to C++ Comparing signs of two numbers
Feb 7, 2013

You could just write a simple function to do it.
No need for multiplication or division.*/

template <class NumTy>
inline bool matchingSigns(NumTy a, NumTy b) {
    return a < (NumTy)0 == b < (NumTy)0;
}

/*Since it's a template it will work for any given number type, be it a signed or unsigned char/short/int, or a float/double.
The casting to NumTy is just there to prevent potential compiler warnings.

The logic is pretty straightforward. Check if both numbers are less than zero, which will result in two bool results. Two positives will yield two false values, and two negatives will yield two true values. True equals true , and false equals false, so either of those cases will cause the function to return true, otherwise the signs don't match and you'll get a false return value.
Hopefully that wasn't too confusing of an explanation.

The function will also most likely be inlined automatically by the compiler, so it will be as if the function was never there.
*/

unsigned char inline abs(signed char _X) 
{
    return(abs((int)_X));
}

inline int multiply(int a, int b)
{
    return a * b;
}