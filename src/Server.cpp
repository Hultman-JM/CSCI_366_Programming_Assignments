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


#include <string>
#include <cmath>
#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
	int count = 0;
	char character;
	while (*file >> character)
    {
	    ++count;
    }
	count = sqrt(count);
	return count;
}


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){
    Server::board_size = board_size;
    Server::p1_setup_board.open(p1_setup_board);
    Server::p2_setup_board.open(p2_setup_board);
    //cout << "board size: " << board_size << std::endl;
    int p1_file_length;
    int p2_file_length;
    //open p1_setup_board.txt and find the board size with get_file_length
    if (p1_setup_board == "player_1.setup_board.txt") {
        ifstream p1_board;
        ifstream *p1;
        p1_board.open(p1_setup_board);
        p1 = &p1_board;
        p1_file_length = get_file_length(p1);// store the size of the file's board
        //cout << "file length:  " << p1_file_length << std::endl;
    }
    //open p2_setup_board.txt and find the board size with get_file_length
    if (p2_setup_board == "player_2.setup_board.txt") {
        ifstream p2_board;
        ifstream *p2;
        p2_board.open(p2_setup_board);
        p2 = &p2_board;
        p2_file_length = get_file_length(p2);// store the size of the file's board
        //cout << "file length: " << p1_file_length << std::endl;
    }
    if (p1_setup_board != "player_1.setup_board.txt" || p2_setup_board != "player_2.setup_board.txt") {
        throw "One or both of the file names do not match what was expected.";
    }
    if (p1_file_length != board_size) {
        throw "p1 board does not match input board size.";
    }
    if (p2_file_length != board_size) {
        throw "p2 board does not match input board size.";
    }
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    string line;
    //cout << "board size: " << board_size << std::endl;
	if (x < board_size && y < board_size)
	{
		for (int i = 0; i < board_size; i++)
		{
            if (player == 1)
            {
                getline(p1_setup_board, line);
            }
            else if (player == 2)
            {
                getline(p2_setup_board, line);
            }
            else
            {
                if (player > 2)
                {
                    throw "player number is too large";
                }
                else if (player < 1)
                {
                    throw "player number is too small";
                }
            }
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (player == 1)
                {
                    if (j == x && i == y)//enters to check coords
                    {
                        //        if = C        or        if = B       or       if = R       or        if = S        or        if = D
                        if (line[j] == SHIPS[0] || line[j] == SHIPS[1] || line[j] == SHIPS[2] || line[j] == SHIPS[3] || line[j] == SHIPS[4])
                        {
                            return HIT;
                        }
                        else // enters if a miss
                        {
                            return MISS;
                        }
                    }
                }
                else if (player == 2)
                {
                    if (j == x && i == y)//enters if a hit
                    {
                        //        if = C        or        if = B       or       if = R       or        if = S        or        if = D
                        if (line[j] == SHIPS[0] || line[j] == SHIPS[1] || line[j] == SHIPS[2] || line[j] == SHIPS[3] || line[j] == SHIPS[4])
                        {
                            return HIT;
                        }
                        else // enters if a miss
                        {
                            return MISS;
                        }
                    }
                }
            }
        }
	}
	else {
		return OUT_OF_BOUNDS;
		cout << "shot was out of bounds" << std::endl;
	}
}


int Server::process_shot(unsigned int player) {
    int x, y, result;
    if (player == 1)
    {
        ifstream p1_shot_file("player_1.shot.json");
        if (!p1_shot_file)
        {
            return NO_SHOT_FILE;
        }
        else
        {
            cereal::JSONInputArchive read_archive(p1_shot_file);
            read_archive(cereal::make_nvp("x", x));
            read_archive(cereal::make_nvp("y", y));
            p1_shot_file.close();
        }
        result = evaluate_shot(player, x, y);
        ofstream  p1_result_file("player_1.result.json");
        cereal::JSONOutputArchive write_archive(p1_result_file);
        write_archive(cereal::make_nvp("result", result));
        p1_result_file << "\n}";
        p1_result_file.close();
        remove("player_1.shot.json");
        return SHOT_FILE_PROCESSED;
    }
    else if (player == 2)
    {
        ifstream p2_shot_file("player_2.shot.json");
        if (!p2_shot_file)
        {
            return NO_SHOT_FILE;
        }
        else
        {
            cereal::JSONInputArchive read_archive(p2_shot_file);
            read_archive(cereal::make_nvp("x", x));
            read_archive(cereal::make_nvp("y", y));
            p2_shot_file.close();
        }
        result = evaluate_shot(player, x, y);
        ofstream  p2_result_file("player_2.result.json");
        cereal::JSONOutputArchive write_archive(p2_result_file);
        write_archive(cereal::make_nvp("result", (int)result));
        p2_result_file << "\n}";
        p2_result_file.close();
        remove("player_2.shot.json");
        return SHOT_FILE_PROCESSED;
    }
    else // if player number is bad
    {
        if (player > 2)
        {
            throw "player number is too large";
        }
        else if (player < 1)
        {
            throw "player number is too small";
        }

    }
}
