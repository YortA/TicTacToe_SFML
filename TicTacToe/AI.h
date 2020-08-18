#pragma once
#include <vector>

class AI
{
private:
	// Game markers (no magic values allowed!)
	const char humanMarker = 'X';
	const char aiMarker = 'O';
	const char emptyMarker = '_';

	class myDebugger* debugger = nullptr;

public:
	AI();
	~AI();

	// required for tracking our moves in our minimax algorithm
	struct Moves
	{
		int x = 0;		// our rows
		int y = 0;		// our cols
	};

	// Use this enum to check user and ai status (used with checkwin)
	enum class PLAYER
	{
		USER,
		COMPUTER
	};

	// Allows our AI to place a circle
	void switchFromXtoO(class Entity* entity);

	// ### MINIMAX ALGORITHM SECTION ###
	// searches for an empty square
	bool hasEmptySquare(char copyMarkervec[3][3]);
	// checks for win condition (user and computer)
	bool checkWin(PLAYER player, char copyMarkervec[3][3]);
	bool checkWin_Game(PLAYER player, std::vector<std::vector<class Entity*>> markerVec);
	// returns win + score
	bool gameOver(char copyMarkervec[3][3]);

	// main algorithm recursion section -- see below for theory
	Moves minimax(std::vector<std::vector<class Entity*>> markerVec);
	int maxReturn(char copyMarkervec[3][3], int iteration);
	int minReturn(char copyMarkervec[3][3], int iteration);
	// returns score for evaluation function
	int score(char copyMarkervec[3][3]);

	// extracts our sign from a number
	int signFN(int num);

};

// MINIMAX ALGORITHM THEORY
/*

A minimax algorithm is a recurision algorithm that checks for a win and loss condition.

It does this by creating a copy of our char array ids [3][3], and cycles through each
grid location looking for the best possible move. This move is calculated by assigning
the id to each grid separately, and looking for which move results in a loss and which
move results in a victory.

We define a win using our heuristic function and checkWin() by returning a score value.
A positive number will result in a win, while a negative number will result in a loss.
Our minimax function checks to see which gives us the quickest win.

An example of this is, if you have three possible spots on our board. One is a win,
one is a loss, and one is a draw; the win will be +1, a loss with be -1, and a draw
will be -1 (because we didn't win). Because we check for a higher score inside of our 
gameover function, we pass our heuristic to give us more values to check for, as well
as return our win condition score. The higher the values, the more checks the AI will
make in the recursion function.

So, from a technical standpoint, let's run through our minimax function:

>> 1. Pass our vector ids, and copy them into a 2d char array;

>> 2. Assign our "best move" to 10000, now if the first location of our grid, [0][0] is == null,
then assign it to AI marker. (o);

>> 3. Run our maxReturn() function by copying our char array, remember our current location [0][0]
has a marker set to (o); maxReturn() checks if game is over -- it's not, so let's check for best
move. Assign our next marker [0][1] to (x) (because 0,0 is taken). Pass our char array to minReturn;

>> 4. Check to see if gameover, it's not -- now check for empty marker, it looks like [0][2] is empty,
assign it the aimarker (o); now pass our char arrary to maxreturn() again.

>> 5. Repeat 3 and 4 until all squares are full. Check for gameover. If gameover returns true;
we get our metric + signFN and our iteration (heuristic fn). Else, we return the bestMove, meaning
no one won, so we'll take any spot really.

>> 6. We repeat this process until our board is full. It is easier for the computer to play defensively
and never lose because there's less outcomes for the minimax function to process.

*/
