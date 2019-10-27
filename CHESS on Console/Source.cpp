//Chess rules are studied from www.chesshouse.com and implemented as they are
#include <iostream>
//#include <iomanip>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

#include "UInterface.h"
#include "chess.h"



Game* current_game = NULL;



// Helper functions to determine if a move is valid, etc
bool isMoveValid(chess::Position present, chess::Position future, chess::Promotion* S_promotion)
{
	bool bValid = false;

	char chPiece = current_game->getPieceAtPosition(present.iRow, present.iColumn);


	// Is the piece  allowed to move in that direction?

	switch (toupper(chPiece))
	{
	case 'P':
	{
		// Wants to move forward
		if (future.iColumn == present.iColumn)
		{
			// Simple move forward
			if ((chess::isWhitePiece(chPiece) && future.iRow == present.iRow + 1) ||
				(chess::isBlackPiece(chPiece) && future.iRow == present.iRow - 1))
			{
				if (EMPTY_SQUARE == current_game->getPieceAtPosition(future.iRow, future.iColumn))
				{
					bValid = true;
				}
			}

			// Double move forward
			else if ((chess::isWhitePiece(chPiece) && future.iRow == present.iRow + 2) ||
				(chess::isBlackPiece(chPiece) && future.iRow == present.iRow - 2))
			{
				// This is only allowed if the pawn is in its original place
				if (chess::isWhitePiece(chPiece))
				{
					if (EMPTY_SQUARE == current_game->getPieceAtPosition(future.iRow - 1, future.iColumn) &&
						EMPTY_SQUARE == current_game->getPieceAtPosition(future.iRow, future.iColumn) &&
						1 == present.iRow)
					{
						bValid = true;
					}
				}
				else // if ( isBlackPiece(chPiece) )
				{
					if (EMPTY_SQUARE == current_game->getPieceAtPosition(future.iRow + 1, future.iColumn) &&
						EMPTY_SQUARE == current_game->getPieceAtPosition(future.iRow, future.iColumn) &&
						6 == present.iRow)
					{
						bValid = true;
					}
				}
			}
			else
			{
				// This is invalid
				return false;
			}
		}

		
		// Wants to capture a piece
		else if (1 == abs(future.iColumn - present.iColumn))
		{
			if ((chess::isWhitePiece(chPiece) && future.iRow == present.iRow + 1) || (chess::isBlackPiece(chPiece) && future.iRow == present.iRow - 1))
			{
				// Only allowed if there is something to be captured in the square
				if (EMPTY_SQUARE != current_game->getPieceAtPosition(future.iRow, future.iColumn))
				{
					bValid = true;
					cout << "\t\t\t\tPawn captured a piece!\n";
				}
			}
		}
		else
		{
			// This is invalid
			return false;
		}

		// If a pawn reaches its eight rank, it must be promoted to another piece
		if ((chess::isWhitePiece(chPiece) && 7 == future.iRow) ||
			(chess::isBlackPiece(chPiece) && 0 == future.iRow))
		{
			cout << "\t\t\t\tPawn must be promoted!\n";
			S_promotion->bApplied = true;
		}
	}
	break;

	case 'R':
	{
		// Horizontal move
		if ((future.iRow == present.iRow) && (future.iColumn != present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::HORIZONTAL))
			{
				bValid = true;
			}
		}
		// Vertical move
		else if ((future.iRow != present.iRow) && (future.iColumn == present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::VERTICAL))
			{
				bValid = true;
			}
		}
	}
	break;

	case 'N':
	{
		if ((2 == abs(future.iRow - present.iRow)) && (1 == abs(future.iColumn - present.iColumn)))
		{
			bValid = true;
		}

		else if ((1 == abs(future.iRow - present.iRow)) && (2 == abs(future.iColumn - present.iColumn)))
		{
			bValid = true;
		}
	}
	break;

	case 'B':
	{
		// Diagonal move
		if (abs(future.iRow - present.iRow) == abs(future.iColumn - present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::DIAGONAL))
			{
				bValid = true;
			}
		}
	}
	break;

	case 'Q':
	{
		// Horizontal move
		if ((future.iRow == present.iRow) && (future.iColumn != present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::HORIZONTAL))
			{
				bValid = true;
			}
		}
		// Vertical move
		else if ((future.iRow != present.iRow) && (future.iColumn == present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::VERTICAL))
			{
				bValid = true;
			}
		}

		// Diagonal move
		else if (abs(future.iRow - present.iRow) == abs(future.iColumn - present.iColumn))
		{
			// Check if there are no pieces on the way
			if (current_game->isPathFree(present, future, chess::DIAGONAL))
			{
				bValid = true;
			}
		}
	}
	break;

	case 'K':
	{
		// Horizontal move by 1
		if ((future.iRow == present.iRow) && (1 == abs(future.iColumn - present.iColumn)))
		{
			bValid = true;
		}

		// Vertical move by 1
		else if ((future.iColumn == present.iColumn) && (1 == abs(future.iRow - present.iRow)))
		{
			bValid = true;
		}

		// Diagonal move by 1
		else if ((1 == abs(future.iRow - present.iRow)) && (1 == abs(future.iColumn - present.iColumn)))
		{
			bValid = true;
		}
	}
	break;

	default:
	{
		cout << "\t\t\t\tShould not reach here. Invalid piece: " << char(chPiece) << "\n\n\n";
	}
	break;
	}

	// If it is a move in an invalid direction, do not even bother to check the rest
	if (false == bValid)
	{
		cout << "\t\t\t\tPiece is not allowed to move to that square\n";
		return false;
	}


	// -------------------------------------------------------------------------
	// 2. Is there another piece of the same color on the destination square?
	// -------------------------------------------------------------------------
	if (current_game->isSquareOccupied(future.iRow, future.iColumn))
	{
		char chTempPiece = current_game->getPieceAtPosition(future.iRow, future.iColumn);
		if (chess::getPieceColor(chPiece) == chess::getPieceColor(chTempPiece))
		{
			cout << "\t\t\t\tPosition is already taken by a piece of the same color\n";
			return false;
		}
	}

	// ----------------------------------------------
	// 3. Would the king be in check after the move?
	// ----------------------------------------------
	if (true == current_game->wouldKingBeInCheck(chPiece, present, future))
	{
		cout << "\t\t\t\tMove would put player's king in check\n";
		return false;
	}

	return bValid;
}

