#ifndef __EVOLUTIVE__
#define __EVOLUTIVE__

//void bubble_sort(unsigned int* array);

void swap(unsigned int* array, unsigned int index1, unsigned int index2, unsigned arraySize);

void shuffle_array(unsigned int* array, unsigned int arraySize);

int is_in_array(unsigned int* array, unsigned int size, unsigned int x);

/*
Generates an individual.
Allocated array of integers from 0 to 9 in random order.
*/
unsigned int* generate_individual(unsigned int arraySize);

/*
Evaluates the fitness of an individual based on the provided solution.
Max fitness = size
*/
unsigned int evaluate_fitness(unsigned int* individual, unsigned int* solution, unsigned int size);

/*
Returns an individual from the given population using tournament selection.
*/
unsigned int* tournament_selection(unsigned int** population, unsigned int populationSize, unsigned tournamentSize,
   unsigned int* solution, unsigned int individualSize);

/*
Creates a new individual by combining two individuals.
*/
unsigned int* crossover(unsigned int* individual1, unsigned int* individual2, unsigned int arraySize);

/*
Applies a mutation to an individual.
Effectively swaps two random elements of the array.
*/
void mutate(unsigned int* individual, unsigned int arraySize);

/*
Evolves a population.
Previous population is freed.
Returns a pointer to the evolved population.
*/
unsigned int** evolve_population(unsigned int** population, unsigned int populationSize, unsigned int individualSize,
   unsigned int tournamentSize, unsigned int* solution);

unsigned int get_max_fitness(unsigned int** population, unsigned int populationSize, unsigned individualSize,
   unsigned int* solution);

unsigned int* get_fittest_individual(unsigned int** population, unsigned int populationSize, unsigned individualSize,
   unsigned int* solution);

#endif