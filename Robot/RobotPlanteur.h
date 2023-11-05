//
// Created by cload on 23/10/2023.
//

#ifndef COURSGITETC_ROBOTPLANTEUR_H
#define COURSGITETC_ROBOTPLANTEUR_H

#include "Robot.h"

class RobotPlanteur : public Robot{
public:
    RobotPlanteur(int x, int y);
    void planter(Environment &env, int x, int y);
    bool isFreeZoneToPlant(Environment &env, int x, int y);

    void action(Environment &env) override;
    void priseDecision(Environment &env) override;
};


#endif //COURSGITETC_ROBOTPLANTEUR_H
