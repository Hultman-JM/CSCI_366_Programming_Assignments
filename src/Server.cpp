//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
	&file.seekg(0, std::ios::end);
	int fileSize = &file.tellg();
	return fileSize;
}


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){
	

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
	if (x < BOARD_SIZE && y < BOARD_SIZE) {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (ijt j = 0; j < BOARD_SIZE; j++)
			{
				if ()//enters if a hit
				{
					return HIT;
				}
				else// enters if a miss
				{
					return MISS;
				}
			}
		}
	}
	else {
		return OUT_OF_BOUNDS;
		//std::cout << "shot was out of bounds" << std::endl;
	}
}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}
