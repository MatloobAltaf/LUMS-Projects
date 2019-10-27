#include <iostream>
//#include <iomanip>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
#include "chess.h"
#include "UInterface.h"


// -------------------------------------------------------------------
// chess class
// -------------------------------------------------------------------
int chess::getPieceColor(char chPiece)
{
	if (isupper(chPiece))
	{
		return WHITE_PIECE;
	}
	else
	{
		return BLACK_PIECE;
	}
}

bool chess::isWhitePiece(char chPiece)
{
	return getPieceColor(chPiece) == chess::WHITE_PIECE ? true : false;
}

bool chess::isBlackPiece(char chPiece)
{
	return getPieceColor(chPiece) == chess::BLACK_PIECE ? true : false;
}

string chess::describePiece(char chPiece)
{
	string description;

	if (isWhitePiece(chPiece))
	{
		description += "White ";
	}
	else
	{
		description += "Black ";
	}

	switch (toupper(chPiece))
	{
	case 'P':
	{
		description += "pawn";
	}
	break;

	case 'N':
	{
		description += "knight";
	}
	break;

	case 'B':
	{
		description += "bishop";
	}
	break;

	case 'R':
	{
		description += "rook";
	}
	break;

	case 'Q':
	{
		description += "queen";
	}
	break;

	default:
	{
		description += "unknow piece";
	}
	break;
	}

	return description;
}

// -------------------------------------------------------------------
// Game class
// -------------------------------------------------------------------
Game::Game()
{
	// White player always starts
	m_CurrentTurn = WHITE_PLAYER;

	// Game on!
	m_bGameFinished = false;


	// Initial board settings
	memcpy(board, initial_board, sizeof(char) * 8 * 8);

	// Castling is allowed (to each side) until the player moves the king or the rook
	/*
	m_bCastlingKingSideAllowed[WHITE_PLAYER] = true;
	m_bCastlingKingSideAllowed[BLACK_PLAYER] = true;

	m_bCastlingQueenSideAllowed[WHITE_PLAYER] = true;
	m_bCastlingQueenSideAllowed[BLACK_PLAYER] = true;
	*/
}

Game::~Game()
{
	white_captured.clear();
	black_captured.clear();

}

void Game::movePiece(Position present, Position future, chess::Promotion* S_promotion)
{
	// Get the piece to be moved
	char chPiece = getPieceAtPosition(present);

	// Is the destination square occupied?
	char chCapturedPiece = getPieceAtPosition(future);

	// So, was a piece captured in this move?
	if (0x20 != chCapturedPiece)
	{
		if (WHITE_PIECE == getPieceColor(chCapturedPiece))
		{
			// A white piece was captured
			white_captured.push_back(chCapturedPiece);
		}
		else
		{
			// A black piece was captured
			black_captured.push_back(chCapturedPiece);
		}

	}
	


	// Remove piece from present position
	board[present.iRow][present.iColumn] = EMPTY_SQUARE;

	// Move piece to new position
	if (true == S_promotion->bApplied)
	{
		board[future.iRow][future.iColumn] = S_promotion->chAfter;

	}
	else
	{
		board[future.iRow][future.iColumn] = chPiece;

	}
	
	// Change turns
	changeTurns();
}

char Game::getPieceAtPosition(int iRow, int iColumn)
{
	return board[iRow][iColumn];
}

char Game::getPieceAtPosition(Position pos)
{
	return board[pos.iRow][pos.iColumn];
}

char Game::getPiece_considerMove(int iRow, int iColumn, IntendedMove* intended_move)
{
	char chPiece;

	// If there is no intended move, just return the current position of the board
	if (nullptr == intended_move)
	{
		chPiece = getPieceAtPosition(iRow, iColumn);
	}
	else
	{
		// In this case, we are trying to understand what WOULD happed if the move was made,
		// so we consider a move that has not been made yet
		if (intended_move->from.iRow == iRow && intended_move->from.iColumn == iColumn)
		{
			// The piece wants to move from that square, so it would be empty
			chPiece = EMPTY_SQUARE;
		}
		else if (intended_move->to.iRow == iRow && intended_move->to.iColumn == iColumn)
		{
			// The piece wants to move to that square, so return the piece
			chPiece = intended_move->chPiece;
		}
		else
		{
			chPiece = getPieceAtPosition(iRow, iColumn);
		}
	}

	return chPiece;
}

