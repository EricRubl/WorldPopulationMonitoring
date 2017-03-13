#include <stdio.h>
#include <crtdbg.h>
#include "tests.h"
#include "Controller/Controller.h"
#include "UI/console.h"
#include "Domain/Country.h"

int main()
{
    performTests();
    Repo* repo = initRepo();
    Controller controller = initController(repo);
    UI* ui = initUI(&controller);

    Country c = newCountry("Romania", Europe, 22);
    ControllerAddCountry(&controller, c);
    c = newCountry("Germany", Europe, 310);
    ControllerAddCountry(&controller, c);
    c = newCountry("Russia", Asia, 77);
    ControllerAddCountry(&controller, c);
    c = newCountry("Italy", Europe, 40);
    ControllerAddCountry(&controller, c);
    c = newCountry("Canada", America, 170);
    ControllerAddCountry(&controller, c);
    c = newCountry("Australia", Australia, 125);
    ControllerAddCountry(&controller, c);
    c = newCountry("South Africa", Africa, 67);
    ControllerAddCountry(&controller, c);
    c = newCountry("Kenya", Africa, 34);
    ControllerAddCountry(&controller, c);
    c = newCountry("Austria", Europe, 9);
    ControllerAddCountry(&controller, c);
    c = newCountry("Brasil", America, 345);
    ControllerAddCountry(&controller, c);

    launchUI(ui);
    destroyUI(&ui);
    destroyRepo(&repo);
    _CrtDumpMemoryLeaks();
    return 0;
}