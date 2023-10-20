//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_OBSTACLE_H
#define COURSC_OBSTACLE_H

#include "Entite.h"
class Obstacle : public Entite {

public:
    bool isSolid;
    Obstacle(int x, int y, bool isSolid);
};


#endif //COURSC_OBSTACLE_H
