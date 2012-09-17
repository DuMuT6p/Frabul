/*
* Copyright (C) 2012 Frabul programmers
* 
* This file is part of Frabul.
* 
* Frabul is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Frabul is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Frabul.  If not, see <http://www.gnu.org/licenses/>.
*/

#include	"Board.h"

Board::		Board()
	: distancetocenter(),rookLW(false),rookRW(false),rookLB(false),rookRB(false),kingW(false),kingB(false)
	,poolObject(PoolObject::getInstance()),depthOption(5),phase("startGame"),bookpos(0),winboard(false)
{

	unsigned int		i;

	for (i = 0; i < 120; ++i)
		board[i] = 'e';

	srand ( time(NULL) );

	// opponent
	board[0x70] = 'R'; board[0x71] = 'H'; board[0x72] = 'B'; board[0x74] = 'K';
	board[0x73] = 'Q'; board[0x75] = 'B'; board[0x76] = 'H'; board[0x77] = 'R';
	board[0x60] = 'P'; board[0x61] = 'P'; board[0x62] = 'P'; board[0x63] = 'P';
	board[0x64] = 'P'; board[0x65] = 'P'; board[0x66] = 'P'; board[0x67] = 'P';

	// player
	board[0x00] = 'r'; board[0x01] = 'h'; board[0x02] = 'b'; board[0x03] = 'q';
	board[0x04] = 'k'; board[0x05] = 'b'; board[0x06] = 'h'; board[0x07] = 'r';
	board[0x10] = 'p'; board[0x11] = 'p'; board[0x12] = 'p'; board[0x13] = 'p';
	board[0x14] = 'p'; board[0x15] = 'p'; board[0x16] = 'p'; board[0x17] = 'p';

	distancetocenter[0x00] = 6; distancetocenter[0x01] = 5; distancetocenter[0x02] = 4; distancetocenter[0x03] = 3;
	distancetocenter[0x04] = 3; distancetocenter[0x05] = 4; distancetocenter[0x06] = 5; distancetocenter[0x07] = 6;

	distancetocenter[0x10] = 5; distancetocenter[0x11] = 4; distancetocenter[0x12] = 3; distancetocenter[0x13] = 2;
	distancetocenter[0x14] = 2; distancetocenter[0x15] = 3; distancetocenter[0x16] = 4; distancetocenter[0x17] = 5;

	distancetocenter[0x20] = 4; distancetocenter[0x21] = 3; distancetocenter[0x22] = 2; distancetocenter[0x23] = 1;
	distancetocenter[0x24] = 1; distancetocenter[0x25] = 2; distancetocenter[0x26] = 3; distancetocenter[0x27] = 4;

	distancetocenter[0x30] = 3; distancetocenter[0x31] = 2; distancetocenter[0x32] = 1; distancetocenter[0x33] = 0;
	distancetocenter[0x34] = 0; distancetocenter[0x35] = 1; distancetocenter[0x36] = 2; distancetocenter[0x37] = 3;

	distancetocenter[0x40] = 3; distancetocenter[0x41] = 2; distancetocenter[0x42] = 1; distancetocenter[0x43] = 0;
	distancetocenter[0x44] = 0; distancetocenter[0x45] = 1; distancetocenter[0x46] = 2; distancetocenter[0x47] = 3;

	distancetocenter[0x50] = 4; distancetocenter[0x51] = 3; distancetocenter[0x52] = 2; distancetocenter[0x53] = 1;
	distancetocenter[0x54] = 1; distancetocenter[0x55] = 2; distancetocenter[0x56] = 3; distancetocenter[0x57] = 4;

	distancetocenter[0x60] = 5; distancetocenter[0x61] = 4; distancetocenter[0x62] = 3; distancetocenter[0x63] = 2;
	distancetocenter[0x64] = 2; distancetocenter[0x65] = 3; distancetocenter[0x66] = 4; distancetocenter[0x67] = 5;

	distancetocenter[0x70] = 6; distancetocenter[0x71] = 5; distancetocenter[0x72] = 4; distancetocenter[0x73] = 3;
	distancetocenter[0x74] = 3; distancetocenter[0x75] = 4; distancetocenter[0x76] = 5; distancetocenter[0x77] = 6;

	move_history.push_back(new MoveType(10, 10, false, 'e', 'e'));
	player = 'w';

	// Standart for many opening move
	std::vector< MoveType > page;
	page.push_back(MoveType(0x34, 0x14, false, 'P', ' '));
	// TODO: put here additational moves
	book.push_back(page);
	// Reti opening
	std::vector< MoveType > page1;
	page1.push_back(MoveType(0x25, 0x06, false, 'H', ' '));
	// TODO: put here additational moves
	book.push_back(page1);
	// English opening
	std::vector< MoveType > page2;
	page2.push_back(MoveType(0x32, 0x12, false, 'P', ' '));
	// TODO: put here additational moves
	book.push_back(page2);

	// Opening moves
	srand(time(NULL));
	chosenOpening = rand()%book.size(); // modulus number of openings

}

Board::		~Board()
{
}

void
	Board::		init()
{
	// opponent
	board[0x70] = 'r'; board[0x71] = 'h'; board[0x72] = 'b'; board[0x74] = 'k';
	board[0x73] = 'q'; board[0x75] = 'b'; board[0x76] = 'h'; board[0x77] = 'r';
	board[0x60] = 'p'; board[0x61] = 'p'; board[0x62] = 'p'; board[0x63] = 'p';
	board[0x64] = 'p'; board[0x65] = 'p'; board[0x66] = 'p'; board[0x67] = 'p';

	// player
	board[0x00] = 'R'; board[0x01] = 'H'; board[0x02] = 'B'; board[0x03] = 'Q';
	board[0x04] = 'K'; board[0x05] = 'B'; board[0x06] = 'H'; board[0x07] = 'R';
	board[0x10] = 'P'; board[0x11] = 'P'; board[0x12] = 'P'; board[0x13] = 'P';
	board[0x14] = 'P'; board[0x15] = 'P'; board[0x16] = 'P'; board[0x17] = 'P';
}

void
	Board::		run()
{
	flog.open("flog.txt");
	Bookopening.open("bigbook.txt");
	std::cout << "Choose your color: type black or white" << std::endl;
	getline(std::cin, buffer2);
	player = buffer2[0];
	if (buffer2[0] == 'b')
		init();
	if (player == 'b')
		computerTurn(depthOption);

	while (42)
	{
		playerTurn();
		computerTurn(depthOption);
	}
}

void
	Board::     displayPastMoves() const
{
	std::cout << "White`s moves:" << std::endl;
	for(unsigned int i = 0; i < move_history.size(); i+=2)
	{
		MoveType* pastMove = move_history.at(i);
		int _oldmove = pastMove->getOldMove();
		int _newmove = pastMove->getNewMove();
		std::cout << (char)((_oldmove & 0x0F) + 'a') << (char)((_oldmove & 0xF0)/16 + '1') << (char)((_newmove & 0x0F) + 'a') << (char)((_newmove & 0xF0)/16 + '1') << ", ";
	}
	std::cout << std::endl;

	std::cout << "Black`s moves:" << std::endl;
	for(unsigned int i = 1; i < move_history.size(); i+=2)
	{
		MoveType* pastMove = move_history.at(i);
		int _oldmove = pastMove->getOldMove();
		int _newmove = pastMove->getNewMove();
		std::cout << (char)((_oldmove & 0x0F) + 'a') << (char)((_oldmove & 0xF0)/16 + '1') << (char)((_newmove & 0x0F) + 'a') << (char)((_newmove & 0xF0)/16 + '1') << ", ";
	}
	std::cout << std::endl;
}

