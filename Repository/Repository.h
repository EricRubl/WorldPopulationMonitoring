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
} Repo;


//Constructor for repository
Repo *initRepo();


//Destructor for repository
void destroyRepo(Repo **repo);


//Add item to repo
int addItem(Repo *repo, Country c);


//Getter for length
int getRepoLength(Repo *repo);


//Getter for position
int getRepoPosition(Repo *repo, char name[]);


//Getter for item
Country getItem(Repo *repo, int index);


//Delete by name
int deleteByName(Repo *repo, char name[]);


//Update by index
int updateByIndex(Repo *repo, Country c, int index);


//Search item by substring
DynamicArray *getItemsBySubstring(Repo *repo, char *subs);


//Get items by continent
DynamicArray *getItemsByContinent(Repo *repo, Continent continent);


//Getter for repo capacity
int getRepoCapacity(Repo *repo);


//Delete item
int deleteItem(Repo *repo, Country c);


//Update country
int updateCountry(Repo *repo, Country c, Country newc);


//Clear repo
void clearRepo(Repo *repo);


#endif //WORLDPOPULATIONMONITORING_REPOSITORY_H
