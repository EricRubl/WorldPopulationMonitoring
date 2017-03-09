//
// Created by Eric on 08.03.2017.
//

#ifndef WORLDPOPULATIONMONITORING_DYNAMICCONTAINER_H
#define WORLDPOPULATIONMONITORING_DYNAMICCONTAINER_H

#include "Country.h"
#include <stdlib.h>


//////////////////////////////////////////////////////////
//                      DEFINES
//////////////////////////////////////////////////////////

//Generic vector element
typedef Country Element;


//Element constructor
typedef Element (*makeElement)(char name[], Continent cont, int population);


//Function for comparation between elements
typedef int (*compElement)(Element* first, Element* second);


//Structure of the ADT
//elements - dynamically allocated array for elements
//length - current stored capacity of elements
//capacity - maximum capacity (variable)
typedef struct
{
    Element* elements;
    int length;
    int capacity;
} DynamicArray;


//Constructor for DynamicArray
DynamicArray* initArray(int capacity);


//

#endif //WORLDPOPULATIONMONITORING_DYNAMICCONTAINER_H

