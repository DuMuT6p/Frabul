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

#ifndef	POOLOBJECT_H
#define POOLOBJECT_H

#define NBSTARTOBJECT

#include <list>
#include "MoveType.h"

class PoolObject
{
public:
private:
  PoolObject();
  ~PoolObject();
  
  std::list<MoveType *> moveTypeList;
public:  
  static PoolObject& getInstance();
  MoveType *getObject();
  MoveType *getObject(const int &_newMove, const int &_oldMove, const bool &_special, const char &_movePiece, const char &_content);
  void releaseObject(MoveType* rendObject);
  const unsigned int getnumber();
};

#endif //!POOLOBJECT_H