chess::UnderAttack Game::isUnderAttack(int iRow, int iColumn, int iColor, IntendedMove* pintended_move)
{
	UnderAttack attack = { 0 };

	// a) Direction: HORIZONTAL
	{
		// Check all the way to the right
		for (int i = iColumn + 1; i < 8; i++)
		{
			char chPieceFound = getPiece_considerMove(iRow, i, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the right, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = iRow;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = i;
				attack.attacker[attack.iNumAttackers - 1].dir = HORIZONTAL;
				break;
			}
			else
			{
				// There is a piece that does not attack horizontally, so no problem
				break;
			}
		}

		// Check all the way to the left
		for (int i = iColumn - 1; i >= 0; i--)
		{
			char chPieceFound = getPiece_considerMove(iRow, i, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the right, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = iRow;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = i;
				attack.attacker[attack.iNumAttackers - 1].dir = HORIZONTAL;
				break;
			}
			else
			{
				// There is a piece that does not attack horizontally, so no problem
				break;
			}
		}
	}

	// b) Direction: VERTICAL
	{
		// Check all the way up
		for (int i = iRow + 1; i < 8; i++)
		{
			char chPieceFound = getPiece_considerMove(i, iColumn, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the right, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = iColumn;
				attack.attacker[attack.iNumAttackers - 1].dir = VERTICAL;
				break;
			}
			else
			{
				// There is a piece that does not attack vertically, so no problem
				break;
			}
		}

		// Check all the way down
		for (int i = iRow - 1; i >= 0; i--)
		{
			char chPieceFound = getPiece_considerMove(i, iColumn, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the right, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = iColumn;
				attack.attacker[attack.iNumAttackers - 1].dir = VERTICAL;
				break;
			}
			else
			{
				// There is a piece that does not attack vertically, so no problem
				break;
			}
		}
	}

	// c) Direction: DIAGONAL
	{
		// Check the diagonal up-right
		for (int i = iRow + 1, j = iColumn + 1; i < 8 && j < 8; i++, j++)
		{
			char chPieceFound = getPiece_considerMove(i, j, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(i == iRow + 1) &&
				(j == iColumn + 1) &&
				(iColor == WHITE_PIECE))
			{
				// A pawn only puts another piece in jeopardy if it's (diagonally) right next to it
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else
			{
				// There is a piece that does not attack diagonally, so no problem
				break;
			}
		}

		// Check the diagonal up-left
		for (int i = iRow + 1, j = iColumn - 1; i < 8 && j > 0; i++, j--)
		{
			char chPieceFound = getPiece_considerMove(i, j, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(i == iRow + 1) &&
				(j == iColumn - 1) &&
				(iColor == WHITE_PIECE))
			{
				// A pawn only puts another piece in jeopardy if it's (diagonally) right next to it
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else
			{
				// There is a piece that does not attack diagonally, so no problem
				break;
			}
		}

		// Check the diagonal down-right
		for (int i = iRow - 1, j = iColumn + 1; i > 0 && j < 8; i--, j++)
		{
			char chPieceFound = getPiece_considerMove(i, j, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(i == iRow - 1) &&
				(j == iColumn + 1) &&
				(iColor == BLACK_PIECE))
			{
				// A pawn only puts another piece in jeopardy if it's (diagonally) right next to it
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else
			{
				// There is a piece that does not attack diagonally, so no problem
				break;
			}
		}

		// Check the diagonal down-left
		for (int i = iRow - 1, j = iColumn - 1; i > 0 && j > 0; i--, j--)
		{
			char chPieceFound = getPiece_considerMove(i, j, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(i == iRow - 1) &&
				(j == iColumn - 1) &&
				(iColor == BLACK_PIECE))
			{
				// A pawn only puts another piece in jeopardy if it's (diagonally) right next to it
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the piece is in jeopardy
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = i;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = j;
				attack.attacker[attack.iNumAttackers - 1].dir = DIAGONAL;
				break;
			}
			else
			{
				// There is a piece that does not attack diagonally, so no problem
				break;
			}
		}
	}

	// d) Direction: L_SHAPED
	{
		// Check if the piece is put in jeopardy by a knigh

		Position knight_moves[8] = { {  1, -2 }, {  2, -1 }, {  2, 1 }, {  1, 2 },
									 { -1, -2 }, { -2, -1 }, { -2, 1 }, { -1, 2 } };
		for (int i = 0; i < 8; i++)
		{
			int iRowToTest = iRow + knight_moves[i].iRow;
			int iColumnToTest = iColumn + knight_moves[i].iColumn;

			if (iRowToTest < 0 || iRowToTest > 7 || iColumnToTest < 0 || iColumnToTest > 7)
			{
				// This square does not even exist, so no need to test
				continue;
			}

			char chPieceFound = getPiece_considerMove(iRowToTest, iColumnToTest, pintended_move);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color, so no problem
				continue;
			}
			else if ((toupper(chPieceFound) == 'N'))
			{
				attack.bUnderAttack = true;
				attack.iNumAttackers += 1;

				attack.attacker[attack.iNumAttackers - 1].pos.iRow = iRowToTest;
				attack.attacker[attack.iNumAttackers - 1].pos.iColumn = iColumnToTest;
				break;
			}
		}
	}

	return attack;
}

bool Game::isReachable(int iRow, int iColumn, int iColor)
{
	bool bReachable = false;

	// a) Direction: HORIZONTAL
	{
		// Check all the way to the right
		for (int i = iColumn + 1; i < 8; i++)
		{
			char chPieceFound = getPieceAtPosition(iRow, i);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the right, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move horizontally
				break;
			}
		}

		// Check all the way to the left
		for (int i = iColumn - 1; i >= 0; i--)
		{
			char chPieceFound = getPieceAtPosition(iRow, i);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook to the left, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move horizontally
				break;
			}
		}
	}

	// b) Direction: VERTICAL
	{
		// Check all the way up
		for (int i = iRow + 1; i < 8; i++)
		{
			char chPieceFound = getPieceAtPosition(i, iColumn);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(getPieceColor(chPieceFound) == BLACK_PIECE) &&
				(i == iRow + 1))
			{
				// There is a pawn one square up, so the square is reachable
				bReachable = true;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook on the way up, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move vertically
				break;
			}
		}

		// Check all the way down
		for (int i = iRow - 1; i >= 0; i--)
		{
			char chPieceFound = getPieceAtPosition(i, iColumn);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'P') &&
				(getPieceColor(chPieceFound) == WHITE_PIECE) &&
				(i == iRow - 1))
			{
				// There is a pawn one square down, so the square is reachable
				bReachable = true;
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'R'))
			{
				// There is a queen or a rook on the way down, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move vertically
				break;
			}
		}
	}

	// c) Direction: DIAGONAL
	{
		// Check the diagonal up-right
		for (int i = iRow + 1, j = iColumn + 1; i < 8 && j < 8; i++, j++)
		{
			char chPieceFound = getPieceAtPosition(i, j);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move diagonally
				break;
			}
		}

		// Check the diagonal up-left
		for (int i = iRow + 1, j = iColumn - 1; i < 8 && j > 0; i++, j--)
		{
			char chPieceFound = getPieceAtPosition(i, j);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move diagonally
				break;
			}
		}

		// Check the diagonal down-right
		for (int i = iRow - 1, j = iColumn + 1; i > 0 && j < 8; i--, j++)
		{
			char chPieceFound = getPieceAtPosition(i, j);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move diagonally
				break;
			}
		}

		// Check the diagonal down-left
		for (int i = iRow - 1, j = iColumn - 1; i > 0 && j > 0; i--, j--)
		{
			char chPieceFound = getPieceAtPosition(i, j);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				break;
			}
			else if ((toupper(chPieceFound) == 'Q') ||
				(toupper(chPieceFound) == 'B'))
			{
				// There is a queen or a bishop in that direction, so the square is reachable
				bReachable = true;
				break;
			}
			else
			{
				// There is a piece that does not move diagonally
				break;
			}
		}
	}

	// d) Direction: L_SHAPED
	{
		// Check if the piece is put in jeopardy by a knigh

		Position knight_moves[8] = { {  1, -2 }, {  2, -1 }, {  2, 1 }, {  1, 2 },
									 { -1, -2 }, { -2, -1 }, { -2, 1 }, { -1, 2 } };
		for (int i = 0; i < 8; i++)
		{
			int iRowToTest = iRow + knight_moves[i].iRow;
			int iColumnToTest = iColumn + knight_moves[i].iColumn;

			if (iRowToTest < 0 || iRowToTest > 7 || iColumnToTest < 0 || iColumnToTest > 7)
			{
				// This square does not even exist, so no need to test
				continue;
			}

			char chPieceFound = getPieceAtPosition(iRowToTest, iColumnToTest);
			if (EMPTY_SQUARE == chPieceFound)
			{
				// This square is empty, move on
				continue;
			}

			if (iColor == getPieceColor(chPieceFound))
			{
				// This is a piece of the same color
				continue;
			}
			else if ((toupper(chPieceFound) == 'N'))
			{
				bReachable = true;
				break;
			}
		}
	}

	return bReachable;
}

