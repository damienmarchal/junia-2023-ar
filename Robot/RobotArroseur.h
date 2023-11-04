//
// Created by cload on 23/10/2023.
//

#ifndef COURSGITETC_ROBOTARROSEUR_H
#define COURSGITETC_ROBOTARROSEUR_H

#include "Robot.h"

class RobotArroseur : public Robot{
public:
    // constructor
    RobotArroseur(int x, int y) ;
    void arroser(Environment &env);

    void priseDecision(Environment &env) override;
    void action(Environment &env) override;
};


#endif //COURSGITETC_ROBOTARROSEUR_H
