/**
 * @Author: Brandon Baars <brandon>
 * @Date:   Wednesday, June 14th 2017, 4:10:56 pm
 * @Filename: Genetic.cpp
 * @Last modified by:   brandon
 * @Last modified time: Monday, June 19th 2017, 10:14:31 am
 */

 #include <random>
 #include <vector>
 #include <iostream>
 #include <cmath>
 #include <stdlib.h>
 #include "Genetic.h"

/* Defines the population size to 100 */
 #define POP_SIZE 100

 int main(int argc, char **argv) {

     srand(time(NULL));

     /* We will start at first generation */
     int generation = 1;

     /* Parent colors with highest Fitness */
     Color parent1, parent2;

     /* Color structure to house the GV Blue */
     Color gvColor;

     /* Populates the color structure with the GV Blue RGB Values */
     gvColor.red = 0;
     gvColor.green = 101;
     gvColor.blue = 164;

     /* If ran through our fitness function it would 'give' a fitness of 565. i.e 255 + 255 + 255 */
     gvColor.fitness = 765;

     /* population of Color structures */
     std::vector<Color> population;

     /* populates with random RGB Values and calculates the fitness */
     populatePopulation(population, gvColor);

     /* selects the two parents with the highest fitness values */
     while(!crossover(population, parent1, parent2, generation));

     return 0;
 }

 /*
 *   Print the Population
 */
void printPopulation(std::vector<Color> & population) {
    for (Color color: population)
        std::cout << color << std::endl;
}


 /* finds the different in the two colors and subtracts them from 255.  * a perfect match will send a 765 (highest fitness), the further off   * the RGB Values, the closer to 0 it will return
 */
 int fitness(Color color) {

     /* Color structure to house the GV Blue */
     Color gvColor;

     /* Populates the color structure with the GV Blue RGB Values */
     gvColor.red = 0;
     gvColor.green = 101;
     gvColor.blue = 164;

     return (255 - abs(gvColor.red - color.red)) + (255 - abs(gvColor.green - color.green)) + (255 - abs(gvColor.blue - color.blue));
 }

 /*
 *   Populates the Population
 */
 void populatePopulation(std::vector<Color> & population, Color & gvColor) {

     /* Grand Valley RGB Values */
     const int max = 256;

     for (int p = 0 ; p < POP_SIZE ; p++) {

         /* Uses random based on clock time */
         std::random_device rd;
         std::mt19937 mt (rand());
         std::uniform_int_distribution<int> i(0, max);

         /* pushes a color into the population vector */
         Color color;
         population.push_back(color);

         for(int c = 0 ; c < 3 ; c++) {
            // int rand = i(mt);

            int random = rand() % 256;

             /* adds the random numbers to the color variables */
             switch(c){
                 case 0:
                     population[p].red = random;
                     break;

                 case 1:
                     population[p].green = random;
                     break;

                 case 2:
                     population[p].blue = random;
                     break;
             }
         }

        population[p].fitness = fitness(population[p]);
     }
 }


/*
*  Select the highest two fitness values as the parents, mutate them
*/
bool crossover(std::vector<Color> & population, Color & parent1, Color & parent2, int & generation) {

    /* new child color */
    Color newColor;

    /* for the Max and Second Highest Fitness */
    int maxVal = 0, secondMax = 0;

    /* Finds the two highest fitness' from the population */
    for (int i = 0 ; i < population.size() ; i++){

        /* finds the current max in the vector */
        if(population[i].fitness > maxVal) {
            parent2 = parent1;
            parent1 = population[i];
            maxVal = population[i].fitness;

        /* finds the second highest in the vector */
        } else if (population[i].fitness > secondMax) {
            parent2 = population[i];
            secondMax = population[i].fitness;
        }
    }

    if (generation == 1) {
        std::cout << "Generation: " << generation << " Fitness: " << " " << parent1 << std::endl;
    }

    population.clear();

    for (int i = 0 ; i < POP_SIZE ; i++) {
        for(int c = 0 ; c < 3 ; c++){
            int randParent = rand() % 2;

            /* if the random parent generated is parent 1, pull values from Parent 1 */
            if (randParent == 0) {
                /* adds the random numbers to the color variables */
                switch(c){
                    case 0:
                        newColor.red = parent1.red;
                        break;

                    case 1:
                        newColor.green = parent1.green;
                        break;

                    case 2:
                        newColor.blue = parent1.blue;
                        break;
                }
            }

            /* if the random parent generated is parent 1, pull values from Parent 1 */
            else {
                /* adds the random numbers to the color variables */
                switch(c){
                    case 0:
                        newColor.red = parent2.red;
                        break;

                    case 1:
                        newColor.green = parent2.green;
                        break;

                    case 2:
                        newColor.blue = parent2.blue;
                        break;
                }
            }
        }

        mutate(newColor);
        newColor.fitness = fitness(newColor);
        population.push_back(newColor);

        if(newColor.fitness == 765){
            std::cout << "Generation: " << ++generation << " Fitness: " << " " << newColor << std::endl;
            return true;
        }
    }

    std::cout << "Generation: " << ++generation << " Fitness: " << " " << newColor << std::endl;

    return false;
}

 /*
 *  Mutates the parents slightly and creates a new generation
 */
void mutate(Color & color) {


    for (int i = 0 ; i < 3 ; i++) {

        /* random number between -5 and 5 */
        int mutation = (rand() % 10) - 5;

        /* Adds the mutation to the colors
            checks to see if it'll go below 0 or higher than 255 */
        switch(i){
            case 0:
                color.red += mutation;

                if (color.red < 0)
                    color.red = 0;
                else if (color.red > 255)
                    color.red = 255;

                break;

            case 1:
                color.green += mutation;

                if (color.green < 0)
                    color.green = 0;
                else if (color.green > 255)
                    color.green = 255;

                break;

            case 2:
                color.blue += mutation;

                if (color.blue < 0)
                    color.blue = 0;
                else if (color.blue > 255)
                    color.blue = 255;
                break;
        }
    }
}
