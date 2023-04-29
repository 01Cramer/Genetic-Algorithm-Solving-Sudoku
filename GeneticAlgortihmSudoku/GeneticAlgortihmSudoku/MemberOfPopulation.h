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

    MemberOfPopulation(); // Create member of first population (no crossovers and mutations)
    MemberOfPopulation(MemberOfPopulation& parent_1, MemberOfPopulation& parent_2); // Create member of population made from reproduction
    MemberOfPopulation& operator=(const MemberOfPopulation& other);
    /////////////////
    void initialize_board_values(); // Makes input board  
    void find_empty_fields(); // Look for empty fields and save them from 1 - first field to 81 - last field
    int read_field_value(int field);
    void crossover(MemberOfPopulation& parent_1, MemberOfPopulation& parent_2);
    bool check_if_value_possible(int field, int val);
    void mutation(int field);
    int find_random_field(); // Select random empty field
    void find_possible_moves_and_chose_one_randomly(int field); // Select random possible number available for selected field
    void generate_solution();
    void calculate_rank();
    bool complete_solution_found(MemberOfPopulation& member);
    //////////////////
    void show_board(); // Test_function
    void show_rank(); // Test_function
};

#endif
