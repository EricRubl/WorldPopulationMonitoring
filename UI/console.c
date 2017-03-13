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


void listCountriesMenu()
{
    system("cls");
    printf("1 | Search by name\n");
    printf("2 | Search by continent\n");
    printf("0 | Back to menu\n\n");
}


void updateCountryMenu()
{
    system("cls");
    printf("1 | Change name\n");
    printf("2 | Change continent\n");
    printf("3 | Change population\n");
    printf("4 | Migrate population\n");
    printf("0 | Back to menu\n\n");
}


int readInteger(char* msg)
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
            printf("Please insert integer!\n");
        }
        else
            break;
    }
    return ret;
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
            printf("Invalid option!\n");
        }
        else
            break;
    }
    return ret;
}


Continent readContinent(char* msg)
{
    char s[20];

    while (1)
    {
        printf(msg);
        scanf("%s", s);
        if(strcmp(s, "all") == 0)
            return Dummy;
        char aux[20];
        char *cts;
        int i;
        for(i = 0; i <= 5; i++)
        {
            cts = continentToString(i, aux);
            if (strcmp(s, cts) == 0)
                return i;
        }
        printf("Invalid continent!\n");
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


void UIListCountries(Controller* controller)
{
    while(1)
    {
        listCountriesMenu();
        int user_input = readCommand("");
        switch (user_input)
        {
            case 0:
                return;
            case 1:
            {
                system("cls");
                printf("Keyword: ");
                char s[20];
                getc(stdin);
                fgets(s, 20, stdin);
                char* out = ControllerSearchCountries(controller, s);
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
                system("cls");
                Continent cont = readContinent("Continent: ");
                int val = readInteger("Population limit:");
                char *out = ControllerGetContinent(controller, cont, val);
                if(out == NULL)
                {
                    printf("\n\nContinent empty!");
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
            default:
                printf("Invalid option!");
        }
    }
}


void UIAddCountry(Controller* controller)
{
    system("cls");
    Country c = readCountry();
    int check = ControllerAddCountry(controller, c);
    if(check)
    {
        printf("\n\n%s added", getName(&c));
        getch();
    }
    else
    {
        printf("\n\n%s already exsists", getName(&c));
        getch();
    }
}


void UIDeleteCountry(Controller* controller)
{
    system("cls");
    printf("Country: ");
    char s[20];
    scanf("%s", s);
    int check = ControllerDeleteCountry(controller, s);
    if(check == -1)
    {
        printf("\n\n%s not found", s);
        getch();
    }
    else
    {
        printf("\n\n%s deleted", s);
        getch();
    }
}


void UIUpdateCountry(Controller* controller)
{
    system("cls");
    printf("Country: ");
    char s[20];
    scanf("%s", s);
    Country c = ControllerCountryFromName(controller, s);
    int check = ControllerCheckCountry(controller, c);
    if(!check)
    {
        printf("\n\nInvalid country!");
        getch();
        return;
    }

    while (1)
    {
        updateCountryMenu();
        int user_input = readCommand("");

        switch (user_input)
        {
            case 0:
                return;
            case 1:
            {
                printf("New name: ");
                char ss[20];
                scanf("%s", ss);
                Country cc = newCountry(ss, getContinent(&c), getPopulation(&c));
                ControllerUpdateCountry(controller, c, cc);
                break;
            }
            case 2:
            {
                Continent cont = readContinent("New continent: ");
                Country cc = newCountry(getName(&c), cont, getPopulation(&c));
                ControllerUpdateCountry(controller, c, cc);
                break;
            }
            case 3:
            {
                int pop = readInteger("New population: ");
                Country cc = newCountry(getName(&c), getContinent(&c), pop);
                ControllerUpdateCountry(controller, c, cc);
                break;
            }
            case 4:
            {
                int migration = readInteger("Migration: ");
                printf("Emigrant country: ");
                char ss[20];
                scanf("%s", ss);
                Country emi = ControllerCountryFromName(controller, ss);
                int checkk = ControllerCheckCountry(controller, emi);
                if(!checkk)
                {
                    printf("\nInvalid country!");
                    getch();
                    break;
                }
                if(!ControllerMigratePopulation(controller, c, emi, migration))
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
                UIListCountries(ui->controller);
                break;
            case 2:
                UIAddCountry(ui->controller);
                break;
            case 3:
                UIDeleteCountry(ui->controller);
                break;
            case 4:
                UIUpdateCountry(ui->controller);
                break;
            default:
                printf("Invalid option!");

        }
    }
}