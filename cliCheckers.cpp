// Command line interface to play checkers with
// Initializes the board and players, has a game loop which takes and carries out commands and displays the result
/*
#include "board.h"
#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	// Initialize players: p v p, p v ai, ai v ai (maybe?)
	int input = 1;
	do{
		cout << "1) PvP\n2) PvAI\n3)AIvAI\nSelection: ";
		cin >> input;
		Player p1, p2;
		switch(input)
		{
			case 1:
				// Set p1 and p2 to be human
				break;
			case 2:
				// Set p1 to be human, p2 to be ai
				break;
			case 3:
				// Set p1 and p2 to be ai
				break;
			default:
				// Yell at user
				cout << "Fool of a Took!" << endl;
				break;
		}
	}while(input < 1 || input > 3);
	// Initialize board
	Board b;
	// Enter game loop
	bool done = false;
	Player* winner = NULL;
	do
	{
		// Display board
		board.output();
		// Prompt player1 for move
		p1.move();
		// Check win/lose
		winner = winlose();
		if(winner != NULL)
			done = true;
			break;
		// Prompt player2 for move
		p2.move();
		// Check win/lose
		winner = winlose();
		if(winner != NULL)
			done = true;
			break;
	}while(!done);

	if(winner == &NOBODY)
		cout << "TIE!" << endl;
	else if(winner == &p1)
		cout << "Player 1 wins!" << endl;
	else if(winner == &p2)
		cout << "Player 2 wins1" << endl;
	else
		cout << "Nobody wins but it's not a tie o_O" << endl;
	return 0;
}

 Sample move function for the human player
 * This could be passed as a function pointer to set a player as human
 * Ie something like this:
 	Player::setMode(void* move) or however you pass function pointers
	{
		moveFunc = move;
	}
	
	...

	Player human, ai;
	human.setMode(sampleMove);
	ai.setMode(aiMove);
 
  * Or it would be integrated into the player class maybe?
  * As a third option we could just set a flag in Player that the main loop
  *  would check, and if isHuman == true then for player move the sampleMove would
  *  be run

void sampleMove(Player& p, Player& o)
{
	int selection, coordX, coordY;
	cout << "1) Make a move\n2) Propose tie\n3) Rage quit\nSelect: ";
	cin >> selection;

	if(selection == 3)
	{
		cout << "N00b" << endl;;
		p.forfeit = true;
		return;
	}
	else if(selection == 2)
	{
		cout << "Proposing to opponent..." << endl;
		p.draw = true;
		o.processDraw();
		if(o.draw)
		{
			cout << "Draw accepted!" << endl;
		}
		else
		{
			cout << "Denied!" << endl;
		}
		return;
	}
	else
	{
		cout << "Choose a piece to move (enter coordinates): ";
		cin >> coordX, coordY;
		cout << "Move (" << coordX << ", " << coordY << ") to :" << endl;
		// List out moves for the piece at (coordX, coordY)
		for(int i = 0; i < board.getMoves(coordX, coordY).size(); i ++)
		{
			// Print out the move
			cout << "\t" <<  i+1 << ") " << board.getMoves(coordX, coordY)[i] << endl;
		}
		cout << "Select: ";
		cin >> selection;
		if(selection < 1 || selection > board.getMoves(coordX, coordY).size() + 1)
			cout << "Fool of a Took!" << endl;
		// Move the piece to the destination
	}
}
*/
