/**
 * @Author: Brandon Baars <brandon>
 * @Date:   Sunday, June 18th 2017, 4:41:10 pm
 * @Filename: Genetic.h
 * @Last modified by:   brandon
 * @Last modified time: Sunday, June 18th 2017, 9:10:38 pm
 */

#ifndef __H_GENETIC__
#define __H_GENETIC__

#include <iostream>
#include <vector>


/* Color structure to house our RGB Values and our Fitness for that Color */
 struct Color {
     int red = 0;
     int green = 0;
     int blue = 0;
     int fitness = 0;
 };

 /*
 *   Print the Population
 */
void printPopulation(std::vector<Color> & population);


 /* finds the different in the two colors and subtracts them from 255.  * a perfect match will send a 765 (highest fitness), the further off   * the RGB Values, the closer to 0 it will return
 */
 int fitness(Color color) ;


 /*
 *   Populates the Population
 */
 void populatePopulation(std::vector<Color> & population, Color & gvColor);

 /*
 *  Select the highest two fitness values as the parents
 */
void selectParents(std::vector<Color> & population, Color & parent1, Color & parent2);


/*
*  Select the highest two fitness values as the parents, mutate them
*/
bool crossover(std::vector<Color> & population, Color & parent1, Color & parent2, int & generation);


/*
*  Mutates the parents slightly and creates a new generation
*/
void mutate(Color & color);

/* overrides the ostream operator to be able to print the data type Color */
std::ostream& operator<< (std::ostream & stream, const Color & c) {
    return stream << "rgb(" << c.red << "," << c.green << "," << c.blue << ")" << " Fitness: " << c.fitness;
}

#endif