void
	Board::		displayBoard() const
{
	int		ind = 8;

	displayPastMoves();

	std::cout << "    a   b   c   d   e   f   g   h  " << std::endl << ind-- << " | ";
	for (int i = 0x70, j = 0; i >= 0; ++j)
	{
		std::cout << board[i + j] << " | ";
		if (j == 7)
		{
			if (ind == 0)
				std::cout << std::endl << "    ";
			else
				std::cout << std::endl << ind-- << " | ";
			i -= 0x10; //go to the next line
			j= -1; //the for will increment just after it will be 0
		}
	}
	std::cout <<  "a   b   c   d   e   f   g   h  " << std::endl;

}

int
	Board::     getDistanceToOtherKing() const
{
	int ownKing = -1, opponentKing = -1;
	for(int i = 0x00; i < 0xFF; ++i)
	{
		if(board[i] == 'k')
			ownKing = i;
		if(board[i] == 'K')
			opponentKing = i;

		if(ownKing != -1 && opponentKing != -1)
			break;
	}

	// Chebyshev distance
	int x1 = ownKing & 0x0F;
	int y1 = (ownKing & 0xF0)/16;
	int x2 = opponentKing & 0x0F;
	int y2 = (opponentKing & 0xF0)/16;

	/*  // DEBUG:
	std::cout << "actual coordinates: ownKing = " << ownKing << " opponentKing = " << opponentKing << std::endl;
	std::cout << "x1 = " << x1 << " y1 = " << y1 << " x2 = " << x2 << " y2 = " << y2 << std::endl;
	//    int distance = std::max(std::abs(x2-x1), std::abs(y2-y1));
	*/
	return (std::abs(x2-x1) > std::abs(y2-y1)) ? std::abs(x2-x1) : std::abs(y2-y1);
}


bool
	Board::		isInsideBoard(int position) const
{
	if (position & 0x88)
		return (false);
	return (true);
}

