//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ROBOT_H
#define COURSC_ROBOT_H

#include <iostream>

#include "Entite.h"

class Robot : public Entite {
public:
    enum class Direction { Nord,Est,Sud,Ouest };
    Direction orientation;

    Robot(int x, int y);
    void deplacer(Direction direction);
};


#endif //COURSC_ROBOT_H
