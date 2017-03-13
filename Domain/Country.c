//
// Created by Eric on 08.03.2017.
//

#include "Country.h"


Country newCountry(char name[], Continent cont, int population)
{
    Country country;

    strcpy(country.name, name);
    country.continent = cont;
    country.population = population;

    return country;
}


char* getName(Country* country)
{
    return country->name;
}


Continent getContinent(Country* country)
{
    return country->continent;
}


int getPopulation(Country* country)
{
    return country->population;
}


char* ContinentToString(Continent cont, char continent_string[])
{
    char sEurope[] = {"Europe"};
    char sAsia[] = {"Asia"};
    char sAmerica[] = {"America"};
    char sAustralia[] = {"Australia"};
    char sAfrica[] = {"Africa"};
    char sError[] = {"Error: Unknown continent!"};

    switch (cont)
    {
        case Europe:
            strcpy(continent_string, sEurope);
            return continent_string;
        case Asia:
            strcpy(continent_string, sAsia);
            return continent_string;
        case America:
            strcpy(continent_string, sAmerica);
            return continent_string;
        case Australia:
            strcpy(continent_string, sAustralia);
            return continent_string;
        case Africa:
            strcpy(continent_string, sAfrica);
            return continent_string;
        default:
            strcpy(continent_string, sError);
            return continent_string;
    }
}

void strCountry(Country* country, char country_string[])
{
    char cont[STRING_LENGTH];
    char* cName = getName(country);
    Continent cContinent = getContinent(country);
    int cPopulation = getPopulation(country);
    char* contString = ContinentToString(cContinent, cont);
    sprintf(country_string, "%s | %s | %d\n", cName, contString, cPopulation);
}

int comparePopulation(Country* first, Country* second)
{
    int pop_first = getPopulation(first);
    int pop_second = getPopulation(second);

    if(pop_first> pop_second)
        return -1;

    if(pop_first == pop_second)
        return 0;

    if(pop_first < pop_second)
        return 1;

    return NULL; //if error occurs
}