std::vector<MoveType*>*
	Board::		generateLegalMovesForAPiece(int pos) const // placeholder
{
	std::vector<
		MoveType*>	*vect;
	char		piece;
	int		_old;
	int		i;
	int		tmpPosition;

	vect = new std::vector<MoveType*>;
	piece	= board[pos];
	_old = pos;
	switch (piece)
	{
	case 'P':
		for (i = 0; i < 4; ++i)
		{
			if (player == 'w')
			{
				tmpPosition = _old + pawnB[i];
				if ((pawnB[i] != SS || (pawnB[i] == SS && ((0xF0 & _old) == 0x60) && board[_old + SOUTH] == 'e'))
					&& isInsideBoard(tmpPosition))
				{
					if ((board[tmpPosition] >= 'a' && board[tmpPosition] != 'e' && (pawnB[i] == SE || pawnB[i] == SW))
						|| (board[tmpPosition] == 'e' && pawnB[i] != SE && pawnB[i] != SW))
						vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
					/*	else if (move_history.back()->getMovePiece() == 'p'
					&& ((move_history.back()->getNewMove() == (_old + 0x01))
					|| move_history.back()->getNewMove() == (_old - 0x01))
					&& (move_history.back()->getOldMove() & 0xF0) == 0x10)
					vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));*/
				}
			}
			else
			{
				tmpPosition = _old + pawn[i];
				if ((pawn[i] != NN || (pawn[i] == NN && ((0xF0 & _old) == 0x10) && board[_old + NORTH] == 'e'))
					&& isInsideBoard(tmpPosition))
				{
					if ((board[tmpPosition] >= 'a' && board[tmpPosition] != 'e' && (pawn[i] == NE || pawn[i] == NW))
						|| (board[tmpPosition] == 'e' && pawn[i] != NE && pawn[i] != NW))
						vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
					/*else if (move_history.back()->getMovePiece() == 'p'
					&& ((move_history.back()->getNewMove() == (_old + 0x01))
					|| move_history.back()->getNewMove() == (_old - 0x01))
					&& (move_history.back()->getOldMove() & 0xF0) == 0x60)
					vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));*/
				}
			}
		}
		break;
	case 'p':
		for (i = 0; i < 4; ++i)
		{
			if (player == 'w')
			{
				tmpPosition = _old + pawn[i];
				if ((pawn[i] != NN || (pawn[i] == NN && ((0xF0 & _old) == 0x10) && board[_old + NORTH] == 'e'))
					&& isInsideBoard(tmpPosition))
				{
					if ((board[tmpPosition] < 'a' && (pawn[i] == NE || pawn[i] == NW))
						|| (board[tmpPosition] == 'e' && pawn[i] != NE && pawn[i] != NW))
						vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
					/*else if (move_history.back()->getMovePiece() == 'P'
					&& ((move_history.back()->getNewMove() == (_old + 0x01))
					|| move_history.back()->getNewMove() == (_old - 0x01))
					&& (move_history.back()->getOldMove() & 0xF0) == 0x60)
					vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));*/
				}
			}
			else
			{
				tmpPosition = _old + pawnB[i];
				if ((pawnB[i] != SS || (pawnB[i] == SS && ((0xF0 & _old) == 0x60) && board[_old + SOUTH] == 'e'))
					&& isInsideBoard(tmpPosition))
				{
					if ((board[tmpPosition] < 'a' && (pawnB[i] == SE || pawnB[i] == SW))
						|| (board[tmpPosition] == 'e' && pawnB[i] != SE && pawnB[i] != SW))
						vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
					/*else if (move_history.back()->getMovePiece() == 'P'
					&& ((move_history.back()->getNewMove() == (_old + 0x01))
					|| move_history.back()->getNewMove() == (_old - 0x01))
					&& (move_history.back()->getOldMove() & 0xF0) == 0x10)
					vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));*/
				}
			}
		}
		break;
	case 'H':
		for (i = 0; i < 8; ++i)
		{
			tmpPosition = _old + horse[i];
			if (isInsideBoard(tmpPosition))
				if (board[tmpPosition] >= 'a')
					vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
		}
		break;
	case 'h':
		for (i = 0; i < 8; ++i)
		{
			tmpPosition = _old + horse[i];
			if (isInsideBoard(tmpPosition))
				if (board[tmpPosition] < 'a' || board[tmpPosition] == 'e')
					vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
		}
		break;
	case 'K':
		for (i = 0; i < 10; ++i)
		{
			tmpPosition = _old + king[i];
			if (isInsideBoard(tmpPosition))
			{
				if (king[i] == EE || king[i] == WW)
				{
				/*if (player == 'w')
				{
				if (castleKingSideBlack(i)
				|| castleQueenSideBlack(i))
				vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));
				}
				else
				{
				if (castleKingSideWhite(i)
				|| castleQueenSideWhite(i))
				vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));
				}*/
				}
				else if (board[tmpPosition] >= 'a')
					vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'k':
		for (i = 0; i < 10; ++i)
		{
			tmpPosition = _old + king[i];
			if (isInsideBoard(tmpPosition))
			{
				if (king[i] == EE || king[i] == WW)
				{
				/*if (player == 'w')
				{
				if (castleKingSideWhite(i)
				|| castleQueenSideWhite(i))
				vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));
				}
				else
				{
				if (castleKingSideBlack(i)
				|| castleQueenSideBlack(i))
				vect->push_back(poolObject.getObject(tmpPosition, _old, true, piece, board[tmpPosition]));
				}*/
				}
				else if (board[tmpPosition] < 'a'
					|| board[tmpPosition] == 'e')
					vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'R':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + rook[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e' )
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += rook[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] >= 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}

		}
		break;
	case 'r':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + rook[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e' )
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += rook[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] < 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'B':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + bishop[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e' )
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += bishop[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] >= 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'b':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + bishop[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += bishop[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] < 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'Q':
		for (i = 0; i < 8; ++i)
		{
			tmpPosition = _old + queen[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e' )
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += queen[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] >= 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	case 'q':
		for (i = 0; i < 8; ++i)
		{
			tmpPosition = _old + queen[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] == 'e')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
				tmpPosition += queen[i];
			}
			if (isInsideBoard(tmpPosition) && board[tmpPosition] < 'a')
			{
				vect->push_back(poolObject.getObject(tmpPosition, _old, false, piece, board[tmpPosition]));
			}
		}
		break;
	default:
		std::cout << "Error, not a piece" << std::endl;
		break;
	}
	return (vect);
}

int
	Board::		distanceToCenter(int position) const
{
	return (this->distancetocenter[position]);
}

int
	Board::		countEmptyMoves(int position, int direction) const
{
	int		nextPosition = position + direction;
	int		value = 0;


	while (isInsideBoard(nextPosition) && board[nextPosition] == 'e')
	{
		++value;
		nextPosition += direction;
	}
	return (value);
}

float
	Board::		evaluate() const
{
	// changed type to float because of rook formula, should we keep it float only because of rook? (and perhaps a little more precision?)
	float value = 0;
	float temp_value = 0;

	for (int i = 0x00; i < 0x78; ++i)
	{
		temp_value = 0;
		switch (board[i])
		{
		case 'p':
			{
				temp_value = -100;
				// extract the row and column - I`m very proud of this ^_^ (DuMuT6p)
				int row = i;
				row &= 0xF0;
				row /= 16;
				int col = i;
				col &= 0x0F;
				if (player == 'w')
					temp_value -= PawnRow[row] + PawnCol[col] * (row/2);
				else
					temp_value -= PawnRow[7 - row] + PawnCol[7 - col] * ( (7 - row) / 2);
				// NOTE: casting between float and int may cause conflict, cosider this in testing phase
			}
			break;
		case 'r':
			{
				temp_value = -500;
				if (this->getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the rook
					for(int j = 0; j < 4; ++j)
					{
						temp_value -= 1.5f*countEmptyMoves(i, rook[j]);
					}
				}
			}
			break;
		case 'h':
			{
				temp_value = -300;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the knight
					// center - 0x33, 0x34, 0x43, 0x44
					temp_value -= 3.f*(4 - distanceToCenter(i));
				}
			}
			break;
		case 'b':
			{
				temp_value = -300;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the bishop
					for(int j = 0; j < 4; ++j)
					{
						temp_value -= 2.f*countEmptyMoves(i, bishop[j]);
					}
				}
			}
			break;
		case 'q':
			{
				temp_value = -900;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the queen
					for(int j = 0; j < 8; ++j)
					{
						temp_value -= countEmptyMoves(i, queen[j]);
					}
				}
			}
			break;
		case 'k':
			{
				temp_value = -10000;
				/*for(int j = 0; j < 4; ++j)
				{
				//if(board[i + king[j]] == 'e')

				}*/
			}
			break;
		case 'P':
			{
				temp_value = 100;
				// extract the row and column - I`m very proud of this ^_^ (DuMuT6p)
				int row = i;
				row &= 0xF0;
				row /= 16;
				int col = i;
				col &= 0x0F;
				if (player == 'b')
					temp_value += PawnRow[row] + PawnCol[col] * (row/2);
				else
					temp_value += PawnRow[7 - row] + PawnCol[7 - col] * ( (7 - row) / 2);
				// NOTE: casting between float and int may cause conflict, cosider this in testing phase
			}
			break;
		case 'R':
			{
				temp_value = 500;
				if (this->getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the rook
					for(int j = 0; j < 4; ++j)
					{
						temp_value += 1.5f*countEmptyMoves(i, rook[j]);
					}
				}
			}
			break;
		case 'H':
			{
				temp_value = 300;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the knight
					// center - 0x33, 0x34, 0x43, 0x44
					temp_value += 3.f*(4 - distanceToCenter(i));
				}
			}
			break;
		case 'B':
			{
				temp_value = 300;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the bishop
					for(int j = 0; j < 4; ++j)
					{
						temp_value += 2.f*countEmptyMoves(i, bishop[j]);
					}
				}
			}
			break;
		case 'Q':
			{
				temp_value = 900;
				if (getPhaseOfGame() != "mateGame") {
					// iterate over the possible moves of the queen
					for(int j = 0; j < 8; ++j)
					{
						temp_value += countEmptyMoves(i, queen[j]);
					}
				}
			}
			break;
		case 'K':
			{
				temp_value = 10000;
				/*for(int j = 0; j < 4; ++j)
				{
				//if(board[i + king[j]] == 'e')

				}*/
			}
			break;
		default:
			break;
		}
		value += temp_value;
	}

	return value;
}

int
	Board::			treeMin(int alpha, int beta, int depth)
{
	int i, res;

	if (depth == 0)
		return evaluate();

	std::vector<std::vector<MoveType *> *> *moves = new std::vector<std::vector<MoveType *> *>;


	for (i = 0; i < 120; ++i)
	{
		if (board[i] != 'e' && board[i] >= 'a')
			moves->push_back(generateLegalMovesForAPiece(i));
	}

	for (; !moves->empty() && alpha < beta;)
	{
		for (; !moves->back()->empty() && alpha < beta;)
		{
			doComputerMove(moves->back()->back());
			res = this->treeMax(alpha, beta, depth - 1);
			if (res < beta && checkCheck() != -1)
				beta = res;
			undoMove();
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		for (; !moves->back()->empty();)
		{
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		delete moves->back();
		moves->pop_back();
	}
	for (; !moves->empty();)
	{
		for (; !moves->back()->empty();)
		{
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		delete moves->back();
		moves->pop_back();
	}
	delete moves;
	return (beta);
}

int
	Board::			treeMax(int alpha, int beta, int depth)
{
	int i, res;


	if (depth == 0)
		return evaluate();


	std::vector<std::vector<MoveType *> *> *moves = new std::vector<std::vector<MoveType *> *>;


	for (i = 0; i < 120; ++i)
	{
		if (board[i] < 'a')
			moves->push_back(generateLegalMovesForAPiece(i));
	}

	for (; !moves->empty() && alpha < beta;)
	{
		for (; !moves->back()->empty() && alpha < beta;)
		{
			doComputerMove(moves->back()->back());
			res = this->treeMin(alpha, beta, depth - 1);
			if (res > alpha && checkCheck() != 1)
				alpha = res;
			undoMove();
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		for (; !moves->back()->empty();)
		{
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		delete moves->back();
		moves->pop_back();
	}
	for (; !moves->empty();)
	{
		for (; !moves->back()->empty();)
		{
			poolObject.releaseObject(moves->back()->back());
			moves->back()->pop_back();
		}
		delete moves->back();
		moves->pop_back();
	}

	delete moves;
	return alpha;
}

void
	Board::			playerTurn()
{
	while (42)
	{
		this->displayBoard();
		std::cout << "where do you want to play ? (example e2e4 is correct, not e2-e4)." << std::endl;
		getline(std::cin, buffer2);
		if (!buffer2.empty())
			if (doPlayerMove(buffer2))
				break;
		std::cout << "Error: invalid move !" << std::endl;
	}
}

void
	Board::			computerTurn(int depth)
{
	int	alpha = -2000000000;
	int beta = +2000000000;
	int res;
	unsigned int i = 0;

	if(phase == "startGame" && move_history.size() < 20)
	{
		/*
		static int nextMove = 0; // counting the moves
		//DEBUG: chosenOpening = 0;
		// TODO: randomize so only 80% of the time the computer answers with thiese moves
		if(player == 'w') // Computer answering moves
		{
		// DEBUG:
		//std::cout << "Computer answer move with chosenOpening = " << chosenOpening << std::endl;
		if(board[0x34] == 'p'){
		// Second reply
		// French defense
		if(board[0x33] == 'p' && board[0x54] == 'P'){
		// DEBUG:
		//std::cout << "Computer second reply with chosenOpening = " << chosenOpening << std::endl;
		savedMove = MoveType(0x43, 0x63, false, 'P', ' ');
		advancePhaseOfGame(); // go into midGame after the hardcoded replies end
		}
		else if(nextMove < 1){ // First reply
		if(chosenOpening == 0)
		// French defense
		savedMove = MoveType(0x54, 0x64, false, 'P', ' ');
		else if(chosenOpening == 1){
		// Sicilian defense
		savedMove = MoveType(0x42, 0x62, false, 'P', ' ');
		advancePhaseOfGame();
		}
		else{
		// Caro-Kann defense
		savedMove = MoveType(0x52, 0x62, false, 'P', ' ');
		advancePhaseOfGame();
		}
		++nextMove;
		}
		}
		else{
		// player didn`t do one of the hardcoded moves
		// DEBUG:
		//std::cout << "Played didn` do a expected move" << std::endl;
		savedMove = MoveType(0x42, 0x62, false, 'P', ' '); // do some move
		advancePhaseOfGame(); // and advance to mid game
		}
		}
		else // if(player == 'b') Computer starting moves
		{
		// DEBUG:
		// std::cout << "Computer starting move with chosenOpening = " << chosenOpening << std::endl;
		// TODO: randomize the starting moves - chooseOpening
		std::vector<MoveType > v = book.at(chosenOpening);
		savedMove = v.at(nextMove);
		++nextMove;
		if(nextMove == v.size()) // if the move is the last from chosenOpening series
		advancePhaseOfGame(); // go into midGame
		}

		*/  



		std::vector<MoveType*>::iterator	it = move_history.begin();
		std::vector<MoveType*>::iterator	end = move_history.end();
		std::string openingmoves;
		std::vector<std::string> movespossible;
		std::string	buf;

		++it;
		while (it != end)
		{
			int _oldmove = (*it)->getOldMove();
			int _newmove = (*it)->getNewMove();
			openingmoves += (char)((_oldmove & 0x0F) + 'a');
			openingmoves += (char)((_oldmove & 0xF0)/16 + '1'); 
			openingmoves += (char)((_newmove & 0x0F) + 'a'); 
			openingmoves += (char)((_newmove & 0xF0)/16 + '1');
			++it;
		}


		if (bookpos != 0)
			Bookopening.seekg(bookpos);
		while (getline(Bookopening, buf) && buf.compare(0, openingmoves.size(), openingmoves) != 0) ;
		bookpos = (int)Bookopening.tellg() - 82;
		if (buf.compare(0, openingmoves.size(), openingmoves) == 0)
			movespossible.push_back(buf.substr(openingmoves.size(), 4));
		while (getline(Bookopening, buf) && buf.compare(0, openingmoves.size(), openingmoves) == 0)
		{
			if (movespossible.empty() || movespossible.back().compare(0, 4, buf.substr(openingmoves.size(), 4)) != 0 )
				movespossible.push_back(buf.substr(openingmoves.size(), 4));
		}	
		if (movespossible.size() != 0)
		{
			int random = rand() % movespossible.size();
			int _old, _new;
			_old = (movespossible[random][0] - 'a') + (movespossible[random][1] - '1') * 16;
			_new = (movespossible[random][2] - 'a') + (movespossible[random][3] - '1') * 16;
			doComputerMove(poolObject.getObject(_new, _old, false, board[_old], board[_new]));
		} 
		else
			advancePhaseOfGame();
	}
	else if (phase == "startGame" && move_history.size() > 20)
		advancePhaseOfGame();


	if (phase == "midGame")
	{
		depth = 0;


		clock_t myclock = clock();
		while (((clock() - myclock) / CLOCKS_PER_SEC) * 70 < 15)
		{
			alpha = -2000000000;
			beta = +2000000000;
			i = 0;
			depth += 1;

			std::vector<std::vector<MoveType *> *> *moves = new std::vector<std::vector<MoveType *> *>;
			for (i = 0; i < 120; ++i)
			{
				if (board[i] < 'a')
					moves->push_back(generateLegalMovesForAPiece(i));
			}

			if (depth > 1)
			{
				doComputerMove(&savedMove);
				if ((res = checkCheck()) != 1 && res != 2)
				{
					res = this->treeMin(alpha, beta, depth - 1);
					if (res > alpha)
						alpha = res;
				}
				undoMove();
			}



			// Alpha-Beta algorithm
			for (; !moves->empty();)
			{
				for (;!moves->back()->empty();)
				{
					doComputerMove(moves->back()->back());
					if ((res = checkCheck()) != 1 && res != 2)
					{

						res = this->treeMin(alpha, beta, depth - 1);
						if (res > alpha)
						{
							alpha = res;
							savedMove = *moves->back()->back();
						}
					}
					undoMove();
					poolObject.releaseObject(moves->back()->back());
					moves->back()->pop_back();
				}
				delete moves->back();
				moves->pop_back();
			}
			delete moves;
		}
		if (alpha == -2000000000)
		{
			if (checkCheck() == 1)
				std::cout << "#checkmate" << std::endl;
			else
				std::cout << "#draw" << std::endl;
		}
		else
			doComputerMove(&savedMove);
		flog << "depth" << depth << std::endl;
	}
}

int
	Board::			InputWaiting() //for non-blocked input
{
#ifdef _WIN32
	DWORD cnt; // small problem with windows implementation it's you can't use it for the standard input if you don't use winboard or xboard cause of peeknamedpipe
	static HANDLE hInp = NULL;
	if(hInp == NULL) hInp = GetStdHandle(STD_INPUT_HANDLE);
	return !PeekNamedPipe(hInp, NULL, 0, NULL, &cnt, NULL) || cnt > 0;
#else
	static fd_set rset;
	static struct timeval timeout = {0, 0};
	FD_ZERO(&rset);
	FD_SET(0, &rset);
	if(select(1, &rset, NULL, NULL, &timeout) < 0) printf("error X\n");
	if (FD_ISSET(0, &rset))   return 1;
#endif
	return 0;
}


void
	Board::			run_winboard()
{
	int resign, contemptFactor, randomize = 0;
	int stm = 1;                                 // side to move
	int engineSide=4, playerSide=1;                     // side played by engine
	int timeLeft;                            // timeleft on engine's clock
	int mps, timeControl = 0, inc, timePerMove;  // time-control parameters, to be used by Search
	int maxDepth;                            // used by search
	MoveType move, ponderMove;
	//	int i, score;

	flog.open("flog.txt");
	Bookopening.open("bigbook.txt");
	randomize++;
	timeControl++;
	winboard = true;


	while(1)
	{ // infinite loop

		//std::cout << std::fflush;                 // make sure everything is printed before we do something that might take time
		fflush(stdout);
		if (stm == engineSide)
		{         // if it is the engine's turn to move, set it thinking, and let it move
			computerTurn(depthOption);
			std::cout << "move " << (char)((move_history.back()->getOldMove() & 0x0F) + 'a') << (char)((move_history.back()->getOldMove() & 0xF0)/16 + '1') << (char)((move_history.back()->getNewMove() & 0x0F) + 'a') << (char)((move_history.back()->getNewMove() & 0xF0)/16 + '1') << std::endl;
			flog << "#move " << (char)((move_history.back()->getOldMove() & 0x0F) + 'a') << (char)((move_history.back()->getOldMove() & 0xF0)/16 + '1') << (char)((move_history.back()->getNewMove() & 0x0F) + 'a') << (char)((move_history.back()->getNewMove() & 0xF0)/16 + '1') << std::endl;

			/*
			score = SearchBestMove(stm, timeLeft, mps, timeControl, inc, timePerMove, &move, &ponderMove);

			if(move == INVALID) {         // game apparently ended
			engineSide = NONE;          // so stop playing
			PrintResult(stm, score);
			} else {
			stm = MakeMove(stm, move);  // assumes MakeMove returns new side to move
			gameMove[moveNr++] = move;  // remember game
			printf("move %s\n", MoveToText(move));
			}
			*/
			stm = playerSide;
		}

		//std::cout << std::fflush; // make sure everything is printed before we do something that might take time

		// now it is not our turn (anymore)
		/*if(engineSide == ANALYZE)
		{       // in analysis, we always ponder the position
		PonderUntilInput(stm);
		}
		else
		if(engineSide != NONE && ponder == ON && moveNr != 0) { // ponder while waiting for input
		if(ponderMove == INVALID) {     // if we have no move to ponder on, ponder the position
		PonderUntilInput(stm);
		} else {
		int newStm = MakeMove(stm, ponderMove);
		PonderUntilInput(newStm);
		UnMake(ponderMove);
		}
		}
		*/
noPonder:

		buffer = "";

		if (InputWaiting())    //for non-blocked input
		{
			getline(std::cin, buffer);  // take one line of input

			std::cerr << buffer << std::endl;
			flog << buffer << std::endl;
		}

		command = buffer.substr(0, buffer.find_first_of(" \0")); // take the first word
		std::cerr << command << std::endl;
		// recognize the command,and execute it
		if(!command.compare("quit"))
			break;														 // breaks out of infinite loop
		if(!command.compare("force"))
		{
			engineSide = NONE;
			continue;
		}
		if(!command.compare("analyze"))
		{
			engineSide = ANALYZE;
			continue;
		}
		if(!command.compare("exit"))
		{
			engineSide = NONE;
			continue;
		}
		if(!command.compare("otim"))
		{
			goto noPonder;
		} // do not start pondering after receiving time commands, as move will follow immediately
		if(!command.compare("time"))
		{
			SSCANF(buffer.c_str(), "time %d", &timeLeft);
			goto noPonder;
		}
		if(!command.compare("level"))
		{
			int min, sec=0;
			SSCANF(buffer.c_str(), "level %d %d %d", &mps, &min, &inc) == 3 ||  // if this does not work, it must be min:sec format
				SSCANF(buffer.c_str(), "level %d %d:%d %d", &mps, &min, &sec, &inc);
			timeControl = 60*min + sec; timePerMove = -1;
			continue;
		}
		if(!command.compare("protover"))
		{
			printf("feature ping=0 setboard=1 colors=0 usermove=1 memory=0 debug=1 time=0");
			printf("feature option=\"Resign -check 0\"");           // example of an engine-defined option
			printf("feature option=\"Contempt -spin 0 -200 200\""); // and another one
			printf("feature done=1");
			continue;
		}
		if(!command.compare("option"))
		{ // setting of engine-define option; find out which
			if(SSCANF(buffer.c_str()+7, "Resign=%d",   &resign)         == 1)
				continue;
			if(SSCANF(buffer.c_str()+7, "Contempt=%d", &contemptFactor) == 1)
				continue;
			continue;
		}
		if(!command.compare("sd"))
		{
			SSCANF(buffer.c_str(), "sd %d", &maxDepth);
			continue;
		}
		if(!command.compare("st"))
		{
			SSCANF(buffer.c_str(), "st %d", &timePerMove);
			continue;
		}
		if(!command.compare("memory"))
		{
			//    SetMemorySize(atoi(buffer.c_str()+7));
			continue;
		}
		if(!command.compare("ping"))
		{
			printf("pong%s", buffer.c_str()+4);
			continue;
		}
		//  if(!command.compare(""))        { SSCANF(buffer.c_str(), " %d", &); continue; }
		if(!command.compare("new"))
		{
			engineSide = BLACK;
			//stm = Setup(DEFAULT_FEN);
			maxDepth = MAXPLY;
			randomize = OFF;
			continue;
		}
		if(!command.compare("setboard"))
		{
			engineSide = 4;
			//stm = Setup(buffer.c_str()+9);
			continue;
		}
		if(!command.compare("easy"))
		{
			//ponder = OFF;
			continue;
		}
		if(!command.compare("hard"))
		{
			//ponder = ON;
			continue;
		}
		if(!command.compare("undo"))
		{
			//stm = TakeBack(1);
			continue;
		}
		if(!command.compare("remove"))
		{
			undoMove();
			undoMove();
			continue;
		}
		if(!command.compare("go"))
		{
			player = 'b';
			init();
			stm = engineSide;
			continue;
		}
		if(!command.compare("post"))
		{
			//postThinking = ON;
			continue;
		}
		if(!command.compare("nopost"))
		{
			//postThinking = OFF;
			continue;
		}
		if(!command.compare("random"))
		{
			randomize = ON;
			continue;
		}
		if(!command.compare("hint"))
		{
			//	if(ponderMove != INVALID)
			//	printf("Hint: %s\n", MoveToText(ponderMove));
			continue;
		}
		if(!command.compare("book"))
			continue;
		// ignored commands:
		if(!command.compare("xboard"))
			continue;
		if(!command.compare("computer"))
			continue;
		if(!command.compare("name"))
			continue;
		if(!command.compare("ics"))
			continue;
		if(!command.compare("accepted"))
			continue;
		if(!command.compare("rejected"))
			continue;
		if(!command.compare("variant"))
			continue;
		if(!command.compare(""))
			continue;
		if(!command.compare("usermove"))
		{
			buffer2 = buffer.substr(buffer.find_first_of(" ") + 1, std::string::npos);
			this->doPlayerMove(buffer2);
			stm = engineSide;
			continue;
		}
		printf("Error: unknown command\n");
	}
}

void
	Board::     choosePromotion(int pos)
{
	// TODO: only choose from taken pieces
	std::cout << "Choose a piece for promotion: " << std::endl;

	std::string p = "NotAPiece";
	while(p == "NotAPiece"){
		std::cin >> p;
		// TODO: include option to undo the move here or if it is done somewhere else, delete this comment
		if( p == "queen" )
			board[pos] = 'q';
		else if( p == "bishop" )
			board[pos] = 'b';
		else if( p == "knight" )
			board[pos] = 'h';
		else if( p == "rook" )
			board[pos] = 'r';
		else
		{
			std::cout << "Not a piece, choose again!" << std::endl;
			p = "NotAPiece";
		}
	}
}

bool
	Board::		doPlayerMove(std::string strmove)
{
	int		pos1;
	int		pos2;
	MoveType	*moveT;

	pos1 = (strmove[0] - 'a') + (strmove[1] - '1') * 16;
	pos2 = (strmove[2] - 'a') + (strmove[3] - '1') * 16;
	if (board[pos1] == 'e' || (board[pos1] >= 'B' && board[pos1] <= 'R'))
		return (false);
	moveT = poolObject.getObject(pos2, pos1, false, board[pos1], board[pos2]);
	if (winboard == true || checkLegalMove(moveT))
	{
		if ((board[pos1] == 'p') && (((0xF0 & pos2) == 0x70) || ((0xF0 & pos2) == 0x00))) // pawn promotion
			choosePromotion(pos2);
		else if (moveT->getSpecial()) // en passant or castle
		{
			if (board[pos1] == 'p') // en passant
			{
				board[pos2] = board[pos1];
				if (player == 'w')
					board[pos2 - 0x10] = 'e';
				else
					board[pos2 + 0x10] = 'e';
			}
			else
			{
				if (player == 'w')
				{
					if (pos2 > pos1)
					{
						board[0x06] = 'k';
						board[0x05] = 'r';
						board[0x07] = 'e';
					}
					else
					{
						board[0x02] = 'k';
						board[0x03] = 'r';
						board[0x00] = 'e';
					}
				}
				else
				{
					if (pos2 > pos1)
					{
						board[0x76] = 'k';
						board[0x75] = 'r';
						board[0x77] = 'e';
					}
					else
					{
						board[0x72] = 'k';
						board[0x73] = 'r';
						board[0x70] = 'e';
					}
				}
			}
		}
		else
			board[pos2] = board[pos1];
		board[pos1] = 'e';
		move_history.push_back(moveT);
		if (pos1 == 0x00)
			rookLW = true;
		else if (pos1 == 0x07)
			rookRW = true;
		else if (pos1 == 0x70)
			rookLB = true;
		else if (pos1 == 0x77)
			rookRB = true;
		else if (pos1 == 0x04)
			kingW = true;
		else if (pos1 == 0x74)
			kingB = true;
		return (true);
	}
	return (false);
}

bool
	Board::		checkLegalMove(MoveType *move) const
{
	char		piece;
	int			_old;
	int			_new;
	int			i;
	int			tmpPosition;

	piece	= move->getMovePiece();
	_old = move->getOldMove();
	_new = move->getNewMove();
	switch (piece)
	{
	case 'p':
		for (i = 0; i < 4; ++i)
		{
			if (player == 'w')
			{
				if ((pawn[i] != NN || (pawn[i] == NN && ((0xF0 & _old) == 0x10) && board[_old + NORTH] == 'e'))
					&& ((_old + pawn[i]) == _new)
					&& isInsideBoard(_new))
				{
					if ((board[_new] < 'a' && (pawn[i] == NE || pawn[i] == NW))
						|| (board[_new] == 'e' && pawn[i] != NE && pawn[i] != NW))
						return (true);
					if (move_history.back()->getMovePiece() == 'P' // en passant
						&& ((move_history.back()->getNewMove() == (_old + 0x01))
						|| move_history.back()->getNewMove() == (_old - 0x01))
						&& (move_history.back()->getOldMove() & 0xF0) == 0x60)
					{
						move->setSpecial(true);
						return (true);
					}
				}
			}
			else
			{
				if ((pawnB[i] != SS || (pawnB[i] == SS && ((0xF0 & _old) == 0x60) && board[_old + SOUTH] == 'e'))
					&& ((_old + pawnB[i]) == _new)
					&& isInsideBoard(_new))
				{
					if ((board[_new] < 'a' && (pawnB[i] == SE || pawnB[i] == SW))
						|| (board[_new] == 'e' && pawnB[i] != SE && pawnB[i] != SW))
						return (true);
					if (move_history.back()->getMovePiece() == 'P' // en passant
						&& ((move_history.back()->getNewMove() == (_old + 0x01))
						|| move_history.back()->getNewMove() == (_old - 0x01))
						&& (move_history.back()->getOldMove() & 0xF0) == 0x10)
					{
						move->setSpecial(true);
						return (true);
					}
				}
			}
		}
		return (false);
	case 'h':
		for (i = 0; i < 8; ++i)
		{
			if ((_old + horse[i]) == _new
				&& (isInsideBoard(_new))
				&& (board[_new] < 'a' || board[_new] == 'e'))
				return (true);
		}
		return (false);
	case 'k':
		for (i = 0; i < 10; ++i)
		{
			if ((_old + king[i]) == _new
				&& isInsideBoard(_new))
			{
				if (king[i] == EE || king[i] == WW)
				{
					if (player == 'w')
					{
						if (castleKingSideWhite(i)
							|| castleQueenSideWhite(i))
						{
							move->setSpecial(true);
							return (true);
						}
					}
					else
					{
						if (castleKingSideBlack(i)
							|| castleQueenSideBlack(i))
						{
							move->setSpecial(true);
							return (true);
						}
					}
					return (false);
				}
				if (board[_new] < 'a'
					|| board[_new] == 'e')
					return (true);
				return (false);
			}
		}
		return (false);
	case 'r':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + rook[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] != board[_new] && board[tmpPosition] == 'e' )
				tmpPosition += rook[i];
			if (isInsideBoard(tmpPosition) && (board[tmpPosition] < 'a' || board[tmpPosition] == 'e') && board[tmpPosition] == board[_new])
				return (true);
		}
		return (false);
	case 'b':
		for (i = 0; i < 4; ++i)
		{
			tmpPosition = _old + bishop[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] != board[_new] && board[tmpPosition] == 'e' )
				tmpPosition += bishop[i];
			if (isInsideBoard(tmpPosition) && (board[tmpPosition] < 'a' || board[tmpPosition] == 'e') && board[tmpPosition] == board[_new])
				return (true);
		}
		return (false);
	case 'q':
		for (i = 0; i < 8; ++i)
		{
			tmpPosition = _old + queen[i];
			while (isInsideBoard(tmpPosition) && board[tmpPosition] != board[_new] && board[tmpPosition] == 'e' )
				tmpPosition += queen[i];
			if (isInsideBoard(tmpPosition) && (board[tmpPosition] < 'a' || board[tmpPosition] == 'e') && board[tmpPosition] == board[_new])
				return (true);
		}
		return (false);
	default:
		std::cout << "Error, not a piece" << std::endl;
		return (false);
	}
	return (true);
}

std::string
	Board::		getPhaseOfGame() const
{
	return (this->phase);
}

void
	Board::		setPhaseOfGame(std::string _phase)
{
	this->phase = _phase;
}

void
	Board::		advancePhaseOfGame()
{
	if(this->phase == "startGame")
		this->phase = "midGame";
	else if(this->phase == "midGame")
		this->phase = "endGame";
	else if(this->phase == "endGame")
		this->phase = "mateGame";
}

void
	Board::		restartGame()
{
	this->phase = "startGame";
}

// return 1 for computer was in check -1 for player and 0 if no check
int
	Board::checkCheck() const
{
	int	i;
	int y;
	int	j;

	//computer
	//pawn
	for (i = 0; board[i] != 'K' && i < 120; ++i) ;

	if (i > 120)
		return 2;

	if (player != 'w')
	{
		if ((!((i + NE) & 0x88) && board[i + NE] == 'p') || (!((i + NW) & 0x88) && board[i + NW] == 'p'))
			return 1;
	}
	else
	{
		if (( !((i + SE) & 0x88) && board[i + SE] == 'p' )||(!((i + SW) & 0x88) && board[i + SW] == 'p'))
			return 1;
	}
	//!pawn
	//knight
	for (y = 0; y < 8; ++y)
	{
		if ( !((i + horse[y]) & 0x88) && board[i + horse[y]] == 'h')
			return 1;
	}
	//!knight
	//bishop and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((i + j * bishop[y]) & 0x88))
				break;
			if (board[i + j * bishop[y]] == 'b' || board[i + j * bishop[y]] == 'q')
				return 1;
		}
	}
	//!bishop and queen
	//rook and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((i + j * rook[y]) & 0x88))
				break;
			if (board[i + j * rook[y]] == 'r' || board[i + j * rook[y]] == 'q')
				return 1;
		}
	}
	//!rook and queen
	//!computer

	//player
	for (i = 0; board[i] != 'k'&& i < 120; ++i) ;

	if (i > 120)
		return -2;

	//pawn
	if (player == 'w')
	{
		if ((!((i + NE) & 0x88) && board[i + NE] == 'P') || (!((i + NW) & 0x88) && board[i + NW] == 'P'))
			return -1;
	}
	else
	{
		if (( !((i + SE) & 0x88) && board[i + SE] == 'P' )||(!((i + SW) & 0x88) && board[i + SW] == 'P'))
			return -1;
	}
	//!pawn
	//knight
	for (y = 0; y < 8; ++y)
	{
		if ( !((i + horse[y]) & 0x88) && board[i + horse[y]] == 'H')
			return -1;
	}
	//!knight
	//bishop and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((i + j * bishop[y]) & 0x88))
				break;
			if (board[i + j * bishop[y]] == 'B' || board[i + j * bishop[y]] == 'Q')
				return -1;
		}
	}
	//!bishop and queen
	//rook and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((i + j * rook[y]) & 0x88))
				break;
			if (board[i + j * rook[y]] == 'R' || board[i + j * rook[y]] == 'Q')
				return -1;
		}
	}
	//!rook and queen
	//!player

	return 0;
}

