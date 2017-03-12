//
// Created by Eric on 12.03.2017.
//

#ifndef WORLDPOPULATIONMONITORING_CONTROLLER_H
#define WORLDPOPULATIONMONITORING_CONTROLLER_H

#include "../Repository/Repository.h"


typedef struct
{
    Repo *countryRepo;

} Controller;


//Constructor for controller
Controller initController(Repo *repo);


//Search countries
char *searchCountries(Controller *controller, char subs[]);


//Get by continent
char *continentCountries(Controller *controller, Continent continent);


//Add new country
int addCountry(Controller *controller, Country c);


//Delete a country
int deleteCountry(Controller *controller, Country c);


//Update a country
int modifyCountry(Controller *controller, Country c, Country newc);


//Check if a country exists
int checkCountry(Controller *controller, Country c);


//Migrate population
int migratePopulation(Controller *controller, Country source, Country destination, int val);


#endif //WORLDPOPULATIONMONITORING_CONTROLLER_H
