//
// Created by cload on 23/10/2023.
//

#ifndef COURSGITETC_ROBOTRECOLTEUR_H
#define COURSGITETC_ROBOTRECOLTEUR_H

#include "Robot.h"
class RobotRecolteur : public Robot {
public:
    // constructor
    RobotRecolteur(int x, int y);

    // destructor
    ~RobotRecolteur();

    // methods
    void action(Environment &env) override;
    void priseDecision(Environment &env) override;
    void recolter();
};


#endif //COURSGITETC_ROBOTRECOLTEUR_H
