#include <stdio.h>
#include <stdlib.h>
#include "evolutive.h"
#include <time.h>

const unsigned int ARRAY_SIZE = 10;
const unsigned int POPULATION_SIZE = 100;
const unsigned int TOURNAMENT_SIZE = 5;
const unsigned int MAX_GENERATIONS = 200;

int main(){

   srand(time(NULL));

   unsigned int testArray[ARRAY_SIZE];
   for(unsigned int i=0; i < ARRAY_SIZE; i++){
      testArray[i] = i;
   }

   unsigned int** population = malloc(sizeof(unsigned int*) * POPULATION_SIZE);
   for(unsigned int i=0; i < POPULATION_SIZE; i++)
      population[i] = generate_individual(ARRAY_SIZE);

   printf("Population generated\n");
   printf("Printing population:\n");

   for(unsigned int i=0; i < POPULATION_SIZE; i++){
      printf("Individual %u: ", i);
      for(unsigned int j=0; j < ARRAY_SIZE; j++){
         printf("%u ", population[i][j]);
      }
      printf("\n");
   }

   unsigned int maxFitness = 0;
   for(unsigned int i=0; i < MAX_GENERATIONS && maxFitness != ARRAY_SIZE; i++){
      population = evolve_population(population, POPULATION_SIZE, ARRAY_SIZE, TOURNAMENT_SIZE, testArray);
      maxFitness = get_max_fitness(population, POPULATION_SIZE, ARRAY_SIZE, testArray);
      printf("Generation %u, Max Fitness: %u\n", i+1, maxFitness);
   }

   unsigned int* fittest = get_fittest_individual(population, POPULATION_SIZE, ARRAY_SIZE, testArray);
   printf("Fittest individual: ");
   for(unsigned int i=0; i < ARRAY_SIZE; i++){
      printf("%u ", fittest[i]);
   }

   for(unsigned int i=0; i < POPULATION_SIZE; i++)
      free(population[i]);
   free(population);

   return 0;
}