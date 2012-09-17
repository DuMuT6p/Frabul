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

#include <iostream>
#include "PoolObject.h"

PoolObject::PoolObject()
	:moveTypeList(NBSTARTOBJECT)
{
	std::list<MoveType *>::iterator it = moveTypeList.begin();
	std::list<MoveType *>::iterator end = moveTypeList.end();

	for(;it != end; ++it)
	{
		(*it) = new MoveType;
	}
}

PoolObject::~PoolObject()
{
	while (!moveTypeList.empty())
	{
		delete moveTypeList.front();
		moveTypeList.pop_front();
	}
}

PoolObject& PoolObject::getInstance()
{
	static PoolObject instance;
	return instance;
}

MoveType *PoolObject::getObject()
{
	if(moveTypeList.empty())
	{
		return (new MoveType);
	}
	MoveType *front = moveTypeList.front();
	moveTypeList.pop_front();
	return front;
}

MoveType *PoolObject::getObject(const int &_newMove, const int &_oldMove, const bool &_special,
	const char &_movePiece, const char &_content)
{
	if(moveTypeList.empty())
	{
		return (new MoveType(_newMove, _oldMove, _special, _movePiece, _content));
	}
	MoveType *front = moveTypeList.front();
	front->resetAllAttributes(_newMove, _oldMove, _special, _movePiece, _content);
	moveTypeList.pop_front();
	return front;

}

void PoolObject::releaseObject(MoveType* rendObject)
{
	moveTypeList.push_back(rendObject);
}

const unsigned int PoolObject::getnumber()
{
	return (moveTypeList.size());
}