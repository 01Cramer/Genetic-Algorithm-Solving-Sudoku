#include <iostream>
#include "MemberOfPopulation.h"
#include <vector>
#include <algorithm>
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
	std::sort(population.begin(), population.end(), [](const MemberOfPopulation& lhs, const MemberOfPopulation& rhs) {return lhs.rank > rhs.rank; });
	vector<MemberOfPopulation> best_out_of_population;
	const int BEST_FROM_POPULATION_SIZE = 50;
	for (int i = 0; i < BEST_FROM_POPULATION_SIZE; i++) {
		best_out_of_population.push_back(population[i]);
	}
	population.clear();

	// Show best rankings
	for (int i = 0; i < 5; i++) {
		best_out_of_population[i].show_board();
		cout << "RANK: " << endl;
		best_out_of_population[i].show_rank();
		cout << endl;
	}
}

