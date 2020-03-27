﻿/*PosVec.cpp*/#include "PosVec.h"
#include "Debugtools/Log.h"

//this is meant to only work with Chess.

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

Pos1::Pos1(unsigned char initial_x)
	: x(initial_x)
{
	errored = false;
	//unsigned can't be less than 0 so don't check for it
	if (initial_x > 8)
	{
		errored = true;
		Log(error, "Can't go there! (" + unsignedchar_toString(initial_x) + ")");
	}
}
bool Pos1::errored = false;

Pos2::Pos2(Pos1 initial_xpos, Pos1 initial_ypos)
	: x(initial_xpos), y(initial_ypos)
{
	errored = false;
	//unsigned can't be less than 0 so don't check for it
	if (initial_xpos.x > 8 or initial_ypos.x > 8)
	{
		errored = true;
		Log(error, "Can't go there! (" + unsignedchar_toString(initial_xpos.x) + ", " + unsignedchar_toString(initial_ypos.x) + ")");
	}
}
unsigned char Pos2::index()
{
	return(x.x + 8 * y.x);
}
bool Pos2::errored = false;

Vec1::Vec1()
	: x(0) {}
Vec1::Vec1(signed char x)
	: x(x) {}


Vec2::Vec2()
	: x(), y() {}
Vec2::Vec2(Vec1 x, Vec1 y)
	: x(x), y(y) {}

Pos1 operator+(Pos1 left, Vec1 right)
{
	return(Pos1(left.x + right.x));
}
Pos1 operator+(Vec1 left, Pos1 right)
{
	return(operator+(right, left)); //commutative property
}

Pos2 operator+(Pos2 left, Vec2 right)
{
	return(Pos2(left.x + right.x, left.y + right.y));
}
Pos2 operator+(Vec2 left, Pos2 right)
{
	return(operator+(right, left)); //commutative property
}