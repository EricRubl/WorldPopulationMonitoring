//
// Created by Eric on 11.03.2017.
//

#ifndef WORLDPOPULATIONMONITORING_REPOSITORY_H
#define WORLDPOPULATIONMONITORING_REPOSITORY_H

#include "../Domain/Country.h"
#include "../Domain/DynamicArray.h"


typedef struct
{
    DynamicArray *countries;
} CountryRepo;


//Constructor for repository
CountryRepo *initRepo();


//Destructor for repository

#endif //WORLDPOPULATIONMONITORING_REPOSITORY_H
