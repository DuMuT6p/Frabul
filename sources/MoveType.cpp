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

#include	"MoveType.h"

MoveType::	MoveType()
  : newMove(0x00), oldMove(0x00), special(false),
    movePiece(' ') ,content(' ')
{
}

MoveType::	MoveType(const int &_newMove, const int &_oldMove, const bool &_special,
	const char &_movePiece, const char &_content)
  : newMove(_newMove), oldMove(_oldMove), special(_special),
    movePiece(_movePiece), content(_content)
{
}

MoveType::	~MoveType()
{
}

int
MoveType::	getNewMove() const
{
  return (newMove);
}

int
MoveType::	getOldMove() const
{
  return (oldMove);
}

bool
MoveType::	getSpecial() const
{
  return (special);
}

char
MoveType::	getMovePiece() const
{
  return (movePiece);
}

char		
MoveType::	getContent() const
{
  return (content);
}

void
MoveType::resetAllAttributes(const int &_newMove, const int &_oldMove, const bool &_special, const char &_movePiece, const char &_content)
{
	newMove = _newMove;
	oldMove = _oldMove;
	special	= _special;
	movePiece = _movePiece;
	content = _content;
}

void
MoveType::	setNewMove(int _newMove)
{
  newMove = _newMove;
}

void
MoveType::	setOldMove(int _oldMove)
{
  oldMove = _oldMove;
}

void	
MoveType::	setSpecial(bool _special)
{
  special = _special;
}

void	
MoveType::	setMovePiece(char _movePiece)
{
  movePiece = _movePiece;
}

void	
MoveType::	setContent(char _content)
{
  content = _content;
}
