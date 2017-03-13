//
// Created by Eric on 12.03.2017.
//

#ifndef WORLDPOPULATIONMONITORING_CONSOLE_H
#define WORLDPOPULATIONMONITORING_CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include "../Controller/Controller.h"

typedef struct
{
    Controller* controller;
} UI;


//Constructor for UI
UI* initUI(Controller* controller);


//Destructor for controller
void destroyUI(UI** ui);


//Launcher for UI main loop
void launchUI(UI* ui);

#endif //WORLDPOPULATIONMONITORING_CONSOLE_H
