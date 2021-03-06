﻿/*PosVec.h*/#pragma once
//this is meant to only work with Chess.

struct Pos1 
{
	unsigned char x;
	static bool errored;
	Pos1() = delete;
	Pos1(unsigned char initial_x);
};

struct Pos2 {
	Pos1 x, y;
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
	static bool errored;
	Pos2() = delete;
	/*
	██A0B1C2D3E4F5G6H7     pairs are for (irl pencil value, signed char value)
	87  ██  ██  ██  ██ black side
	76██  ██  ██  ██   black side
	65  ██  ██  ██  ██
	54██  ██  ██  ██
	43  ██  ██  ██  ██
	32██  ██  ██  ██
	21  ██  ██  ██  ██ white side
	10██  ██  ██  ██   white side
	*/
	Pos2(Pos1 initial_xpos, Pos1 initial_ypos);
	unsigned char index();
};

struct Vec1 {
	signed char x;

	Vec1();
	Vec1(signed char x);
};

struct Vec2 {
	Vec1 x, y;
	Vec2();
	Vec2(Vec1 x, Vec1 y);
};

Pos1 operator+(Pos1 left, Vec1 right);
Pos1 operator+(Vec1 left, Pos1 right);

Pos2 operator+(Pos2 left, Vec2 right);
Pos2 operator+(Vec2 left, Pos2 right);
void operator+=(Pos2& left, Vec2 right);

Vec1 operator-(Pos1 start, Pos1 finish);
Vec2 operator-(Pos2 start, Pos2 finish);

bool operator==(Vec2 a, Vec2 b);
bool operator!=(Vec2 a, Vec2 b);

bool operator==(Pos1 a, Pos1 b);
bool operator!=(Pos1 a, Pos1 b);
bool operator==(Pos2 a, Pos2 b);
bool operator!=(Pos2 a, Pos2 b);

#include <string>

std::string operator$(Pos2 a);
std::string operator$(Vec2 a);
