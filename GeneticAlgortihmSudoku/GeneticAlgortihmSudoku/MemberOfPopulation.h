#ifndef MEMBER_OF_POPULATION_H
#define MEMBER_OF_POPULATION_H

#include <vector>

struct MemberOfPopulation {
    int ROWS = 9; // Board size 
    int COLS = 9;
    std::vector<std::vector<int>> board;
    std::vector<int> empty_fields; // Vector containing fields that need to be completed
    std::vector<int> no_more_moves;

    int rank;

    MemberOfPopulation();
    MemberOfPopulation& operator=(const MemberOfPopulation& other);
    void initialize_board_values(); // Makes input board  
    void find_empty_fields(); // Look for empty fields and save them from 1 - first field to 81 - last field
    int find_random_field();
    void find_possible_moves_and_chose_one_randomly(int field);
    void generate_solution();
    void calculate_rank();
    void show_board(); // Test_function
    void show_rank(); // Test_function
};

#endif
