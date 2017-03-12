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


//Function for comparison between elements
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


//Destructor for DynamicArray
void destroyArray(DynamicArray **array);


//Push element at the end
void push(DynamicArray* array, Element e);


//Getter for current length
int getLength(DynamicArray* array);


//Getter for current capacity
int getCapacity(DynamicArray* array);


//Resize the capacity of vector
void resize(DynamicArray* array);


//Getter for element
Element getElement(DynamicArray* array, int index);


//Swapper for two elements
void swap(DynamicArray* array, int first, int second);


//Sort function
void sort(DynamicArray* array, compElement function, int direction);



#endif //WORLDPOPULATIONMONITORING_DYNAMICCONTAINER_H