void
	Board::		doComputerMove(MoveType *move)
{
	int		pos1;
	int		pos2;
	char	piece1;
	char	piece2;

	pos1 = move->getOldMove();
	pos2 = move->getNewMove();
	piece1 = move->getMovePiece();
	piece2	= move->getContent();
	board[pos2] = board[pos1];
	if ((piece1 == 'p') && (((0xF0 & pos2) == 0x70) || ((0xF0 & pos2) == 0x00))) // pawn promotion
		board[pos2] = 'q';
	else if ((piece1 == 'P') && (((0xF0 & pos2) == 0x70) || ((0xF0 & pos2) == 0x00))) // pawn promotion
		board[pos2] = 'Q';
	else if (move->getSpecial()) // en passant or castle
	{
		if (board[pos1] == 'p') // en passant
		{
			if (player == 'w')
				board[pos2 - 0x10] = 'e';
			else
				board[pos2 + 0x10] = 'e';
		}
		else if (board[pos1] == 'P')
		{
			if (player == 'w')
				board[pos2 + 0x10] = 'e';
			else
				board[pos2 - 0x10] = 'e';
		}
		else // castle
		{
			if (board[pos1] == 'k')
			{
				if (player == 'w')
				{
					if (pos2 > pos1)
					{
						board[0x05] = 'r';
						board[0x07] = 'e';
					}
					else
					{
						board[0x03] = 'r';
						board[0x00] = 'e';
					}
				}
				else
				{
					if (pos2 > pos1)
					{
						board[0x75] = 'r';
						board[0x77] = 'e';
					}
					else
					{
						board[0x73] = 'r';
						board[0x70] = 'e';
					}
				}
			}
			else
			{
				if (player == 'w')
				{
					if (pos2 > pos1)
					{
						board[0x75] = 'R';
						board[0x77] = 'e';
					}
					else
					{
						board[0x73] = 'R';
						board[0x70] = 'e';
					}
				}
				else
				{
					if (pos2 > pos1)
					{
						board[0x05] = 'R';
						board[0x07] = 'e';
					}
					else
					{
						board[0x03] = 'R';
						board[0x00] = 'e';
					}
				}
			}
		}
	}
	board[pos1] = 'e';
	move_history.push_back(move);
	if (pos1 == 0x00)
		rookLW = true;
	else if (pos1 == 0x07)
		rookRW = true;
	else if (pos1 == 0x70)
		rookLB = true;
	else if (pos1 == 0x77)
		rookRB = true;
	else if (pos1 == 0x04)
		kingW = true;
	else if (pos1 == 0x74)
		kingB = true;
}

