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

    DynamicArray *countries = (*repo)->countries;
    destroyArray(&countries);
    free(*repo);
    *repo = NULL;
}


int addItem(Repo *repo, Country c)
{
    if(repo == NULL)
        return -1;

    if(getRepoPosition(repo, getName(&c)) >= 0)
        return 0;

    DynamicArray *countries = repo->countries;
    push(countries, c);
    return 1;
}


int getRepoLength(Repo *repo)
{
    if(repo == NULL)
        return -1;

    DynamicArray *countries = repo->countries;
    return getLength(countries);
}


int getRepoPosition(Repo *repo, char name[])
{
    if(repo == NULL)
        return -1;

    int i;
    for(i = 0; i < getRepoLength(repo); i++)
    {
        Country c = getItem(repo, i);
        if(strcmp(getName(&c), name) == 0)
            return i;
    }
    return -1;
}


Country getItem(Repo *repo, int index)
{
    if(repo == NULL || index < 0 || index > getLength(repo->countries))
        return newCountry("", Dummy, -1);

    return getElement(repo->countries, index);
}


int deleteByName(Repo *repo, char name[])
{
    if(repo == NULL)
        return -1;

    int pos = getRepoPosition(repo, name);
    if(pos == -1)
        return -1;

    int newCapacity = getCapacity(repo->countries);
    int oldLength = getLength(repo->countries);
    if((oldLength < newCapacity - 1) && newCapacity > 0)
        newCapacity--;

    DynamicArray *newElements = initArray(newCapacity);
    int i;
    for(i = 0; i < oldLength; i++)
    {
        if(i != pos)
            push(newElements, getItem(repo, i));

    }

    DynamicArray *oldElements = repo->countries;
    repo->countries = newElements;
    destroyArray(&oldElements);

    return 1;
}


int updateByIndex(Repo *repo, Country c, int index)
{
    if(repo == NULL)
        return -1;

    if(index < 0 || index > getRepoLength(repo) - 1)
        return 0;

    DynamicArray *newElements = initArray(getCapacity(repo->countries));
    int i, len = getCapacity(repo->countries);
    for(i = 0; i < len; i++)
        if(i == index)
            push(newElements, c);
        else
            push(newElements, getItem(repo, i));

    DynamicArray *oldElements = repo->countries;
    repo->countries = newElements;
    destroyArray(&oldElements);

    return 1;
}


DynamicArray *getItemsBySubstring(Repo *repo, char *subs)
{
    char *pos;
    if((pos = strchr(subs, '\n')) != NULL)
        *pos = '\0';

    if(strcmp(subs, "") == 0)
    {
        DynamicArray *allCoubntries = initArray(getCapacity(repo->countries));
        int i, len = getRepoLength(repo);
        if(len == 0)
        {
            destroyArray(&allCoubntries);
            return NULL;
        }
        for(int i = 0; i < len; ++i)
            push(allCoubntries, getItem(repo, i));
        return allCoubntries;
    }

    int occ = 0, i, len = getRepoLength(repo);
    for(i = 0; i < len; ++i)
    {
        Country c = getItem(repo, i);
        if(strstr(getName(&c), subs) != NULL)
            occ++;
    }

    if(occ == 0)
        return NULL;

    DynamicArray *foundElements = initArray(occ);
    for(i = 0; i < len; ++i)
    {
        Country c = getItem(repo, i);
        if(strstr(getName(&c), subs) != NULL)
            push(foundElements, c);
    }

    return foundElements;
}


DynamicArray *getItemsByContinent(Repo *repo, Continent continent)
{
    if(continent == Dummy)
        return NULL;

    int occ = 0, i, len = getRepoLength(repo);
    for(i = 0; i < len; ++i)
    {
        Country c = getItem(repo, i);
        if(getContinent(&c) == continent)
            occ++;
    }

    if(occ == 0)
        return NULL;

    DynamicArray *foundElements = initArray(occ);
    for(i = 0; i < len; ++i)
    {
        Country c = getItem(repo, i);
        if(getContinent(&c) == continent)
            push(foundElements, c);
    }

    return foundElements;

}


int getRepoCapacity(Repo *repo)
{
    return repo->countries->capacity;
}


int deleteItem(Repo *repo, Country c)
{
    int i, len = getRepoLength(repo), removeIndex = -1;

    for(i = 0; i < len; ++i)
    {
        Country curr = getItem(repo, i);

        if(comparePopulation(&curr, &c) == 0)
        {
            removeIndex = i;
            break;
        }
    }

    if(removeIndex == -1)
        return 0;

    DynamicArray *newElements = initArray(getRepoCapacity(repo));

    for(i = 0; i < len; ++i)
    {
        if(i == removeIndex)
            continue;
        else
        {
            push(newElements, getElement(repo->countries, i));
        }
    }

    free(repo->countries->elements);
    repo->countries->elements = malloc(sizeof(Element) * repo->countries->capacity);
    memcpy(repo->countries->elements, newElements->elements, sizeof(Element) * (len - 1));
    repo->countries->length--;

    destroyArray(&newElements);
    return 1;
}

int updateCountry(Repo *repo, Country c, Country newc)
{
    int i, len = getRepoLength(repo), countryIndex = -1;
    for(i = 0; i < len; ++i)
    {
        Country curr = getItem(repo, i);
        if(comparePopulation(&c, &curr) == 0)
        {
            countryIndex = i;
            break;
        }
    }

    if(countryIndex == -1)
        return 0;

    deleteItem(repo, c);
    addItem(repo, newc);

    return 1;
}


void clearRepo(Repo *repo)
{
    int oldcapacity = getRepoCapacity(repo);
    destroyArray(&repo->countries);
    repo->countries = initArray(oldcapacity);
}