//
// Created by cload on 23/10/2023.
//

#ifndef COURSGITETC_ROBOTARROSEUR_H
#define COURSGITETC_ROBOTARROSEUR_H

#include "Robot.h"

class RobotArroseur : public Robot{
public:
    RobotArroseur(int x, int y) ;
    void arroser();
    void priseDecision(Environment &env);
    void action();
};


#endif //COURSGITETC_ROBOTARROSEUR_H