void
	Board::		undoMove()
{
	MoveType *move = move_history.back();
	move_history.pop_back();

	int		_new = move->getNewMove();
	int		_old = move->getOldMove();
	char	movePiece = move->getMovePiece();

	board[_new] = move->getContent();
	board[_old] = movePiece;

	if ((player == 'w'
		&&	((movePiece == 'r' && (_old == 0x07 || _old == 0x00))
		|| (movePiece == 'R' && (_old == 0x70 || _old == 0x77))
		|| (movePiece == 'k' && _old == 0x04)
		|| (movePiece == 'K' && _old == 0x74)))
		|| ((movePiece == 'R' && (_old == 0x07 || _old == 0x00))
		|| (movePiece == 'r' && (_old == 0x70 || _old == 0x77))
		|| (movePiece == 'K' && _old == 0x04)
		|| (movePiece == 'k' && _old == 0x74)))
	{
		int flag = 0;

		for (int i = 0, size = move_history.size(); i < size; ++i)
		{
			if (move_history[i]->getMovePiece() == movePiece && move_history[i]->getOldMove() == _old)
				++flag;
		}
		if (flag == 0)
		{
			if (_old == 0x00)
				rookLW = false;
			else if (_old == 0x07)
				rookRW = false;
			else if (_old == 0x70)
				rookLB = false;
			else if (_old == 0x77)
				rookRB = false;
			else if (_old == 0x04)
				kingW = false;
			else if (_old == 0x74)
				kingB = false;
		}
	}


	if (move->getSpecial()) // en passant or castle
	{
		if (movePiece == 'p') // en passant
		{
			if (player == 'w')
				board[_new - 0x10] = 'P';
			else
				board[_new + 0x10] = 'P';
		}
		else if (movePiece == 'P') // en passant
		{
			if (player == 'w')
				board[_new + 0x10] = 'p';
			else
				board[_new - 0x10] = 'p';
		}
		else // castle
		{
			if (movePiece == 'k')
			{
				if (player == 'w')
				{
					if (_new == 0x06)
					{
						board[0x05] = 'e';
						board[0x07] = 'r';
					}
					else
					{
						board[0x03] = 'e';
						board[0x00] = 'r';
					}
				}
				else
				{
					if (_new == 0x76)
					{
						board[0x75] = 'e';
						board[0x77] = 'r';
					}
					else
					{
						board[0x73] = 'e';
						board[0x70] = 'r';
					}
				}
			}
			else
			{
				if (player == 'w')
				{
					if (0x76)
					{
						board[0x75] = 'e';
						board[0x77] = 'R';
					}
					else
					{
						board[0x73] = 'e';
						board[0x70] = 'R';
					}
				}
				else
				{
					if (0x06)
					{
						board[0x05] = 'e';
						board[0x07] = 'R';
					}
					else
					{
						board[0x03] = 'e';
						board[0x00] = 'R';
					}
				}
			}
		}
	}

}

