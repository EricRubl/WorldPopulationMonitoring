//
// Created by Eric on 12.03.2017.
//

#include "Controller.h"


Controller initController(Repo *repo)
{
    Controller controller;
    controller.countryRepo = repo;
    return controller;
}


char* searchCountries(Controller *controller, char subs[])
{
    int i, len = 0;
    DynamicArray *c = getItemsBySubstring(controller->countryRepo, subs);
    if(c == NULL)
        return NULL;
    len = getLength(c);

    int buffer = len * STRING_LENGTH;
    char* format = (char*) malloc(buffer * sizeof(char));
    format[0] = 0;
    for(i = 0; i < len; i++)
    {
        Country ctr = getElement(c, i);
        char re[20];
        strCountry(&ctr, re);
        strcat(format, re);
    }
    return format;
}


char *continentCountries(Controller *controller, Continent continent)
{
    int i, len = 0;
    DynamicArray *c = getItemsByContinent(controller->countryRepo, continent);
    if(c == NULL)
        return NULL;
    len = getLength(c);

    int buffer = 2 * len + len * STRING_LENGTH * (sizeof(char));
    char *format = (char *) malloc(2 * len + len * STRING_LENGTH * (sizeof(char)));
    memset(format, 1, 2 * len + len * STRING_LENGTH * (sizeof(char)));
    format[buffer - 1] = 0;
    for(i = 0; i < len; i++)
    {
        Country ctr = getElement(c, i);
        char re[STRING_LENGTH];
        strCountry(&ctr, re);
        strcat(re, "\n");
        strcat(format, re);
    }
    return format;
}


int addCountry(Controller *controller, Country c)
{
    return addItem(controller->countryRepo, c);
}


int deleteCountry(Controller *controller, Country c)
{
    return deleteItem(controller->countryRepo, c);
}


int modifyCountry(Controller *controller, Country c, Country newc)
{
    return updateCountry(controller->countryRepo, c, newc);
}


int checkCountry(Controller *controller, Country c)
{
    int i, len = getRepoLength(controller->countryRepo);
    for(i = 0; i < len; i++)
    {
        Country ctr = getItem(controller->countryRepo, i);
        if(comparePopulation(&ctr, &c) == 0)
            return 1;
    }
    return 0;
}


int migratePopulation(Controller *controller, Country source, Country destination, int val)
{
    if(!(checkCountry(controller, source) && checkCountry(controller, destination)))
        return 0;

    int pops = getPopulation(&source);
    int popd = getPopulation(&destination);

    if(val > pops)
        return 0;

    Country new_source = newCountry(getName(&source), getContinent(&source), pops - val);
    Country new_destination = newCountry(getName(&destination), getContinent(&destination), popd + val);
    modifyCountry(controller, source, new_source);
    modifyCountry(controller, destination, new_destination);

    return 1;
}