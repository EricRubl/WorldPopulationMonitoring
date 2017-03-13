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
char* ControllerSearchCountries(Controller *controller, char subs[]);


//Get by continent
char *ControllerGetContinent(Controller *controller, Continent continent);


//Add new country
int ControllerAddCountry(Controller *controller, Country c);


//Delete a country
int ControllerDeleteCountry(Controller *controller, char name[]);


//Update a country
int ControllerUpdateCountry(Controller *controller, Country c, Country newc);


//Check if a country exists
int ControllerCheckCountry(Controller *controller, Country c);


//Get country object from corresponding name
Country ControllerCountryFromName(Controller* controller, char name[]);


//Migrate population
int ControllerMigratePopulation(Controller *controller, Country source, Country destination, int val);


#endif //WORLDPOPULATIONMONITORING_CONTROLLER_H