bool
	Board::		castleKingSideWhite(int i) const
{
	if (kingW == false
		&& rookRW == false
		&& board[0x05] == 'e'
		&& board[0x06] == 'e'
		&& !checkCheck()
		&& !caseControlledByBlack(0x05)
		&& !caseControlledByBlack(0x06))
		return (true);
	return (false);
}

bool
	Board::		castleQueenSideWhite(int i) const
{
	if (kingW == false
		&& rookLW == false
		&& board[0x01] == 'e'
		&& board[0x02] == 'e'
		&& board[0x03] == 'e'
		&& !checkCheck()
		&& !caseControlledByBlack(0x01)
		&& !caseControlledByBlack(0x02)
		&& !caseControlledByBlack(0x03))
		return (true);
	return (false);
}

bool
	Board::		castleKingSideBlack(int i) const
{
	if (kingB == false
		&& rookRB == false
		&& board[0x75] == 'e'
		&& board[0x76] == 'e'
		&& !checkCheck()
		&& !caseControlledByWhite(0x75)
		&& !caseControlledByWhite(0x76))
		return (true);
	return (false);
}

bool
	Board::		castleQueenSideBlack(int i) const
{
	if (kingW == false
		&& rookLW == false
		&& board[0x71] == 'e'
		&& board[0x72] == 'e'
		&& board[0x73] == 'e'
		&& !checkCheck()
		&& !caseControlledByWhite(0x71)
		&& !caseControlledByWhite(0x72)
		&& !caseControlledByWhite(0x73))
		return (true);
	return (false);
}

