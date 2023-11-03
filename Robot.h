#pragma once

#include "Environment.h"
#include <iostream>
#include <vector>

class Robot {
public:
    int id;
    double pos_x;
    double pos_y;
    double pos_w;
    int case_x;
    int case_y;

    Robot(int id, Environment& map, int case_x, int case_y);

    int get_id();
    double get_pos_x();
    double get_pos_y();
    int get_case_x();
    int get_case_y();


    void set_wheel_speed(Environment& map, double left_speed, double right_speed);

};