void makeTheMove(chess::Position present, chess::Position future, chess::Promotion* S_promotion)
{
	char chPiece = current_game->getPieceAtPosition(present.iRow, present.iColumn);

	// -----------------------
	// Captured a piece?
	// -----------------------
	if (current_game->isSquareOccupied(future.iRow, future.iColumn))
	{
		char chAuxPiece = current_game->getPieceAtPosition(future.iRow, future.iColumn);

		if (chess::getPieceColor(chPiece) != chess::getPieceColor(chAuxPiece))
		{
			createNextMessage("\t\t\t\t"+chess::describePiece(chAuxPiece) + " captured!\n");
		}
		else
		{
			cout << "\t\t\t\tError. We should not be making this move\n";
			throw("\t\t\t\tError. We should not be making this move");
		}
	}




	current_game->movePiece(present, future, S_promotion);
}



void movePiece(void)
{
	std::string to_record;

	// Get user input for the piece they want to move
	cout << "\t\t\t\tChoose piece to be moved. (example: A1 or b2): ";

	std::string move_from;
	getline(cin, move_from);

	if (move_from.length() > 2)
	{
		createNextMessage("\t\t\t\tYou should type only two characters (column and row)\n");
		return;
	}

	chess::Position present;
	present.iColumn = move_from[0];
	present.iRow = move_from[1];

	// ---------------------------------------------------
	// Did the user pick a valid piece?
	// Must check if:
	// - It's inside the board (A1-H8)
	// - There is a piece in the square
	// - The piece is consistent with the player's turn
	// ---------------------------------------------------
	present.iColumn = toupper(present.iColumn);

	if (present.iColumn < 'A' || present.iColumn > 'H')
	{
		createNextMessage("\t\t\t\tInvalid column.\n");
		return;
	}

	if (present.iRow < '0' || present.iRow > '8')
	{
		createNextMessage("\t\t\t\tInvalid row.\n");
		return;
	}

	// Put in the string to be logged
	to_record += present.iColumn;
	to_record += present.iRow;
	to_record += "-";

	// Convert column from ['A'-'H'] to [0x00-0x07]
	present.iColumn = present.iColumn - 'A';

	// Convert row from ['1'-'8'] to [0x00-0x07]
	present.iRow = present.iRow - '1';

	char chPiece = current_game->getPieceAtPosition(present.iRow, present.iColumn);
	cout << "\t\t\t\tPiece is " << char(chPiece) << "\n";

	if (0x20 == chPiece)
	{
		createNextMessage("\t\t\t\tYou picked an EMPTY square.\n");
		return;
	}

	if (chess::WHITE_PIECE == current_game->getCurrentTurn())
	{
		if (false == chess::isWhitePiece(chPiece))
		{
			createNextMessage("\t\t\t\tIt is WHITE's turn and you picked a BLACK piece\n");
			return;
		}
	}
	else
	{
		if (false == chess::isBlackPiece(chPiece))
		{
			createNextMessage("\t\t\t\tIt is BLACK's turn and you picked a WHITE piece\n");
			return;
		}
	}

	// ---------------------------------------------------
	// Get user input for the square to move to
	// ---------------------------------------------------
	cout << "\t\t\t\tMove to: ";
	std::string move_to;
	getline(cin, move_to);

	if (move_to.length() > 2)
	{
		createNextMessage("\t\t\t\tYou should type only two characters (column and row)\n");
		return;
	}

	// ---------------------------------------------------
	// Did the user pick a valid house to move?
	// Must check if:
	// - It's inside the board (A1-H8)
	// - The move is valid
	// ---------------------------------------------------
	chess::Position future;
	future.iColumn = move_to[0];
	future.iRow = move_to[1];

	future.iColumn = toupper(future.iColumn);

	if (future.iColumn < 'A' || future.iColumn > 'H')
	{
		createNextMessage("\t\t\t\tInvalid column.\n");
		return;
	}

	if (future.iRow < '0' || future.iRow > '8')
	{
		createNextMessage("\t\t\t\tInvalid row.\n");
		return;
	}

	// Put in the string to be logged
	to_record += future.iColumn;
	to_record += future.iRow;

	// Convert columns from ['A'-'H'] to [0x00-0x07]
	future.iColumn = future.iColumn - 'A';

	// Convert row from ['1'-'8'] to [0x00-0x07]
	future.iRow = future.iRow - '1';

	// Check if it is not the exact same square
	if (future.iRow == present.iRow && future.iColumn == present.iColumn)
	{
		createNextMessage("\t\t\t\t[Invalid] You picked the same square!\n");
		return;
	}

	// Is that move allowed?

	chess::Promotion  S_promotion = { 0 };

	if (false == isMoveValid(present, future, &S_promotion))
	{
		createNextMessage("\t\t\t\t[Invalid] Piece can not move to that square!\n");
		return;
	}

	// ---------------------------------------------------
	// Promotion: user most choose a piece to
	// replace the pawn
	// ---------------------------------------------------
	if (S_promotion.bApplied == true)
	{
		cout << "\t\t\t\tPromote to (Q, R, N, B): ";
		std::string piece;
		getline(cin, piece);

		if (piece.length() > 1)
		{
			createNextMessage("\t\t\t\tYou should type only one character (Q, R, N or B)\n");
			return;
		}

		char chPromoted = toupper(piece[0]);

		if (chPromoted != 'Q' && chPromoted != 'R' && chPromoted != 'N' && chPromoted != 'B')
		{
			createNextMessage("\t\t\t\tInvalid character.\n");
			return;
		}

		S_promotion.chBefore = current_game->getPieceAtPosition(present.iRow, present.iColumn);

		if (chess::WHITE_PLAYER == current_game->getCurrentTurn())
		{
			S_promotion.chAfter = toupper(chPromoted);
		}
		else
		{
			S_promotion.chAfter = tolower(chPromoted);
		}

	}

	// ---------------------------------------------------
	// Make the move
	// ---------------------------------------------------
	makeTheMove(present, future, &S_promotion);

	// ---------------------------------------------------------------
	// Check if this move we just did put the oponent's king in check
	// Keep in mind that player turn has already changed
	// ---------------------------------------------------------------
	if (true == current_game->playerKingInCheck())
	{
		if (true == current_game->isCheckMate())
		{
			if (chess::WHITE_PLAYER == current_game->getCurrentTurn())
			{
				appendToNextMessage("\t\t\t\tCheckmate! Black wins the game!\n");
			}
			else
			{
				appendToNextMessage("\t\t\t\tCheckmate! White wins the game!\n");
			}
		}
		else
		{
			// Add to the string with '+=' because it's possible that
			// there is already one message (e.g., piece captured)
			if (chess::WHITE_PLAYER == current_game->getCurrentTurn())
			{
				appendToNextMessage("\t\t\t\tWhite king is in check!\n");
			}
			else
			{
				appendToNextMessage("\t\t\t\tBlack king is in check!\n");
			}
		}
	}

	return;
}



int main()
{
	bool bRun = true;

	current_game = new Game();
	printCaptured(*current_game);
	printBoard(*current_game);

	while (bRun)
	{
		printMessage();

		
		//using try-throw-catch to handle exceptions properly
		try
		{
			if (NULL != current_game)
			{
				if (current_game->isFinished())
				{
					cout << "\t\t\t\tThis game has already finished!\n";
					bRun = false;
				}
				else
				{
					movePiece();
					cin.get();
					clearScreen();
					printCaptured(*current_game);
					printBoard(*current_game);
				}
			}
			else
			{
				cout << "\t\t\t\tNo game running!\n";
			}
		}
		catch (const char* s)
		{
			s;
		}
	}

	system("PAUSE");
	return 0;
}