bool
	Board::		caseControlledByWhite(int pos) const
{
	if (player == 'w')
		return caseControlledByPlayer(pos);
	return caseControlledByComputer(pos);
}

bool
	Board::		caseControlledByBlack(int pos) const
{
	if (player == 'w')
		return caseControlledByComputer(pos);
	return caseControlledByPlayer(pos);

}

bool
	Board::		caseControlledByPlayer(int pos) const
{
	int j;
	int y;

	//pawn
	if (player != 'w')
	{
		if ((!((pos + NE) & 0x88) && board[pos + NE] == 'p') || (!((pos + NW) & 0x88) && board[pos + NW] == 'p'))
			return true;
	}
	else
	{
		if (( !((pos + SE) & 0x88) && board[pos + SE] == 'p' )||(!((pos + SW) & 0x88) && board[pos + SW] == 'p'))
			return true;
	}
	//!pawn
	//knight
	for (y = 0; y < 8; ++y)
	{
		if ( !((pos + horse[y]) & 0x88) && board[pos + horse[y]] == 'h')
			return true;
	}
	//!knight
	//bishop and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((pos + j * bishop[y]) & 0x88))
				break;
			if (board[pos + j * bishop[y]] == 'b' || board[pos + j * bishop[y]] == 'q')
				return true;
		}
	}
	//!bishop
	//rook
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((pos + j * rook[y]) & 0x88))
				break;
			if (board[pos + j * rook[y]] == 'r' || board[pos + j * rook[y]] == 'q')
				return true;
		}
	}
	return (false);
}


