#include "evolutive.h"
#include <stdlib.h>
#include <assert.h>

int is_in_array(unsigned int* array, unsigned int size, unsigned int x){

   for(unsigned int i=0; i < size; i++){
      if(array[i] == x)
         return 1;
   }

   return 0;
}

void swap(unsigned int* array, unsigned int index1, unsigned int index2, unsigned arraySize){
   assert(index1 < arraySize && index2 < arraySize);

   unsigned int temp = array[index1];
   array[index1] = array[index2];
   array[index2] = temp;
}

void shuffle_array(unsigned int* array, unsigned int arraySize){

   for(unsigned int i=0; i < arraySize; i++){
      swap(array, rand() % arraySize, rand() % arraySize, arraySize);
   }
}

unsigned int* generate_individual(unsigned int arraySize){

   unsigned int* individual = malloc(sizeof(unsigned int*) * arraySize);
   for(unsigned int i=0; i < arraySize; i++)
      individual[i] = i;

   shuffle_array(individual, arraySize);

   return individual;
}

unsigned int evaluate_fitness(unsigned int* individual, unsigned int* solution, unsigned int size){

   unsigned int fitness = 0;
   for(unsigned int i=0; i < size; i++)
      if(individual[i] == solution[i])
         fitness++;

   return fitness;
}

unsigned int* tournament_selection(unsigned int** population, unsigned int populationSize, unsigned tournamentSize,
   unsigned int* solution, unsigned int individualSize){

   unsigned int individualIndex = rand() % populationSize;
   unsigned int individualFitness = evaluate_fitness(population[individualIndex], solution, individualSize);

   for(unsigned int i=1; i < tournamentSize; i++){
      unsigned int newIndex = rand() % populationSize;
      unsigned int newFitness = evaluate_fitness(population[newIndex], solution, individualSize);

      if(newFitness > individualFitness){
         individualIndex = newIndex;
         individualFitness = newFitness;
      }
   }

   return population[individualIndex];
}

void mutate(unsigned int* individual, unsigned int arraySize){
   swap(individual, rand() % arraySize, rand() % arraySize, arraySize);
}

unsigned int* crossover(unsigned int* individual1, unsigned int* individual2, unsigned int arraySize){

   unsigned int* child = malloc(sizeof(unsigned int*) * arraySize);
   unsigned int size = rand() % (arraySize/2) + (arraySize/5);

   for(unsigned int i=0; i < size; i++){
      child[i] = individual1[i];
   }

   unsigned int found = 0;
   for(unsigned int i=0; i < arraySize && found < (arraySize - size); i++){
      if(!is_in_array(individual1, size, individual2[i])){
         child[size + found] = individual2[i];
         found++;
      }
   }

   return child;
}

unsigned int** evolve_population(unsigned int** population, unsigned int populationSize, unsigned int individualSize,
   unsigned int tournamentSize,  unsigned int* solution){

   unsigned int** evolvedPopulation = malloc(sizeof(unsigned int**) * populationSize);

   for(unsigned int i=0; i < populationSize; i++){

      unsigned int* parent1 = tournament_selection(population, populationSize, tournamentSize, solution, individualSize);
      unsigned int* parent2 = tournament_selection(population, populationSize, tournamentSize, solution, individualSize);

      unsigned int* child = crossover(parent1, parent2, individualSize);
      mutate(child, individualSize);

      evolvedPopulation[i] = child;
   }

   for(unsigned int i=0; i < populationSize; i++)
      free(population[i]);
   free(population);

   return evolvedPopulation;
}

unsigned int get_max_fitness(unsigned int** population, unsigned int populationSize, unsigned individualSize,
   unsigned int* solution){

   unsigned int maxFitness = 0;
   for(unsigned int i=0; i < populationSize; i++){
      unsigned int newFitness = evaluate_fitness(population[i], solution, individualSize);
      if(newFitness > maxFitness)
         maxFitness = newFitness;
   }

   return maxFitness;
}

unsigned int* get_fittest_individual(unsigned int** population, unsigned int populationSize, unsigned individualSize,
   unsigned int* solution){

   unsigned int maxFitness = 0;
   unsigned int index = 0;

   for(unsigned int i=0; i < populationSize; i++){
      unsigned int newFitness = evaluate_fitness(population[i], solution, individualSize);
      if(newFitness > maxFitness){
         maxFitness = newFitness;
         index = i;
      }
   }

   return population[index];
}