//one: Write an algorithm that works under certain conditions but will run an infinite loop under other conditions. Explain each condition and why it works or runs an infinite loop.
void one(const char* const conditions) {
	while(conditions != "certain"){
		//infinite loop
	};
	//do stuff here that makes the algorithm work	
}	//this function will start a loop that never ends when the conditions are not ""certain"". Otherwise, this algorithm will work.

//two: Write an algorithm for printing all of the even numbers from 1 to 100, inclusively.
void two() {
	for( unsigned int even ; even <= 100 ; even += 2 ) {
		Print(even);
	}
}

//three: Write an algorithm that would handle moving a knight in chess. Keep in mind the movement pattern of a knight and that there are certain moves that would be impossible.
bool Piece::white = true;
bool Piece::black = false;

class Piece {
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
	bool color; //white=true, black=false
	
	Piece() = delete;

	Piece(signed char inital_x, signed char initial_y, bool color) 
	: x(inital_x), y(initial_y)
	{
		
	}
	
}

class Knight {
	Piece piece;
	Knight() = delete;
	Knight(bool team, bool Btrue_Gfalse) // B column = true, G column = false  
	: piece.color(team), piece.x((Btrue_Gfalse) ? 1 : 6), piece.y((Btrue_Gfalse) ? 0 : 7)
	{
	}
	//HEY MR. (teacher), THIS IS PROBABLY THE PART YOU CARE ABOUT
	//HEY MR. (teacher), THIS IS PROBABLY THE PART YOU CARE ABOUT
	//HEY MR. (teacher), THIS IS PROBABLY THE PART YOU CARE ABOUT
	//HEY MR. (teacher), THIS IS PROBABLY THE PART YOU CARE ABOUT
	//HEY MR. (teacher), THIS IS PROBABLY THE PART YOU CARE ABOUT
	void move(bool left_right, bool up_down, bool more_vertical_than_horizontal) {
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
		int x, y = { piece.x, piece.y }
		x+= ((left_right) ? 1 : -1 ) * ((more_vertical_than_horizontal) ? 1 : 2);
		y+= ((up_down)    ? 1 : -1 ) * ((more_vertical_than_horizontal) ? 2 : 1);
		if(x > 7 || x < 0 || y > 7 || y < 0)
		{
			Print("can't move there!")
		} else {
			piece.x = x;
			piece.y = y;
		}
	}
}

int main() {
	one("certain");
	//this function will start a loop that never ends when the condition is not ""certain"". Otherwise, this algorithm will work.
	two();
	Knight three = Knight(true, true);
	three.move(false, true, true);
}
