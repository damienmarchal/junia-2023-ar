//
// Created by cload on 23/10/2023.
//

#ifndef COURSGITETC_ROBOTPLANTEUR_H
#define COURSGITETC_ROBOTPLANTEUR_H

#include "Robot.h"

class RobotPlanteur : public Robot{
public:
    RobotPlanteur(int x, int y);
    void planter(Environment &env);
    void action(Environment &env);
    bool isFreeZoneToPlant();
};


#endif //COURSGITETC_ROBOTPLANTEUR_H
