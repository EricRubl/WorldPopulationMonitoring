//
// Created by Eric on 13.03.2017.
//

#include <conio.h>
#include "console.h"


UI* initUI(Controller* controller)
{
    UI* ui = malloc(sizeof(UI));
    if(ui == NULL)
        return NULL;

    ui->controller = controller;
    return ui;
}


void destroyUI(UI** ui)
{
    if (*ui == NULL)
        return;

    free(*ui);
    *ui = NULL;
}


void printMenu()
{
    system("cls");
    printf("1 | List countries\n");
    printf("2 | Add country\n");
    printf("3 | Delete country\n");
    printf("4 | Update country\n");
    printf("0 | Exit app\n\n");
}


void listMenu()
{
    system("cls");
    printf("1 | Search by name\n");
    printf("2 | Search by continent\n");
    printf("0 | Back to menu\n\n");
}


void updateMenu()
{
    system("cls");
    printf("1 | Change name\n");
    printf("2 | Change continent\n");
    printf("3 | Change population\n");
    printf("4 | Migrate population\n");
    printf("0 | Back to menu\n\n");
}


int readCommand(char* msg)
{
    char s[20];
    int ret = 0;

    while (1)
    {
        printf(msg);
        scanf("%s", s);
        int result = sscanf(s, "%d", &ret);
        if(result == 0)
        {
            printf("Insert valid Command!\n");
        }
        else
            break;
    }
    return ret;
}


Continent readContinent(char* msg)
{
    char s[20];
    Continent ret = Dummy;

    while (1)
    {
        printf(msg);
        scanf("%s", s);
        char aux[20];
        char *cts;
        int i;
        for (i = 0; i <= 5; i++) {
            cts = ContinentToString(i, aux);
            if (strcmp(s, cts) == 0)
                return i;
        }
        printf("Invalid content!\n");
    }
}

Country readCountry()
{
    printf("Country: ");
    char s[20];
    scanf("%s", s);

    Continent cont = readContinent("Continent: ");
    int population = readCommand("Population: ");

    Country newcountry = newCountry(s, cont, population);
    return newcountry;
}


void UIlistCountries(Controller* controller)
{
    while(1)
    {
        listMenu();
        int user_input = readCommand("");
        switch (user_input)
        {
            case 0:
                return;
            case 1:
            {
                system("cls");
                printf("Search tag: ");
                char s[20];
                scanf("%s", s);
                char* out = searchCountries(controller, s);
                if(out == NULL)
                {
                    printf("\n\nNo matches found!");
                    getch();
                }
                else
                {
                    system("cls");
                    printf(out);
                    getch();
                }
                break;
            }
            case 2:
            {
                Continent cont = readContinent("Continent: ");
                char* out = continentCountries(controller, cont);
                if(out == NULL)
                {
                    printf("\n\nInsert valid continent!");
                    getch();
                }
                else
                {
                    system("cls");
                    printf(out);
                }
                break;
            }
            default:
                printf("Invalid option!");

        }
    }
}


void UIaddCountry(Controller* controller)
{
    Country c = readCountry();
    int check = addCountry(controller, c);
    if(check)
    {
        printf("\n\n%s added", getName(&c));
        getch();
    }
    else
    {
        printf("\n\nError adding %s", getName(&c));
        getch();
    }
}


void UIdeleteCountry(Controller* controller)
{
    Country c = readCountry();
    int check = deleteCountry(controller, c);
    if(check == 0)
    {
        printf("\n\n%s not found", getName(&c));
        getch();
    }
    else
    {
        printf("\n\n%s deleted", getName(&c));
        getch();
    }
}


void UImodifyCountry(Controller* controller)
{
    printf("Country: ");
    Country c = readCountry();
    int check = checkCountry(controller, c);
    if(!check)
    {
        printf("\n\nInvalid country!");
        getch();
        return;
    }

    while (1)
    {
        updateMenu();
        int user_input = readCommand("");

        switch (user_input)
        {
            case 0:
                return;
            case 1:
            {
                printf("New name: ");
                char s[20];
                scanf("%s", s);
                Country cc = newCountry(s, getContinent(&c), getPopulation(&c));
                modifyCountry(controller, c, cc);
                break;
            }
            case 2:
            {
                Continent cont = readContinent("New continent: ");
                Country cc = newCountry(getName(&c), cont, getPopulation(&c));
                modifyCountry(controller, c, cc);
                break;
            }
            case 3:
            {
                int pop = readCommand("New population: ");
                Country cc = newCountry(getName(&c), getContinent(&c), pop);
                modifyCountry(controller, c, cc);
                break;
            }
            case 4:
            {
                int migration = readCommand("Migration: ");
                printf("\nEmigrant country: ");
                Country emi = readCountry();
                if(!migratePopulation(controller, c, emi, migration))
                {
                    printf("\n\nNot enough emigrants!");
                    getch();
                }
                else
                {
                    printf("\n\n%d million migrated from %s to %s", migration, getName(&c), getName(&emi));
                    getch();
                }
                break;
            }
            default:
                printf("\n\nInvalid option!\n\n");
        }
    }
}

void launchUI(UI* ui)
{
    while (1)
    {
        printMenu();
        int user_input = readCommand("");

        switch (user_input)
        {
            case 0:
                return;
            case 1:
                UIlistCountries(ui->controller);
                break;
            case 2:
                UIaddCountry(ui->controller);
                break;
            case 3:
                UIdeleteCountry(ui->controller);
                break;
            case 4:
                UImodifyCountry(ui->controller);
                break;
            default:
                printf("Invalid option!");

        }
    }
}