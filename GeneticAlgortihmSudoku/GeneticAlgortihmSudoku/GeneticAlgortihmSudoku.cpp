#include <iostream>
#include "MemberOfPopulation.h"
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int main()
{
	// Generate first population
	vector<MemberOfPopulation> population;
	const int POPULATION_SIZE = 300;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		MemberOfPopulation MemberOfPopulation;
		population.push_back(MemberOfPopulation);
	}

	// Select best from first population. Method : Rank Selection
	vector<MemberOfPopulation> best_out_of_population;
	const int BEST_FROM_POPULATION_SIZE = 30;
	int i = 0;
	do{
		best_out_of_population.clear();
		std::sort(population.begin(), population.end(), [](const MemberOfPopulation& lhs, const MemberOfPopulation& rhs) {return lhs.rank > rhs.rank; });
		for (int i = 0; i < BEST_FROM_POPULATION_SIZE; i++) {
			best_out_of_population.push_back(population[i]);
		}
		population.clear();

		for (int i = 0; i < POPULATION_SIZE; i++) { // Reproduction
			random_device device;
			uniform_int_distribution<int> parent(0, BEST_FROM_POPULATION_SIZE - 1);
			int parent_1 = parent(device);
			int parent_2 = parent(device);
			if (parent_1 == parent_2) { // Make sure we dont crossover on a single parent
				parent_2 = parent(device);
			}
			MemberOfPopulation member(best_out_of_population[parent_1], best_out_of_population[parent_2]);
			population.push_back(member);
		}
		// Show best ranking
			best_out_of_population[i].show_board();
			cout << "RANK: " << endl;
			best_out_of_population[i].show_rank();
			cout << endl;
		
	} while(best_out_of_population[0].rank != 100);
}

