//
// Created by Eric on 11.03.2017.
//

#include "DynamicArray.h"

DynamicArray *initArray(int capacity)
{
    if(capacity < 0)
        return NULL;

    DynamicArray *array = (DynamicArray *) malloc(sizeof(DynamicArray));

    if(array != NULL)
    {
        array->capacity = capacity;
        array->length = 0;
        array->elements = (Element *) malloc(capacity * sizeof(Element));

        if(array->elements = NULL)
            return NULL;
        return array;
    }
    return NULL;
}


void destroyArray(DynamicArray **array)
{
    if(*array == NULL)
        return;

    Element *elements = (*array)->elements;
    free(elements);
    (*array)->elements = NULL;

    free(*array);
    *array = NULL;
    return;
}


void push(DynamicArray *array, Element e)
{
    if(array == NULL || array->elements == NULL)
        return;

    if(array->length == array->capacity)
        resize(array);

    array->elements[array->length++] = e;
}


int getLength(DynamicArray *array)
{
    if(array == NULL || array->elements == NULL)
        return -1;
    return array->length;
}

int getCapacity(DynamicArray *array)
{
    if(array == NULL)
        return -1;
    return array->capacity;
}


void resize(DynamicArray *array)
{
    if(array == NULL)
        return;
    if(array->capacity == 0)
    {
        array->capacity = 1;
        array->elements = (Element *) realloc(array->elements, array->capacity * sizeof(Element));
        return;
    }

    array->capacity *= 2;
    array->elements = (Element *) realloc(array->elements, array->capacity * sizeof(Element));
}


Element getElement(DynamicArray *array, int index)
{
    makeElement new = newCountry;

    if(index > array->length)
    {
        Element dummy = new("", Dummy, -1);
        return dummy;
    }

    return array->elements[index];
}


void swap(DynamicArray *array, int first, int second)
{
    if(array == NULL || array->elements == NULL)
        return;

    if(first > array->length || second > array->length)
        return;

    Element temp = array->elements[first];
    array->elements[first] = array->elements[second];
    array->elements[second] = temp;
    return;
}


void sort(DynamicArray *array, compElement function, int direction)
{
    if(array == NULL)
        return;

    int i, j, ok = 0, len = array->length;
    while(!ok)
    {
        ok = 1;
        for(i = 0; i < len - 1; ++i)
            for(j = i + 1; j < len; ++j)
            {
                Element first = getElement(array, i);
                Element second = getElement(array, j);
                if(function(&first, &second) == direction)
                {
                    swap(array, i, j);
                    ok = 0;
                }
            }
    }
    return;
}