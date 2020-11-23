// Tentative pseudocode for checking the win/lose conditions
/*
Player* winlose()
{
	if player1.getPieces().empty() && player2.getPieces.empty()
		return &Nobody
	if player1.getPieces().empty
		// Player2 wins
		return &Playe2
	else if player2.getPieces().empty
		// Player1 wins
		return &Player1
	else if player1.forfeit
		// Player2 wins
		return &Player2
	else if player2.forfeit
		// Player1 wins
		return &Player1
	// If some player can't move, they lose
	else if board.getValidMoves(player1).empty() // Somehow check all valid moves (maybe for loop through pieces)
		return &Player2
	else if board.getValidMoves(player2).empty() // Somehow check all valid moves (maybe for loop through pieces)
		return &Player1
	// If both players agree to draw, nobody wins
	else if playe1.draw && player2.draw
		return &Nobody
	// If neither player can force a win, nobody wins (40 move rule)
	else if player1.draw && player2.moves > 40 || player2.draw && player1.moves > 40
		return &Nobody
}
*/
