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
int RepoAddCountry(Repo *repo, Country c);


//Getter for length
int RepoGetLength(Repo *repo);


//Getter for position
int RepoGetPosition(Repo *repo, char name[]);


//Getter for item
Country RepoGetCountry(Repo *repo, int index);


//Delete by name
int RepoDeleteCountryByName(Repo *repo, char name[]);


//Search item by substring
DynamicArray *RepoSearchCountry(Repo *repo, char *subs);


//Get items by continent
DynamicArray *RepoGetContinent(Repo *repo, Continent continent);


//Getter for repo capacity
int RepoGetCapacity(Repo *repo);


//Delete item
int RepoDeleteCountry(Repo *repo, Country c);


//Update country
int RepoUpdateCountry(Repo *repo, Country c, Country newc);


#endif //WORLDPOPULATIONMONITORING_REPOSITORY_H