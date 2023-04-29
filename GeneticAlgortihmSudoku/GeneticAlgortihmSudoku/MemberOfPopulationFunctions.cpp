#include "MemberOfPopulation.h"
#include <iostream>
#include <random>
#include<algorithm>
using namespace std;
MemberOfPopulation::MemberOfPopulation() : board(ROWS, std::vector<int>(COLS)) { // Creating board and setting all fields to 0 (meaning empty field)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
    initialize_board_values();
    find_empty_fields();
    generate_solution();
    calculate_rank();
}
MemberOfPopulation :: MemberOfPopulation(MemberOfPopulation& parent_1, MemberOfPopulation& parent_2) : board(ROWS, std::vector<int>(COLS)) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
    initialize_board_values();
    find_empty_fields();
    crossover(parent_1, parent_2);
    calculate_rank();
}

MemberOfPopulation& MemberOfPopulation :: operator=(const MemberOfPopulation& other) {
    ROWS = other.ROWS;
    COLS = other.COLS;
    empty_fields = other.empty_fields;
    board = other.board;
    no_more_moves = other.no_more_moves;
    rank = other.rank;
    return *this;
}

void MemberOfPopulation::initialize_board_values() { // Do poprawy - teraz na czas testowania samego algorytmu na sztywno wpisane wartosci
    board[0][0] = 7;
    board[0][2] = 3;
    board[0][4] = 8;
    board[0][7] = 5;
    board[1][6] = 2;
    board[2][4] = 9;
    board[2][7] = 1;
    board[2][8] = 6;
    board[3][1] = 9;
    board[3][3] = 5;
    board[4][0] = 1;
    board[4][4] = 4;
    board[4][5] = 7;
    board[6][0] = 5;
    board[6][1] = 7;
    board[6][5] = 1;
    board[6][7] = 2;
    board[7][0] = 6;
    board[7][2] = 2;
    board[7][6] = 9;
    board[7][8] = 1;
    board[8][2] = 9;
    board[8][4] = 7;
    board[8][5] = 4;
}
void MemberOfPopulation::find_empty_fields() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                int field_number = 9 * i + j + 1;
                empty_fields.push_back(field_number);
            }
        }
    }
}
int MemberOfPopulation::find_random_field() {
    random_device device;
    uniform_int_distribution<int> rand_field(0, empty_fields.size() - 1);
    int random_field = empty_fields[rand_field(device)];
    return random_field;
}
void MemberOfPopulation::find_possible_moves_and_chose_one_randomly(int field) {
    vector<int> possible_moves = { 1,2,3,4,5,6,7,8,9 };
    int row = (field - 1) / 9;
    int col = (field - 1) % 9;
    for (int i = 0; i < COLS; i++) { // Search row
        if (board[row][i] != 0) {
            if (find(possible_moves.begin(), possible_moves.end(), board[row][i]) != possible_moves.end()) {
                possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[row][i]), possible_moves.end());
            }
        }
    }
    for (int i = 0; i < ROWS; i++) { // Search column
        if (board[i][col] != 0) {
            if (find(possible_moves.begin(), possible_moves.end(), board[i][col]) != possible_moves.end()) {
                possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][col]), possible_moves.end());
            }
        }
    }
    // Search square
    if (row >= 0 and row <= 2) {
        if (col >= 0 and col <= 2) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
    }
    else if (row >= 3 and row <= 5) {
        if (col >= 0 and col <= 2) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
    }
    else {
        if (col >= 0 and col <= 2) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] != 0) {
                        if (find(possible_moves.begin(), possible_moves.end(), board[i][j]) != possible_moves.end()) {
                            possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), board[i][j]), possible_moves.end());
                        }
                    }
                }
            }
        }
    }
    if (possible_moves.size() == 0) { // No more moves for this field 
        no_more_moves.emplace_back(field);
        empty_fields.erase(std::remove(empty_fields.begin(), empty_fields.end(), field), empty_fields.end());
    }
    else { // Make random move from possible movess
        empty_fields.erase(std::remove(empty_fields.begin(), empty_fields.end(), field), empty_fields.end());
        random_device device;
        uniform_int_distribution<int> rand_val(0, possible_moves.size() - 1);
        board[row][col] = possible_moves[rand_val(device)];
    }


}
void MemberOfPopulation::generate_solution() { // Try to complete board until there is no possible move left
    while (empty_fields.size() != 0) {
        int field = find_random_field();
        find_possible_moves_and_chose_one_randomly(field);
    }
}
void MemberOfPopulation::calculate_rank() { // If board is completed rank 100 if there are missing fields rank is equal to 100 - number of missing pieaces
    rank = (no_more_moves.size() == 0) ? 100 : 100 - no_more_moves.size();
}
bool MemberOfPopulation::check_if_value_possible(int field, int val) {
    int row = (field - 1) / 9;
    int col = (field - 1) % 9;
    for (int i = 0; i < COLS; i++) { // Search row
        if (board[row][i] == val) {
            return false;
        }
    }
    for (int i = 0; i < ROWS; i++) { // Search column
        if (board[i][col] == val) {
            return false;
        }
    }
    // Search square
    if (row >= 0 and row <= 2) {
        if (col >= 0 and col <= 2) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
    }
    else if (row >= 3 and row <= 5) {
        if (col >= 0 and col <= 2) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 3; i <= 5; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
    }
    else {
        if (col >= 0 and col <= 2) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 3 and col <= 5) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 3; j <= 5; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
        if (col >= 6 and col <= 8) {
            for (int i = 6; i <= 8; i++) {
                for (int j = 6; j <= 8; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
int MemberOfPopulation :: read_field_value(int field) {
    int row = (field - 1) / 9;
    int col = (field - 1) % 9;
    return board[row][col];
}
bool MemberOfPopulation::complete_solution_found(MemberOfPopulation& member) {
    if (member.no_more_moves.size() == 0) {
        return true;
    }
    return false;
}
void MemberOfPopulation::show_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j] << " ";
            if (j == 2 or j == 5) {
                cout << "|";
            }
            if (j == 8) {
                cout << endl;
            }
        }
        if (i == 2 or i == 5) {
            for (int x = 0; x < COLS * 2; x++) {
                cout << "-";
            }
            cout << endl;
        }
    }
}
void MemberOfPopulation::show_rank() {
    cout << rank;
}