bool
	Board::		caseControlledByComputer(int pos) const
{
	int j;
	int y;

	//pawn
	if (player == 'w')
	{
		if ((!((pos + NE) & 0x88) && board[pos + NE] == 'P') || (!((pos + NW) & 0x88) && board[pos + NW] == 'P'))
			return true;
	}
	else
	{
		if (( !((pos + SE) & 0x88) && board[pos + SE] == 'P' )||(!((pos + SW) & 0x88) && board[pos + SW] == 'P'))
			return true;
	}
	//!pawn
	//knight
	for (y = 0; y < 8; ++y)
	{
		if ( !((pos + horse[y]) & 0x88) && board[pos + horse[y]] == 'H')
			return true;
	}
	//!knight
	//bishop and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((pos + j * bishop[y]) & 0x88))
				break;
			if (board[pos + j * bishop[y]] == 'B' || board[pos + j * bishop[y]] == 'Q')
				return true;
		}
	}
	//!bishop and queen
	//rook and queen
	for (y = 0; y < 4; ++y)
	{
		for (j = 1; j < 8; ++j)
		{
			if (!((pos + j * rook[y]) & 0x88))
				break;
			if (board[pos + j * rook[y]] == 'R' || board[pos + j * rook[y]] == 'Q')
				return true;
		}
	}
	return (false);
}
