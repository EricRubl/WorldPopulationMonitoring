//
// Created by Eric on 11.03.2017.
//

#include "Repository.h"

Repo *initRepo()
{
    Repo *repo = malloc(sizeof(Repo));
    if(repo == NULL)
        return NULL;

    repo->countries = initArray(1);
    return repo;
}


void destroyRepo(Repo **repo)
{
    if(repo == NULL)
        return;

    destroyArray(&(*repo)->countries);
    free(*repo);
    *repo = NULL;
}


int RepoAddCountry(Repo *repo, Country c)
{
    if(repo == NULL)
        return -1;

    if(RepoGetPosition(repo, getName(&c)) >= 0)
        return 0;

    push(repo->countries, c);
    return 1;
}


int RepoGetLength(Repo *repo)
{
    if(repo == NULL)
        return -1;

    return getLength(repo->countries);
}


int RepoGetPosition(Repo *repo, char name[])
{
    if(repo == NULL)
        return -1;

    int i;
    for(i = 0; i < RepoGetLength(repo); i++)
    {
        Country c = RepoGetCountry(repo, i);
        if(strcmp(getName(&c), name) == 0)
            return i;
    }
    return -1;
}


Country RepoGetCountry(Repo *repo, int index)
{
    if(repo == NULL || index < 0 || index > RepoGetLength(repo))
        return newCountry("", Dummy, -1);

    return getElement(repo->countries, index);
}


int RepoDeleteCountryByName(Repo *repo, char name[])
{
    if(repo == NULL)
        return -1;

    int pos = RepoGetPosition(repo, name);
    if(pos == -1)
        return -1;

    int newCapacity = RepoGetCapacity(repo);
    int oldLength = RepoGetLength(repo);
    if((oldLength < newCapacity - 1) && newCapacity > 0)
        newCapacity--;

    DynamicArray *newElements = initArray(newCapacity);
    int i;
    for(i = 0; i < oldLength; i++)
        if(i != pos)
            push(newElements, RepoGetCountry(repo, i));


    DynamicArray *oldElements = repo->countries;
    repo->countries = newElements;
    destroyArray(&oldElements);

    return 1;
}


DynamicArray *RepoSearchCountry(Repo *repo, char *subs)
{
    char *pos;
    if((pos = strchr(subs, '\n')) != NULL)
        *pos = '\0';

    if(strcmp(subs, "") == 0)
    {
        DynamicArray *allCountries = initArray(RepoGetLength(repo));
        int i;
        if(RepoGetLength(repo) == 0)
        {
            destroyArray(&allCountries);
            return NULL;
        }
        for(i = 0; i < RepoGetLength(repo); ++i)
            push(allCountries, RepoGetCountry(repo, i));
        return allCountries;
    }

    int occ = 0, i;
    for(i = 0; i < RepoGetLength(repo); ++i)
    {
        Country c = RepoGetCountry(repo, i);
        if(strstr(getName(&c), subs) != NULL)
            occ++;
    }

    if(occ == 0)
        return NULL;

    DynamicArray *foundElements = initArray(occ);
    for(i = 0; i < RepoGetLength(repo); ++i)
    {
        Country c = RepoGetCountry(repo, i);
        if(strstr(getName(&c), subs) != NULL)
            push(foundElements, c);
    }

    return foundElements;
}


DynamicArray *RepoGetContinent(Repo *repo, Continent continent, int val)
{
    int occ = 0, i;

    if(continent == Dummy)
    {
        for(i = 0; i < RepoGetLength(repo); ++i)
        {
            Country c = RepoGetCountry(repo, i);
            if(getPopulation(&c) > val)
                occ++;
        }

        if(occ == 0)
            return NULL;

        DynamicArray *foundElements = initArray(occ);
        for(i = 0; i < RepoGetLength(repo); ++i)
        {
            Country c = RepoGetCountry(repo, i);
            if(getPopulation(&c) > val)
                push(foundElements, c);
        }

        sort(foundElements, comparePopulation, -1);
        return foundElements;
    }


    for(i = 0; i < RepoGetLength(repo); ++i)
    {
        Country c = RepoGetCountry(repo, i);
        if(getContinent(&c) == continent && getPopulation(&c) > val)
            occ++;
    }

    if(occ == 0)
        return NULL;

    DynamicArray *foundElements = initArray(occ);
    for(i = 0; i < RepoGetLength(repo); ++i)
    {
        Country c = RepoGetCountry(repo, i);
        if(getContinent(&c) == continent && getPopulation(&c) > val)
            push(foundElements, c);
    }

    sort(foundElements, comparePopulation, -1);
    return foundElements;
}


int RepoGetCapacity(Repo *repo)
{
    return getCapacity(repo->countries);
}


int RepoDeleteCountry(Repo *repo, Country c)
{
    int i, len = RepoGetLength(repo), removeIndex = -1;

    for(i = 0; i < len; ++i)
    {
        Country curr = RepoGetCountry(repo, i);

        if(comparePopulation(&curr, &c) == 0)
        {
            removeIndex = i;
            break;
        }
    }

    if(removeIndex == -1)
        return 0;

    DynamicArray *newElements = initArray(RepoGetCapacity(repo));

    for(i = 0; i < len; ++i)
    {
        if(i == removeIndex)
            continue;
        else
        {
            push(newElements, RepoGetCountry(repo, i));
        }
    }

    free(repo->countries->elements);
    repo->countries->elements = malloc(sizeof(Element) * repo->countries->capacity);
    memcpy(repo->countries->elements, newElements->elements, sizeof(Element) * (len - 1));
    repo->countries->length--;

    destroyArray(&newElements);
    return 1;
}

int RepoUpdateCountry(Repo *repo, Country c, Country newc)
{
    int i, countryIndex = -1;
    for(i = 0; i < RepoGetLength(repo); ++i)
    {
        Country curr = RepoGetCountry(repo, i);
        if(comparePopulation(&c, &curr) == 0)
        {
            countryIndex = i;
            break;
        }
    }

    if(countryIndex == -1)
        return 0;

    RepoDeleteCountry(repo, c);
    RepoAddCountry(repo, newc);

    return 1;
}