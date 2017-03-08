//
// Created by Eric on 08.03.2017.
//


#include "tests.h"


void performTests()
{
    int flag_country = testCountry();

    if(flag_country)
    {
        printf("Tests performed, no malfunction\nPress any key to continue\n");
        system("pause>nul");
    }
    else
    {
        printf("Tests found malfunctions!\nProcess will now terminate\n");
        system("pause>nul");
        exit(1);
    }

}


int testCountry()
{
    Country test_country = newCountry("Austria", Europe, 9);

    if(strcmp(getName(&test_country), "Austria") != 0 || getContinent(&test_country) != Europe || getPopulation(&test_country) != 9)
        return 0;

    char cont_str[STRING_LENGTH];
    if(strcmp(ContinentToString(getContinent(&test_country), cont_str), "Austria") != 0)
        return 0;

    char c_string[STRING_LENGTH];
    strCountry(&test_country, c_string);
    if(strcmp(c_string, "Austria | Europe | 9\n") != 0)
        return 0;

    return 1;
}