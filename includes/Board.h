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

#ifndef				__BOARD_H__
# define			__BOARD_H__

// four different constants, with values for WHITE and BLACK that suit your engine
#define WHITE		1
#define BLACK		2
#define NONE		0
#define ANALYZE		3

// some value that cannot occur as a valid move
#define INVALID		666

// some parameter of your engine
#define MAXMOVES	500  /* maximum game length  */
#define MAXPLY		60   /* maximum search depth */

#define OFF			0
#define ON			1

#define DEFAULT_FEN	"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#ifdef WIN32
# define SSCANF		sscanf_s
#endif


// include windows
#ifdef			_WIN32

# include		<Windows.h>
# include		<WinBase.h>

#ifndef SSCANF
# define SSCANF	sscanf
#endif

#else		// include linux

# include		<sys/select.h>
# define SSCANF	sscanf

#endif

#include		<iostream>
#include		<sstream>
#include		<fstream>
#include		<string>
#include		<vector>
#include		<list>
#include        <time.h>

//  For the Chebyshev distance function, may also get hardcoded
//#include        <stdlib.h>
#include        <algorithm>

#include		"MoveType.h"
#include		"PoolObject.h"

class			Board
{
    const int   depthOption;
  char			player;
  char			board[120];
  char			distancetocenter[120];
  bool			rookLW;
  bool			rookRW;
  bool			rookLB;
  bool			rookRB;
  bool			kingW;
  bool			kingB;
  PoolObject&	poolObject;

  std::string	phase; // SUGGESTION: make this a enumerate? It can be only startGame, midGame, endGame or mateGame

    int chosenOpening;
  std::vector< std::vector< MoveType > > book; // Book of opening moves

  std::string		buffer;
  std::string		buffer2;
  std::string		command;
  std::vector<MoveType*>	move_history;
  MoveType			savedMove;
  std::ofstream		flog; // fichier de log
  std::ifstream		Bookopening;
  int				bookpos;
  bool				winboard;

  void			init();
  void			playerTurn();
  int			InputWaiting(); //for non-blocked input
  void			computerTurn(int);
  int			treeMin(int, int, int);
  int			treeMax(int, int, int);
  bool			doPlayerMove(std::string);
  void			doComputerMove(MoveType *);
  void			undoMove();
  void          choosePromotion(int);
  std::string	getPhaseOfGame() const;
  void			setPhaseOfGame(std::string);
  void			advancePhaseOfGame();
  void			restartGame();
  float			evaluate() const;

  void			displayBoard() const;
  void          displayPastMoves() const;
  bool			isInsideBoard(int) const;
  int           getDistanceToOtherKing() const;
  int			distanceToCenter(int) const;
  int			countEmptyMoves(int, int) const;
  bool			checkLegalMove(MoveType*) const;
  std::vector<MoveType*>
    *generateLegalMovesForAPiece(int) const;
  int			checkCheck() const; // return 1 for computer was in check -1 for player and 0 if no check
  bool			castleKingSideWhite(int) const;
  bool			castleQueenSideWhite(int) const;
  bool			castleKingSideBlack(int) const;
  bool			castleQueenSideBlack(int) const;
  bool			caseControlledByWhite(int) const;
  bool			caseControlledByBlack(int) const;
  bool			caseControlledByPlayer(int) const;
  bool			caseControlledByComputer(int) const;

 public:
  Board();
  ~Board();

  void			run();

  //for x-Board / winboard
  void			run_winboard();

};

#endif		// __BOARD_H__
