//
// Created by Eric on 08.03.2017.
//

#ifndef WORLDPOPULATIONMONITORING_COUNTRY_H
#define WORLDPOPULATIONMONITORING_COUNTRY_H

#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////
//                DEFINES AND ENUMS
//////////////////////////////////////////////////////////

#define STRING_LENGTH 50


//Continent enum
typedef enum
{
    Europe, Asia, America, Australia, Africa
} Continent;


//Country data structure
typedef struct
{
    char name[STRING_LENGTH];
    Continent continent;
    int population; //in millions
} Country;

//////////////////////////////////////////////////////////
//            METHODS FOR COUNTRY AND CONTINENT
//////////////////////////////////////////////////////////

//Country constructor
//Input: name, continent, population
//Output: Country object
Country newCountry(char name[], Continent cont, int population);


//Getter for country name
char* getName(Country* country);


//Getter for continent
Continent getContinent(Country* country);


//Getter for country population
int getPopulation(Country* country);


//Continent string generator
char* ContinentToString(Continent cont, char continent_string[]);


//Country "str method" for printing inm the UI
void strCountry(Country* country, char country_string[]);


//Compare function for country population
//Standard (-1 | 0 | 1) return value
int comparePopulation(Country* first, Country* second);

#endif //WORLDPOPULATIONMONITORING_COUNTRY_H
