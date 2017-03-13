#include <stdio.h>
#include <crtdbg.h>
#include "tests.h"
#include "Controller/Controller.h"
#include "UI/console.h"

int main()
{
    performTests();
    Repo* repo = initRepo();
    Controller controller = initController(repo);
    UI* ui = initUI(&controller);
    launchUI(ui);
    destroyUI(&ui);
    destroyRepo(&repo);
    _CrtDumpMemoryLeaks();
    return 0;
}