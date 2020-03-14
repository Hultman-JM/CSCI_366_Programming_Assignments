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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    Client::player = player;
    Client::board_size = board_size;
    if (player == 1)
    {
        Client::board_name = "player_1.action_board.json";
        vector<vector<int>> player1ActionBoard( board_size , vector<int> (board_size));
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                player1ActionBoard[i][j] = 0;
            }
        }
        ofstream player_1_action_board("player_1.action_board.json");
        cereal::JSONOutputArchive write_archive(player_1_action_board);
        write_archive(cereal::make_nvp("board", player1ActionBoard));
        player_1_action_board << "\n}";
        player_1_action_board.close();

        initialized = true;
    }
    else if (player == 2)
    {
        Client::board_name = "player_2.action_board.json";
        vector<vector<int>> player2ActionBoard( board_size , vector<int> (board_size));
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                player2ActionBoard[i][j] = 0;
            }
        }
        ofstream player_2_action_board("player_2.action_board.json");
        cereal::JSONOutputArchive write_archive(player_2_action_board);
        write_archive(cereal::make_nvp("board", player2ActionBoard));
        player_2_action_board << "\n}";
        player_2_action_board.close();
        initialized = true;
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    if (player == 1)
    {
        ofstream shot_file("player_1.shot.json");
        cereal::JSONOutputArchive write_archive(shot_file);
        write_archive(cereal::make_nvp("x", x));
        write_archive(cereal::make_nvp("y", y));
        shot_file << "\n}";
        shot_file.close();
    }
    else if (player == 2)
    {
        ofstream shot_file("player_2.shot.json");
        cereal::JSONOutputArchive write_archive(shot_file);
        write_archive(cereal::make_nvp("x", x));
        write_archive(cereal::make_nvp("y", y));
        shot_file << "\n}";
        shot_file.close();
    }

}


bool Client::result_available() {
    ifstream p1_result_file("player_1.result.json");
    ifstream p2_result_file("player_2.result.json");
    if (p1_result_file || p2_result_file)
    {
        return true;
    }
    else{
        return false;
    }
}


int Client::get_result() {
    int result;
    if (player == 1)
    {
        ifstream result_file("player_1.result.json");
        cereal::JSONInputArchive read_archive(result_file);
        read_archive(cereal::make_nvp("result", result));
        result_file.close();
        remove("player_1.result.json");
    }
    else if (player == 2) {
        ifstream result_file("player_2.result.json");
        cereal::JSONInputArchive read_archive(result_file);
        read_archive(cereal::make_nvp("result", result));
        result_file.close();
        remove("player_2.result.json");
    }
    if (result == HIT)
    {
        return HIT;
    }
    else if (result == MISS)
    {
        return MISS;
    }
    else if (result == OUT_OF_BOUNDS)
    {
        return OUT_OF_BOUNDS;
    }
    else
    {
        throw "bad result";
    }
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {//edit write from std files to .json
    vector<vector<int>> action_board( board_size , vector<int> (board_size));
    string data;
    if (player == 1)
    {
        ifstream in_action_board("player_1.action_board.json");
        cereal::JSONInputArchive read_archive(in_action_board);
        read_archive(action_board);
        in_action_board.close();
        remove("player_1.action_board.json");

        action_board[x][y] = result;

        ofstream player_1_action_board("player_1.action_board.json");
        cereal::JSONOutputArchive write_archive(player_1_action_board);
        write_archive(cereal::make_nvp("board", action_board));
        player_1_action_board << "\n}";
        player_1_action_board.close();
    }
    else if (player == 2)
    {
        ifstream in_action_board("player_2.action_board.json");
        cereal::JSONInputArchive read_archive(in_action_board);
        read_archive(action_board);
        in_action_board.close();
        remove("player_2.action_board.json");

        action_board[x][y] = result;

        ofstream player_2_action_board("player_2.action_board.json");
        cereal::JSONOutputArchive write_archive(player_2_action_board);
        write_archive(cereal::make_nvp("board", action_board));
        player_2_action_board << "\n}";
        player_2_action_board.close();
    }
}


string Client::render_action_board(){
    string action_board;

    if (player == 1)
    {
        ofstream player_1_action_board("player_1.action_board.json");
        cereal::JSONOutputArchive write_archive(player_1_action_board);
        write_archive(cereal::make_nvp("board", action_board));
        player_1_action_board.close();
    }
    else if (player == 2)
    {
        ofstream player_2_action_board("player_2.action_board.json");
        cereal::JSONOutputArchive write_archive(player_2_action_board);
        write_archive(cereal::make_nvp("board", action_board));
        player_2_action_board.close();
    }
    //cout << action_board << std::endl;
    return action_board;
}
