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


char* ControllerSearchCountries(Controller *controller, char subs[])
{
    int i, len = 0;
    DynamicArray *found = RepoSearchCountry(controller->countryRepo, subs);
    if(found == NULL)
        return NULL;
    len = getLength(found);

    int buffer = len * 20;
    char* format = (char*) malloc(buffer * sizeof(char));
    format[0] = 0;
    for(i = 0; i < len; i++)
    {
        Country ctr = getElement(found, i);
        char re[20];
        countryToString(&ctr, re);
        strcat(format, re);
    }
    return format;
}


char *ControllerGetContinent(Controller *controller, Continent continent)
{

    int i, len = 0;
    DynamicArray *c = RepoGetContinent(controller->countryRepo, continent);
    if(c == NULL)
        return NULL;
    len = getLength(c);

    int buffer = len * 20;
    char* format = (char*)malloc(buffer * sizeof(char));
    format[0] = 0;
    for(i = 0; i < len; i++)
    {
        Country ctr = getElement(c, i);
        char re[STRING_LENGTH];
        countryToString(&ctr, re);
        strcat(format, re);
    }
    return format;
}


int ControllerAddCountry(Controller *controller, Country c)
{
    return RepoAddCountry(controller->countryRepo, c);
}


int ControllerDeleteCountry(Controller *controller, char name[])
{
    return RepoDeleteCountryByName(controller->countryRepo, name);
}


int ControllerUpdateCountry(Controller *controller, Country c, Country newc)
{
    return RepoUpdateCountry(controller->countryRepo, c, newc);
}


int ControllerCheckCountry(Controller *controller, Country c)
{
    int i;
    for(i = 0; i < RepoGetLength(controller->countryRepo); i++)
    {
        Country ctr = RepoGetCountry(controller->countryRepo, i);
        if(comparePopulation(&ctr, &c) == 0)
            return 1;
    }
    return 0;
}


Country ControllerCountryFromName(Controller* controller, char name[])
{
    Country ret = newCountry("", Dummy, -1);

    int pos = RepoGetPosition(controller->countryRepo, name);
    if(pos == -1)
        return ret;

    return RepoGetCountry(controller->countryRepo, pos);
}


int ControllerMigratePopulation(Controller *controller, Country source, Country destination, int val)
{
    if(!(ControllerCheckCountry(controller, source) && ControllerCheckCountry(controller, destination)))
        return 0;

    int pop_s = getPopulation(&source);
    int pop_d = getPopulation(&destination);

    if(val > pop_s)
        return 0;

    Country new_source = newCountry(getName(&source), getContinent(&source), pop_s - val);
    Country new_destination = newCountry(getName(&destination), getContinent(&destination), pop_d + val);
    ControllerUpdateCountry(controller, source, new_source);
    ControllerUpdateCountry(controller, destination, new_destination);

    return 1;
}