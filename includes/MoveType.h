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

#ifndef		__MOVETYPE_H__
# define	__MOVETYPE_H__

/*
** Movements possible
** All moves are defined clockwise starting from top / twelve o`clock
*/

// king, queen, rook, bishop and pawn
#define	NORTH	0x10
#define	NE		0x11
#define	EAST	0x01
#define	SE		-0x0F
#define	SOUTH	-0x10
#define	SW		-0x11
#define	WEST	-0x01
#define	NW		0x0F
#define	NN		0x20 // possible first move - special
#define	SS		-0x20 // possible first move - special
#define	EE		0x02	// castle king side - special
#define	WW		-0x02	// castle queen side - special

// knight
#define NEF	0x21 // F standig for "far"
#define NEN	0x12 // N standing for "near"
#define SEN	-0xE
#define SEF	-0x1F
#define SWF	-0x21
#define SWN	-0x12
#define NWN	0xE
#define NWF	0x1F

const int	king[10] = {NORTH, NE, EAST, EE, SE, SOUTH, SW, WEST, WW, NW};
const int	queen[8] = {NORTH, NE, EAST, SE, SOUTH, SW, EAST, NW};
const int	bishop[4] = {NE, SE, SW, NW};
const int	rook[4] = {NORTH, EAST, SOUTH, WEST};
const int	horse[8] = {NEF, NEN, SEN, SEF, SWF, SWN, NWN, NWF};
const int	pawn[4] = {NN, NORTH, NE, NW};
const int	pawnB[4] = {SE, SOUTH, SS, SW};

// For evaluation function (I didn`t know where else to put them ;])
const int	PawnRow[8] = {0, 0, -1, 0, 2, 14, 30, 0};
const int	PawnCol[8] = {-2, 0, 3, 4, 5, 1, -2, -2};

class		MoveType
{
  int		newMove;
  int		oldMove;
  bool		special;
  char		movePiece;
  char		content;

 public:
  MoveType();
  MoveType(const int &_newMove, const int &_oldMove, const bool &_special, const char &_movePiece, const char &_content);
  ~MoveType();

  int		getNewMove() const;
  int		getOldMove() const;
  bool		getSpecial() const;
  char		getMovePiece() const;
  char		getContent() const;

  void		setNewMove(int);
  void		setOldMove(int);
  void		setSpecial(bool);
  void		setMovePiece(char);
  void		setContent(char);
  void		resetAllAttributes(const int &_newMove, const int &_oldMove, const bool &_special, const char &_movePiece, const char &_content);
};

#endif		// __MOVETYPE_H__