bool Game::isSquareOccupied(int iRow, int iColumn)
{
	bool bOccupied = false;

	if (0x20 != getPieceAtPosition(iRow, iColumn))
	{
		bOccupied = true;
	}

	return bOccupied;
}

bool Game::isPathFree(Position startingPos, Position finishingPos, int iDirection)
{
	bool bFree = false;

	switch (iDirection)
	{
	case chess::HORIZONTAL:
	{
		// If it is a horizontal move, we can assume the startingPos.iRow == finishingPos.iRow
		// If the piece wants to move from column 0 to column 7, we must check if columns 1-6 are free
		if (startingPos.iColumn == finishingPos.iColumn)
		{
			cout << "Error. Movement is horizontal but column is the same\n";
		}

		// Moving to the right
		else if (startingPos.iColumn < finishingPos.iColumn)
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = startingPos.iColumn + 1; i < finishingPos.iColumn; i++)
			{
				if (isSquareOccupied(startingPos.iRow, i))
				{
					bFree = false;
					cout << "Horizontal path to the right is not clear!\n";
				}
			}
		}

		// Moving to the left
		else //if (startingPos.iColumn > finishingPos.iColumn)
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = startingPos.iColumn - 1; i > finishingPos.iColumn; i--)
			{
				if (isSquareOccupied(startingPos.iRow, i))
				{
					bFree = false;
					cout << "Horizontal path to the left is not clear!\n";
				}
			}
		}
	}
	break;

	case chess::VERTICAL:
	{
		// If it is a vertical move, we can assume the startingPos.iColumn == finishingPos.iColumn
		// If the piece wants to move from column 0 to column 7, we must check if columns 1-6 are free
		if (startingPos.iRow == finishingPos.iRow)
		{
			cout << "Error. Movement is vertical but row is the same\n";
			throw("Error. Movement is vertical but row is the same");
		}

		// Moving up
		else if (startingPos.iRow < finishingPos.iRow)
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = startingPos.iRow + 1; i < finishingPos.iRow; i++)
			{
				if (isSquareOccupied(i, startingPos.iColumn))
				{
					bFree = false;
					cout << "Vertical path up is not clear!\n";
				}
			}
		}

		// Moving down
		else //if (startingPos.iColumn > finishingPos.iRow)
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = startingPos.iRow - 1; i > finishingPos.iRow; i--)
			{
				if (isSquareOccupied(i, startingPos.iColumn))
				{
					bFree = false;
					cout << "Vertical path down is not clear!\n";
				}
			}
		}
	}
	break;

	case chess::DIAGONAL:
	{
		// Moving up and right
		if ((finishingPos.iRow > startingPos.iRow) && (finishingPos.iColumn > startingPos.iColumn))
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (isSquareOccupied(startingPos.iRow + i, startingPos.iColumn + i))
				{
					bFree = false;
					cout << "Diagonal path up-right is not clear!\n";
				}
			}
		}

		// Moving up and left
		else if ((finishingPos.iRow > startingPos.iRow) && (finishingPos.iColumn < startingPos.iColumn))
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (isSquareOccupied(startingPos.iRow + i, startingPos.iColumn - i))
				{
					bFree = false;
					cout << "Diagonal path up-left is not clear!\n";
				}
			}
		}

		// Moving down and right
		else if ((finishingPos.iRow < startingPos.iRow) && (finishingPos.iColumn > startingPos.iColumn))
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (isSquareOccupied(startingPos.iRow - i, startingPos.iColumn + i))
				{
					bFree = false;
					cout << "Diagonal path down-right is not clear!\n";
				}
			}
		}

		// Moving down and left
		else if ((finishingPos.iRow < startingPos.iRow) && (finishingPos.iColumn < startingPos.iColumn))
		{
			// Settting bFree as initially true, only inside the cases, guarantees that the path is checked
			bFree = true;

			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (isSquareOccupied(startingPos.iRow - i, startingPos.iColumn - i))
				{
					bFree = false;
					cout << "Diagonal path down-left is not clear!\n";
				}
			}
		}

		else
		{
			throw("Error. Diagonal move not allowed");
		}
	}
	break;
	}

	return bFree;
}

