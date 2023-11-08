#pragma once

#include<vector>
#include<chrono>
#include"Etat.h"

class Environment {
public:
    int size_x;
    int size_y;
    std::vector<std::vector<Etat>> map_etat;

    Environment(int size_x, int size_y);
    std::vector<double> Deplacement(double pos_x, double pos_y, double pos_w, double left_speed, double right_speed, double time);
};


