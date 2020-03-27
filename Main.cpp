#include <iostream>
void Print(const char* const output) { std::cout << output; }

//Write an algorithm that would handle moving a knight in chess. Keep in mind the movement pattern of a knight and that there are certain moves that would be impossible.

struct Board;

struct Piece {
	static enum Color : bool {white = true, black = false};

	signed char x, y;
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
	Color color; //white=true, black=false
	Board* board;

	Piece() = delete;

	Piece(signed char inital_x, signed char initial_y, Color color, Board& board)
		: x(inital_x), y(initial_y), color(color), board(&board)
	{
		board.pointers[8 * (7 - y) + x] = (void*)this;
	}

};

struct Knight {
	Piece piece;

	Knight() = delete;
	const static enum StartingColumn : signed char { B = 1, G = 6};
	Knight(Piece::Color team, StartingColumn column, Board& board) // B column = true, G column = false  
		: piece(column, (team) ? 7 : 0, team, board) //decide where to put the piece
	{}

	const static enum HDir : signed char {east  = 1, west  = -1};
	const static enum VDir : signed char {north = 1, south = -1};
	const static enum SDir : bool {vertical = true, horizontal = false};

	void move(HDir hdir, VDir vdir, bool vert_or_horiz_direction) {
		/*
		  ██  ██  ██  ██
		██  ██  ██  ██
		  ██hh██aa██  ██
		██gg██  ██bb██
		  ██  KK  ██  ██
		██ff██  ██cc██
		  ██ee██dd██  ██
		██  ██  ██  ██

		a ttt
		b ttf
		c tff
		d tft
		e fft
		f fff
		g ftf
		h ftt
		*/
		int x = piece.x;
		int y = piece.y;
		x += hdir * ((vert_or_horiz_direction) ? 1 : 2);
		y += hdir * ((vert_or_horiz_direction) ? 2 : 1);
		if (x > 7 || x < 0 || y > 7 || y < 0)
		{
			Print("can't move there!");
		}  else /*if(piece.board[8 * (7 - y) + x]) */{
			piece.x = x;
			piece.y = y;
		}
	}
};

struct Board
{
	void* pointers [64] ;
	Board() 
	{
		memset(pointers, (char)0, 64*sizeof(nullptr));
	}

	~Board()
	{
		delete[] pointers;
	};
	void clear()
	{
		//it doesn't make sense to delete every piece on the board if each piece has its own scope and will deconstruct itself on its own
	};
};

int main() {
	Board board;
	Knight three = Knight(Piece::white, Knight::B, board);
	three.move(Knight::west, Knight::north, Knight::vertical);
}