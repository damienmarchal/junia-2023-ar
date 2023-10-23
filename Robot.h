#pragma once

#include "Environment.h"
#include <iostream>
#include <vector>

class Robot {
public:
    int id;
    int pos_x;
    int pos_y;

    Robot(int id, Environment& map, int pos_x, int pos_y);

    int get_id();
    int get_pos_x();
    int get_pos_y();

    void planter(Environment& map);

    void deplacer(Environment& map, int dir);

};

