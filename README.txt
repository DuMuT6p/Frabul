--------Frabul--------------
Frabul is a cross-platform chess engine, developed for an Artificial Intelligence course at Roskilde University, Denmark.

--------------THIS PROJECT IS NO LONGER DEVELOPED-----------
It is left in hope that it may be usefull for someone.

-------Information---------
The engine uses:
- the MinMAx with Alpha-Beta pruning algorithm
- iterative deepening technique
- evaluation methods inspired by Kaare Danielsen
- a Pool object for better memory management
- a book of opening moves

The maximum depth within reasonable time is 7 plys.

Frabul is tested and runs on Linux and Windows 7 machines.
The engine can use either Xboard(https://www.gnu.org/software/xboard/) or be played in a console. Just change the main() function.

To install xboard on UBUNTU

- sudo apt-get isntall xboard
- sudo apt-get install xfonts-100dpi
- sudo xset fp+ /usr/share/fonts/X11/100dpi

Then you can run it by typing xboard on a terminal.
Use man xboard for more information

Frabul Programmers:
DuMuT6p
Nicolas Rochelle (aerhos@gmail.com)
Pascal Vergnes (vergnes.pascal@gmail.com)

Copyright (C) 2012 Frabul programmers

This file is part of Frabul.

Frabul is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Frabul is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Frabul.  If not, see <http://www.gnu.org/licenses/>.
