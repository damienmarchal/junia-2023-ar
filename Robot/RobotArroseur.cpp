//
// Created by cload on 23/10/2023.
//

#include "RobotArroseur.h"


void RobotArroseur::arroser() {
    if(this->position[0] == 0 && this->position[1] == 0)
        std::cout << "Arrosage en cours" << std::endl;
}