bool Game::canBeBlocked(Position startingPos, Position finishingPos, int iDirection)
{
	bool bBlocked = false;

	chess::UnderAttack blocker = { 0 };

	switch (iDirection)
	{
	case chess::HORIZONTAL:
	{
		// If it is a horizontal move, we can assume the startingPos.iRow == finishingPos.iRow
		// If the piece wants to move from column 0 to column 7, we must check if columns 1-6 are free
		if (startingPos.iColumn == finishingPos.iColumn)
		{
			cout << "Error. Movement is horizontal but column is the same\n";
		}

		// Moving to the right
		else if (startingPos.iColumn < finishingPos.iColumn)
		{
			for (int i = startingPos.iColumn + 1; i < finishingPos.iColumn; i++)
			{
				if (true == isReachable(startingPos.iRow, i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		// Moving to the left
		else //if (startingPos.iColumn > finishingPos.iColumn)
		{
			for (int i = startingPos.iColumn - 1; i > finishingPos.iColumn; i--)
			{
				if (true == isReachable(startingPos.iRow, i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}
	}
	break;

	case chess::VERTICAL:
	{
		// If it is a vertical move, we can assume the startingPos.iColumn == finishingPos.iColumn
		// If the piece wants to move from column 0 to column 7, we must check if columns 1-6 are free
		if (startingPos.iRow == finishingPos.iRow)
		{
			cout << "Error. Movement is vertical but row is the same\n";
			throw("Error. Movement is vertical but row is the same");
		}

		// Moving up
		else if (startingPos.iRow < finishingPos.iRow)
		{
			for (int i = startingPos.iRow + 1; i < finishingPos.iRow; i++)
			{
				if (true == isReachable(i, startingPos.iColumn, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		// Moving down
		else //if (startingPos.iColumn > finishingPos.iRow)
		{
			for (int i = startingPos.iRow - 1; i > finishingPos.iRow; i--)
			{
				if (true == isReachable(i, startingPos.iColumn, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}
	}
	break;

	case chess::DIAGONAL:
	{
		// Moving up and right
		if ((finishingPos.iRow > startingPos.iRow) && (finishingPos.iColumn > startingPos.iColumn))
		{
			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (true == isReachable(startingPos.iRow + i, startingPos.iColumn + i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		// Moving up and left
		else if ((finishingPos.iRow > startingPos.iRow) && (finishingPos.iColumn < startingPos.iColumn))
		{
			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (true == isReachable(startingPos.iRow + i, startingPos.iColumn - i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		// Moving down and right
		else if ((finishingPos.iRow < startingPos.iRow) && (finishingPos.iColumn > startingPos.iColumn))
		{
			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (true == isReachable(startingPos.iRow - i, startingPos.iColumn + i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		// Moving down and left
		else if ((finishingPos.iRow < startingPos.iRow) && (finishingPos.iColumn < startingPos.iColumn))
		{
			for (int i = 1; i < abs(finishingPos.iRow - startingPos.iRow); i++)
			{
				if (true == isReachable(startingPos.iRow - i, startingPos.iColumn - i, getOpponentColor()))
				{
					// Some piece can block the way
					bBlocked = true;
				}
			}
		}

		else
		{
			cout << "Error. Diagonal move not allowed\n";
			throw("Error. Diagonal move not allowed");
		}
	}
	break;
	}

	return bBlocked;
}

bool Game::isCheckMate()
{
	bool bCheckmate = false;

	// 1. First of all, it the king in check?
	if (false == playerKingInCheck())
	{
		return false;
	}

	// 2. Can the king move the other square?
	chess::Position king_moves[8] = { {  1, -1 },{  1, 0 },{  1,  1 }, { 0,  1 },
									   { -1,  1 },{ -1, 0 },{ -1, -1 }, { 0, -1 } };

	chess::Position king = findKing(getCurrentTurn());

	for (int i = 0; i < 8; i++)
	{
		int iRowToTest = king.iRow + king_moves[i].iRow;
		int iColumnToTest = king.iColumn + king_moves[i].iColumn;

		if (iRowToTest < 0 || iRowToTest > 7 || iColumnToTest < 0 || iColumnToTest > 7)
		{
			// This square does not even exist, so no need to test
			continue;
		}

		if (EMPTY_SQUARE != getPieceAtPosition(iRowToTest, iColumnToTest))
		{
			// That square is not empty, so no need to test
			continue;
		}

		chess::IntendedMove intended_move;
		intended_move.chPiece = getPieceAtPosition(king.iRow, king.iColumn);
		intended_move.from.iRow = king.iRow;
		intended_move.from.iColumn = king.iColumn;
		intended_move.to.iRow = iRowToTest;
		intended_move.to.iColumn = iColumnToTest;

		// Now, for every possible move of the king, check if it would be in jeopardy
		// Since the move has already been made, current_game->getCurrentTurn() now will return 
		// the next player's color. And it is in fact this king that we want to check for jeopardy
		chess::UnderAttack king_moved = isUnderAttack(iRowToTest, iColumnToTest, getCurrentTurn(), &intended_move);

		if (false == king_moved.bUnderAttack)
		{
			// This means there is at least one position when the king would not be in jeopardy, so that's not a checkmate
			return false;
		}
	}

	// 3. Can the attacker be taken or another piece get into the way? 
	chess::UnderAttack king_attacked = isUnderAttack(king.iRow, king.iColumn, getCurrentTurn());
	if (1 == king_attacked.iNumAttackers)
	{
		// Can the attacker be taken?
		chess::UnderAttack king_attacker = { 0 };
		king_attacker = isUnderAttack(king_attacked.attacker[0].pos.iRow, king_attacked.attacker[0].pos.iColumn, getOpponentColor());

		if (true == king_attacker.bUnderAttack)
		{
			// This means that the attacker can be taken, so it's not a checkmate
			return false;
		}
		else
		{
			// Last resort: can any piece get in between the attacker and the king?
			char chAttacker = getPieceAtPosition(king_attacked.attacker[0].pos.iRow, king_attacked.attacker[0].pos.iColumn);

			switch (toupper(chAttacker))
			{
			case 'P':
			case 'N':
			{
				// If it's a pawn, there's no space in between the attacker and the king
				// If it's a knight, it doesn't matter because the knight can 'jump'
				// So, this is checkmate
				bCheckmate = true;
			}
			break;

			case 'B':
			{
				if (false == canBeBlocked(king_attacked.attacker[0].pos, king, chess::DIAGONAL))
				{
					// If no piece can get in the way, it's a checkmate
					bCheckmate = true;
				}
			}
			break;

			case 'R':
			{
				if (false == canBeBlocked(king_attacked.attacker[0].pos, king, king_attacked.attacker[0].dir))
				{
					// If no piece can get in the way, it's a checkmate
					bCheckmate = true;
				}
			}
			break;

			case 'Q':
			{
				if (false == canBeBlocked(king_attacked.attacker[0].pos, king, king_attacked.attacker[0].dir))
				{
					// If no piece can get in the way, it's a checkmate
					bCheckmate = true;
				}
			}
			break;


			default:
			{
				throw("!!!!Should not reach here. Invalid piece");
			}
			break;
			}
		}
	}
	else
	{
		// If there is more than one attacker and we reached this point, it's a checkmate
		bCheckmate = true;
	}

	// If the game has ended, store in the class variable
	m_bGameFinished = bCheckmate;

	return bCheckmate;
}

bool Game::isKingInCheck(int iColor, IntendedMove* pintended_move)
{
	bool bCheck = false;

	Position king = { 0 };

	// Must check if the intended move is to move the king itself
	if (nullptr != pintended_move && 'K' == toupper(pintended_move->chPiece))
	{
		king.iRow = pintended_move->to.iRow;
		king.iColumn = pintended_move->to.iColumn;
	}
	else
	{
		king = findKing(iColor);
	}

	UnderAttack king_attacked = isUnderAttack(king.iRow, king.iColumn, iColor, pintended_move);

	if (true == king_attacked.bUnderAttack)
	{
		bCheck = true;
	}

	return bCheck;
}

bool Game::playerKingInCheck(IntendedMove* intended_move)
{
	return isKingInCheck(getCurrentTurn(), intended_move);
}

bool Game::wouldKingBeInCheck(char chPiece, Position present, Position future)
{
	IntendedMove intended_move;

	intended_move.chPiece = chPiece;
	intended_move.from.iRow = present.iRow;
	intended_move.from.iColumn = present.iColumn;
	intended_move.to.iRow = future.iRow;
	intended_move.to.iColumn = future.iColumn;

	return playerKingInCheck(&intended_move);
}

chess::Position Game::findKing(int iColor)
{
	char chToLook = (WHITE_PIECE == iColor) ? 'K' : 'k';
	Position king = { 0 };

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chToLook == getPieceAtPosition(i, j))
			{
				king.iRow = i;
				king.iColumn = j;
			}
		}
	}

	return king;
}

void Game::changeTurns(void)
{
	if (WHITE_PLAYER == m_CurrentTurn)
	{
		m_CurrentTurn = BLACK_PLAYER;
	}
	else
	{
		m_CurrentTurn = WHITE_PLAYER;
	}
}

bool Game::isFinished(void)
{
	return m_bGameFinished;
}

int Game::getCurrentTurn(void)
{
	return m_CurrentTurn;
}

int Game::getOpponentColor(void)
{
	int iColor;

	if (chess::WHITE_PLAYER == getCurrentTurn())
	{
		iColor = chess::BLACK_PLAYER;
	}
	else
	{
		iColor = chess::WHITE_PLAYER;
	}

	return iColor;
}

void Game::parseMove(string move, Position* pFrom, Position* pTo, char* chPromoted)
{
	pFrom->iColumn = move[0];
	pFrom->iRow = move[1];
	pTo->iColumn = move[3];
	pTo->iRow = move[4];

	// Convert columns from ['A'-'H'] to [0x00-0x07]
	pFrom->iColumn = pFrom->iColumn - 'A';
	pTo->iColumn = pTo->iColumn - 'A';

	// Convert row from ['1'-'8'] to [0x00-0x07]
	pFrom->iRow = pFrom->iRow - '1';
	pTo->iRow = pTo->iRow - '1';

	if (chPromoted != nullptr)
	{
		if (move[5] == '=')
		{
			*chPromoted = move[6];
		}
		else
		{
			*chPromoted = EMPTY_SQUARE;
		}
	}
}
